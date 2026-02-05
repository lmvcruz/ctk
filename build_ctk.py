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
            clang_c = os.getenv('CLANG_C_COMPILER', 'clang')
            clang_cxx = os.getenv('CLANG_CXX_COMPILER', 'clang++')
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

        result = subprocess.run([str(test_exe)])

        if result.returncode != 0:
            self.logger.error("Some tests failed")
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
