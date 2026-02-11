#!/usr/bin/env python3
"""
CTK Build Script
Automates building the CTK project with different compilers and configurations.
"""

import argparse
import os
import sys
import subprocess
import shutil
import multiprocessing
import logging
from pathlib import Path
from dotenv import load_dotenv


class ColoredFormatter(logging.Formatter):
    """Custom formatter with colors for different log levels"""

    COLORS = {
        'DEBUG': '\033[96m',      # Cyan
        'INFO': '\033[94m',       # Blue
        'SUCCESS': '\033[92m',    # Green
        'WARNING': '\033[93m',    # Yellow
        'ERROR': '\033[91m',      # Red
        'CRITICAL': '\033[91m',   # Red
        'HEADER': '\033[95m',     # Magenta
    }
    RESET = '\033[0m'
    BOLD = '\033[1m'

    def format(self, record):
        # Add color to the level name
        levelname = record.levelname
        if levelname in self.COLORS:
            record.levelname = f"{self.COLORS[levelname]}{levelname}{self.RESET}"

        # Handle special 'HEADER' level
        if hasattr(record, 'header') and record.header:
            msg = record.getMessage()
            separator = '=' * 60
            return f"\n{self.COLORS['HEADER']}{self.BOLD}{separator}{self.RESET}\n" \
                   f"{self.COLORS['HEADER']}{self.BOLD}{msg}{self.RESET}\n" \
                   f"{self.COLORS['HEADER']}{self.BOLD}{separator}{self.RESET}\n"

        return super().format(record)


def setup_logger(verbose=False):
    """Configure the logger with colored output"""
    # Add custom SUCCESS level
    logging.SUCCESS = 25  # Between INFO(20) and WARNING(30)
    logging.addLevelName(logging.SUCCESS, 'SUCCESS')

    def success(self, message, *args, **kwargs):
        if self.isEnabledFor(logging.SUCCESS):
            self._log(logging.SUCCESS, message, args, **kwargs)

    def header(self, message, *args, **kwargs):
        if self.isEnabledFor(logging.INFO):
            self._log(logging.INFO, message, args,
                      extra={'header': True}, **kwargs)

    logging.Logger.success = success
    logging.Logger.header = header

    # Configure root logger
    logger = logging.getLogger('CTKBuilder')
    logger.setLevel(logging.DEBUG if verbose else logging.INFO)

    # Create console handler
    handler = logging.StreamHandler(sys.stdout)
    handler.setLevel(logging.DEBUG if verbose else logging.INFO)

    # Set formatter
    formatter = ColoredFormatter('%(levelname)s: %(message)s')
    handler.setFormatter(formatter)

    # Add handler to logger
    logger.addHandler(handler)

    return logger


class CTKBuilder:
    def __init__(self, args, logger):
        self.args = args
        self.logger = logger
        self.project_root = Path(__file__).parent.absolute()

        # Load .env file
        env_file = self.project_root / '.env'
        if not env_file.exists():
            self.logger.warning(f".env file not found at {env_file}")
            self.logger.info(
                "Using .env.example as template. Please create .env with your custom paths.")
            env_file = self.project_root / '.env.example'

        load_dotenv(env_file)

        # Get configuration from .env
        self.opencv_dir = os.getenv('OPENCV_DIR')
        self.gtest_dir = os.getenv('GTEST_DIR')
        self.benchmark_dir = os.getenv('BENCHMARK_DIR')

        # Build directories
        if args.msvc:
            self.build_dir = self.project_root / \
                os.getenv('BUILD_DIR_MSVC', 'build-msvc')
            self.compiler = 'MSVC'
        elif args.clang:
            self.build_dir = self.project_root / \
                os.getenv('BUILD_DIR_CLANG', 'build-clang')
            self.compiler = 'Clang'
        else:
            self.logger.error("No compiler specified. Use --msvc or --clang")
            sys.exit(1)

        # Build configuration
        self.build_type = 'Debug' if args.debug else 'Release'
        self.jobs = args.jobs or os.getenv(
            'BUILD_JOBS') or multiprocessing.cpu_count()
        self.install_prefix = args.install_prefix or os.getenv(
            'INSTALL_PREFIX')

        # Validate required paths
        self._validate_paths()

    def _validate_paths(self):
        """Validate that required dependency paths exist"""
        missing = []

        if not self.opencv_dir or not Path(self.opencv_dir).exists():
            missing.append(f"OpenCV: {self.opencv_dir}")

        if not self.gtest_dir or not Path(self.gtest_dir).parent.parent.parent.exists():
            missing.append(f"GTest: {self.gtest_dir}")

        if not self.benchmark_dir or not Path(self.benchmark_dir).parent.parent.parent.exists():
            missing.append(f"Benchmark: {self.benchmark_dir}")

        if missing:
            self.logger.error("Missing required dependencies:")
            for item in missing:
                self.logger.error(f"  - {item}")
            self.logger.info(
                "\nPlease update your .env file with correct paths.")
            sys.exit(1)

    def clean(self):
        """Clean build directory"""
        if self.build_dir.exists():
            self.logger.info(f"Cleaning {self.build_dir}...")
            shutil.rmtree(self.build_dir)
            self.logger.success(f"Removed {self.build_dir}")
        else:
            self.logger.info(
                f"Build directory {self.build_dir} does not exist. Nothing to clean.")

    def configure(self):
        """Configure the project with CMake"""
        self.logger.header(
            f"Configuring CTK with {self.compiler} ({self.build_type})")

        # Create build directory
        self.build_dir.mkdir(parents=True, exist_ok=True)

        # Prepare CMake command
        cmake_args = [
            'cmake',
            f'-DOpenCV_DIR={self.opencv_dir}',
            f'-DGTest_DIR={self.gtest_dir}',
            f'-Dbenchmark_DIR={self.benchmark_dir}',
        ]

        if self.args.msvc:
            # MSVC configuration
            generator = os.getenv('CMAKE_GENERATOR_MSVC',
                                  'Visual Studio 17 2022')
            cmake_args.extend(['-G', generator])
        elif self.args.clang:
            # Clang configuration
            clang_c = os.getenv('CLANG_C_COMPILER')
            clang_cxx = os.getenv('CLANG_CXX_COMPILER')

            # Auto-detect Clang on Windows if not specified
            if not clang_c or not clang_cxx:
                if sys.platform == 'win32':
                    # Try common Clang installation paths on Windows
                    possible_paths = [
                        r'C:\Program Files\LLVM\bin\clang.exe',
                        r'C:\Program Files (x86)\LLVM\bin\clang.exe',
                    ]
                    for path in possible_paths:
                        if Path(path).exists():
                            clang_c = clang_c or path
                            clang_cxx = clang_cxx or path.replace(
                                'clang.exe', 'clang++.exe')
                            self.logger.info(f"Auto-detected Clang at: {path}")
                            break
                    else:
                        # Try to find in PATH
                        try:
                            result = subprocess.run(['where', 'clang'],
                                                    capture_output=True,
                                                    text=True,
                                                    check=True)
                            clang_path = result.stdout.strip().split('\n')[0]
                            clang_c = clang_c or clang_path
                            clang_cxx = clang_cxx or clang_path.replace(
                                'clang.exe', 'clang++.exe')
                            self.logger.info(
                                f"Found Clang in PATH: {clang_path}")
                        except subprocess.CalledProcessError:
                            self.logger.error(
                                "Clang not found! Please install LLVM/Clang or set "
                                "CLANG_C_COMPILER and CLANG_CXX_COMPILER in .env"
                            )
                            sys.exit(1)
                else:
                    # On Linux/macOS, use defaults
                    clang_c = clang_c or 'clang'
                    clang_cxx = clang_cxx or 'clang++'

            cmake_args.extend([
                '-G', 'Ninja',
                f'-DCMAKE_C_COMPILER={clang_c}',
                f'-DCMAKE_CXX_COMPILER={clang_cxx}',
                f'-DCMAKE_BUILD_TYPE={self.build_type}',
            ])

        if self.install_prefix:
            cmake_args.append(f'-DCMAKE_INSTALL_PREFIX={self.install_prefix}')

        # Add source directory
        cmake_args.append('..')

        # Run CMake
        self.logger.info(f"Running: {' '.join(cmake_args)}")
        result = subprocess.run(cmake_args, cwd=self.build_dir)

        if result.returncode != 0:
            self.logger.error("CMake configuration failed")
            sys.exit(1)

        self.logger.success("Configuration completed successfully")

    def build(self):
        """Build the project"""
        self.logger.header(
            f"Building CTK with {self.compiler} ({self.build_type})")

        if not self.build_dir.exists():
            self.logger.error(
                f"Build directory {self.build_dir} does not exist. Run configure first.")
            sys.exit(1)

        # Prepare build command
        if self.args.msvc:
            build_cmd = [
                'cmake',
                '--build', '.',
                '--config', self.build_type,
                '--parallel', str(self.jobs)
            ]
        else:  # Clang with Ninja
            build_cmd = ['ninja']
            if self.args.verbose:
                build_cmd.append('-v')
            build_cmd.extend(['-j', str(self.jobs)])

        # Add specific target if requested
        if self.args.target:
            build_cmd.append(self.args.target)

        self.logger.info(f"Running: {' '.join(build_cmd)}")
        self.logger.info(f"Using {self.jobs} parallel jobs")

        result = subprocess.run(build_cmd, cwd=self.build_dir)

        if result.returncode != 0:
            self.logger.error("Build failed")
            sys.exit(1)

        self.logger.success("Build completed successfully")

    def test(self):
        """Run unit tests"""
        self.logger.header("Running Unit Tests")

        if self.args.msvc:
            test_exe = self.build_dir / 'ctkunittests' / self.build_type / 'unittests.exe'
        else:
            test_exe = self.build_dir / 'ctkunittests' / 'unittests.exe'

        if not test_exe.exists():
            self.logger.error(f"Test executable not found at {test_exe}")
            self.logger.info("Build the project first.")
            sys.exit(1)

        # Set up environment variables for tests
        test_env = os.environ.copy()
        test_env['CTK_ENV_VAR_TEST'] = 'Test'
        test_env['CTK_WORKSPACE'] = str(self.project_root)

        # Add DLL paths to PATH for runtime dependencies
        dll_paths = []
        if self.opencv_dir:
            # OpenCV_DIR points to build directory, DLLs are in build/bin/Release or build/bin/Debug
            opencv_build_root = Path(self.opencv_dir)
            opencv_bin = opencv_build_root / 'bin' / self.build_type
            if opencv_bin.exists():
                dll_paths.append(str(opencv_bin))
                self.logger.debug(f"Added OpenCV DLL path: {opencv_bin}")
            else:
                self.logger.warning(
                    f"OpenCV bin directory not found: {opencv_bin}")

        if dll_paths:
            current_path = test_env.get('PATH', '')
            test_env['PATH'] = os.pathsep.join(dll_paths + [current_path])
            self.logger.debug(f"Updated PATH with DLL directories")

        self.logger.info(f"Running: {test_exe}")
        try:
            result = subprocess.run(
                [str(test_exe)],
                env=test_env,
                cwd=self.build_dir,
                capture_output=False,  # Show output directly
                text=True
            )
        except Exception as e:
            self.logger.error(f"Failed to run tests: {e}")
            sys.exit(1)

        if result.returncode != 0:
            self.logger.error(
                f"Tests failed with exit code {result.returncode}")
            sys.exit(1)

        self.logger.success("All tests passed")

    def install(self):
        """Install the project"""
        self.logger.header("Installing CTK")

        if not self.install_prefix:
            self.logger.error(
                "No install prefix specified. Set INSTALL_PREFIX in .env or use --install-prefix")
            sys.exit(1)

        install_cmd = ['cmake', '--install', '.']
        if self.args.msvc:
            install_cmd.extend(['--config', self.build_type])

        result = subprocess.run(install_cmd, cwd=self.build_dir)

        if result.returncode != 0:
            self.logger.error("Installation failed")
            sys.exit(1)

        self.logger.success(f"Installation completed to {self.install_prefix}")

    def format_check(self, fix=False):
        """Check or fix clang-format violations"""
        action = "Fixing" if fix else "Checking"
        self.logger.header(f"{action} Clang-Format Violations")

        # Find clang-format executable
        clang_format = None
        possible_paths = [
            r'C:\Program Files\LLVM\bin\clang-format.exe',
            r'C:\Program Files (x86)\LLVM\bin\clang-format.exe',
        ]
        
        for path in possible_paths:
            if Path(path).exists():
                clang_format = path
                break
        
        if not clang_format:
            # Try to find in PATH
            try:
                result = subprocess.run(['where', 'clang-format'],
                                        capture_output=True,
                                        text=True,
                                        check=True)
                clang_format = result.stdout.strip().split('\n')[0]
            except subprocess.CalledProcessError:
                self.logger.error(
                    "clang-format not found! Please install LLVM/Clang.")
                sys.exit(1)

        self.logger.info(f"Using clang-format: {clang_format}")

        # Find source files
        source_dirs = ['ctk', 'ctkunittests', 'benchmark', 'demos']
        extensions = ['*.cpp', '*.h', '*.hpp']
        
        files_to_check = []
        for src_dir in source_dirs:
            src_path = self.project_root / src_dir
            if src_path.exists():
                for ext in extensions:
                    files_to_check.extend(src_path.rglob(ext))

        if not files_to_check:
            self.logger.warning("No source files found to check")
            return

        self.logger.info(f"Found {len(files_to_check)} source files")

        violations_found = 0
        files_with_violations = []

        for file_path in files_to_check:
            # Check for violations using --dry-run --Werror
            if fix:
                cmd = [clang_format, '-i', str(file_path)]
            else:
                cmd = [clang_format, '--dry-run', '--Werror', str(file_path)]
            
            result = subprocess.run(cmd, capture_output=True, text=True)
            
            if result.returncode != 0:
                violations_found += 1
                files_with_violations.append(file_path)
                if self.args.verbose:
                    self.logger.warning(f"Violation in: {file_path.relative_to(self.project_root)}")
                    if result.stderr:
                        for line in result.stderr.strip().split('\n')[:5]:
                            self.logger.info(f"  {line}")

        if fix:
            self.logger.success(f"Formatted {len(files_to_check)} files")
        elif violations_found > 0:
            self.logger.error(f"\nFound {violations_found} files with format violations:")
            for f in files_with_violations[:20]:  # Show first 20
                self.logger.error(f"  - {f.relative_to(self.project_root)}")
            if len(files_with_violations) > 20:
                self.logger.error(f"  ... and {len(files_with_violations) - 20} more")
            self.logger.info("\nRun with --format-fix to automatically fix violations")
            sys.exit(1)
        else:
            self.logger.success("No format violations found!")

    def list_targets(self):
        """List available build targets"""
        self.logger.header("Available Build Targets")

        if not self.build_dir.exists():
            self.logger.error(
                "Build directory does not exist. Configure first.")
            sys.exit(1)

        if self.args.clang:
            result = subprocess.run(['ninja', '-t', 'targets', 'all'],
                                    cwd=self.build_dir,
                                    capture_output=True,
                                    text=True)
            if result.returncode == 0:
                targets = [line.split(':')[0]
                           for line in result.stdout.splitlines()]
                for target in sorted(targets):
                    self.logger.info(f"  - {target}")
        else:
            self.logger.info("Use Visual Studio to see available targets")

    def run(self):
        """Execute the build process"""
        try:
            if self.args.list_targets:
                self.list_targets()
                return

            if self.args.format_check:
                self.format_check(fix=False)
                return

            if self.args.format_fix:
                self.format_check(fix=True)
                return

            if self.args.clean:
                self.clean()

            if not self.args.build_only:
                self.configure()

            if not self.args.configure_only:
                self.build()

            if self.args.test:
                self.test()

            if self.args.install:
                self.install()

            self.logger.success("\nAll operations completed successfully!")

        except KeyboardInterrupt:
            self.logger.error("\nBuild interrupted by user")
            sys.exit(1)
        except Exception as e:
            self.logger.error(f"Unexpected error: {e}")
            sys.exit(1)


def main():
    parser = argparse.ArgumentParser(
        description='Build CTK project with different compilers and configurations',
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  %(prog)s --msvc                    # Build with MSVC (Release)
  %(prog)s --clang --debug           # Build with Clang (Debug)
  %(prog)s --msvc --clean            # Clean and build with MSVC
  %(prog)s --clang --test            # Build with Clang and run tests
  %(prog)s --msvc --configure-only   # Only configure, don't build
  %(prog)s --clang --target ctklib   # Build only the ctklib target
  %(prog)s --clang --list-targets    # List available build targets
  %(prog)s --msvc --format-check     # Check for clang-format violations
  %(prog)s --msvc --format-fix       # Fix clang-format violations
        """
    )

    # Compiler selection (mutually exclusive)
    compiler_group = parser.add_mutually_exclusive_group(required=True)
    compiler_group.add_argument('--msvc', action='store_true',
                                help='Build using MSVC compiler')
    compiler_group.add_argument('--clang', action='store_true',
                                help='Build using Clang compiler')

    # Build configuration
    parser.add_argument('--debug', action='store_true',
                        help='Build in Debug mode (default: Release)')
    parser.add_argument('--jobs', '-j', type=int, metavar='N',
                        help='Number of parallel build jobs (default: CPU count)')

    # Build steps
    parser.add_argument('--clean', action='store_true',
                        help='Clean build directory before building')
    parser.add_argument('--configure-only', action='store_true',
                        help='Only run CMake configuration, do not build')
    parser.add_argument('--build-only', action='store_true',
                        help='Only build, skip configuration (assumes already configured)')
    parser.add_argument('--target', type=str, metavar='TARGET',
                        help='Build specific target (e.g., ctklib, unittests)')

    # Post-build actions
    parser.add_argument('--test', action='store_true',
                        help='Run unit tests after building')
    parser.add_argument('--install', action='store_true',
                        help='Install the project after building')
    parser.add_argument('--install-prefix', type=str, metavar='PATH',
                        help='Installation prefix (overrides .env)')

    # Utility options
    parser.add_argument('--list-targets', action='store_true',
                        help='List available build targets')
    parser.add_argument('--verbose', '-v', action='store_true',
                        help='Verbose build output')
    parser.add_argument('--format-check', action='store_true',
                        help='Check for clang-format violations (dry-run)')
    parser.add_argument('--format-fix', action='store_true',
                        help='Fix clang-format violations in-place')

    args = parser.parse_args()

    # Validate argument combinations
    if args.configure_only and args.build_only:
        parser.error(
            "--configure-only and --build-only are mutually exclusive")

    # Setup logger
    logger = setup_logger(verbose=args.verbose)

    builder = CTKBuilder(args, logger)
    builder.run()


if __name__ == '__main__':
    main()
