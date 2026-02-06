#!/usr/bin/env python3
"""
CTK Test Runner
Run GoogleTest unit tests with filtering and other options.
"""

import argparse
import os
import sys
import subprocess
from pathlib import Path
from dotenv import load_dotenv


class CTKTestRunner:
    def __init__(self, args):
        self.args = args
        self.project_root = Path(__file__).parent.absolute()

        # Load .env file for configuration
        env_file = self.project_root / '.env'
        if env_file.exists():
            load_dotenv(env_file)

        # Determine build directory and configuration
        if args.msvc:
            self.build_dir = self.project_root / \
                os.getenv('BUILD_DIR_MSVC', 'build-msvc')
            self.config = args.config or 'Release'
            self.test_exe = self.build_dir / 'ctkunittests' / self.config / 'unittests.exe'
        elif args.clang:
            self.build_dir = self.project_root / \
                os.getenv('BUILD_DIR_CLANG', 'build-clang')
            self.test_exe = self.build_dir / 'ctkunittests' / 'unittests.exe'
        else:
            print("Error: No compiler specified. Use --msvc or --clang")
            sys.exit(1)

        # Check if test executable exists
        if not self.test_exe.exists():
            print(f"Error: Test executable not found at {self.test_exe}")
            print("Build the project first with: python build_ctk.py --msvc (or --clang)")
            sys.exit(1)

        # Setup environment for OpenCV DLLs
        self.test_env = os.environ.copy()
        self.test_env['CTK_ENV_VAR_TEST'] = 'Test'
        self.test_env['CTK_WORKSPACE'] = str(self.project_root)

        # Add OpenCV DLL path
        opencv_dir = os.getenv('OPENCV_DIR')
        if opencv_dir:
            build_type = self.config if args.msvc else os.getenv(
                'CMAKE_BUILD_TYPE', 'Release')
            opencv_bin = Path(opencv_dir) / 'bin' / build_type
            if opencv_bin.exists():
                current_path = self.test_env.get('PATH', '')
                self.test_env['PATH'] = str(
                    opencv_bin) + os.pathsep + current_path

    def run(self):
        """Execute the test runner with appropriate GoogleTest arguments"""
        # Build the command
        cmd = [str(self.test_exe)]

        if self.args.list:
            # List all tests
            cmd.append('--gtest_list_tests')
        elif self.args.filter:
            # Run specific test(s) matching the filter
            cmd.append(f'--gtest_filter={self.args.filter}')

        # Add additional GoogleTest flags
        if self.args.repeat:
            cmd.append(f'--gtest_repeat={self.args.repeat}')

        if self.args.shuffle:
            cmd.append('--gtest_shuffle')

        if self.args.break_on_failure:
            cmd.append('--gtest_break_on_failure')

        if self.args.output:
            cmd.append(f'--gtest_output={self.args.output}')

        if self.args.verbose:
            print(f"Running: {' '.join(cmd)}")
            print(f"Working directory: {self.build_dir}")
            print()

        # Run the tests
        try:
            result = subprocess.run(
                cmd,
                env=self.test_env,
                cwd=self.build_dir
            )
            return result.returncode
        except Exception as e:
            print(f"Error running tests: {e}", file=sys.stderr)
            return 1


def main():
    parser = argparse.ArgumentParser(
        description='Run CTK unit tests with GoogleTest filtering and options',
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  # List all tests
  %(prog)s --msvc --list

  # Run a specific test
  %(prog)s --msvc --filter CtkFileSystemTest.Test_CurrentPath

  # Run all tests in a test suite
  %(prog)s --clang --filter CtkFileSystemTest.*

  # Run tests matching a pattern (wildcards supported)
  %(prog)s --msvc --filter *Image*

  # Run all tests except certain ones
  %(prog)s --clang --filter -*Slow*

  # Run all tests in Release config
  %(prog)s --msvc --config Release

  # Run all tests in Debug config
  %(prog)s --msvc --config Debug

  # Repeat tests 5 times
  %(prog)s --clang --filter CtkFileSystemTest.* --repeat 5

  # Generate XML report
  %(prog)s --msvc --output xml:test_results.xml

GoogleTest Filter Syntax:
  - Use * as wildcard: *Image* matches any test with "Image" in the name
  - Use : to separate multiple patterns: Test1:Test2
  - Use - prefix to exclude: -*Slow* excludes tests with "Slow" in name
  - Combine inclusion and exclusion: *Fast*:*Quick*-*Unstable*
        """
    )

    # Compiler selection (mutually exclusive)
    compiler_group = parser.add_mutually_exclusive_group(required=True)
    compiler_group.add_argument('--msvc', action='store_true',
                                help='Use MSVC build')
    compiler_group.add_argument('--clang', action='store_true',
                                help='Use Clang build')

    # Test configuration (MSVC only)
    parser.add_argument('--config', type=str, choices=['Debug', 'Release'],
                        help='Build configuration for MSVC (default: Release)')

    # Test filtering and execution
    parser.add_argument('--list', action='store_true',
                        help='List all available tests')
    parser.add_argument('--filter', type=str, metavar='PATTERN',
                        help='Run only tests matching the filter pattern (GoogleTest syntax)')

    # GoogleTest options
    parser.add_argument('--repeat', type=int, metavar='N',
                        help='Run tests N times')
    parser.add_argument('--shuffle', action='store_true',
                        help='Randomize test execution order')
    parser.add_argument('--break-on-failure', action='store_true',
                        help='Break on first test failure')
    parser.add_argument('--output', type=str, metavar='FORMAT:FILE',
                        help='Output format (e.g., xml:results.xml or json:results.json)')

    # Utility options
    parser.add_argument('--verbose', '-v', action='store_true',
                        help='Verbose output')

    args = parser.parse_args()

    runner = CTKTestRunner(args)
    return_code = runner.run()
    sys.exit(return_code)


if __name__ == '__main__':
    main()
