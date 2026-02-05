# ctk
Cross Toolkit

Two environment variables has to be created:
export CTK_ENV_VAR_TEST=Test
export CTK_WORKSPACE=<CODE_FOLDER>

Note that CTK_ENV_VAR_TEST is just a test case used in unit test and its value has to be 'Test'

# Build Script Usage Guide

This project contains a .pro configuration, to use with QT environment. We also have a CMake to build out of QT. In addition, we create a build script to make easier the configuration of cmake.

First of all, create an .env file filling up all variables in .env.example. Also, the script build_ctk.py requires python-dotenv (ensure it is installed).

Please, see the usage instructions below:


### 2. Build the project

```powershell
# Build with MSVC (Release mode, default)
python build_ctk.py --msvc

# Build with Clang (Release mode)
python build_ctk.py --clang

# Build in Debug mode
python build_ctk.py --msvc --debug
python build_ctk.py --clang --debug
```

## Common Usage Examples

### Clean Build
```powershell
python build_ctk.py --msvc --clean
```

### Build and Run Tests
```powershell
python build_ctk.py --clang --test
```

### Configure Only (no build)
```powershell
python build_ctk.py --msvc --configure-only
```

### Build Only (skip configuration)
```powershell
python build_ctk.py --clang --build-only
```

### Build Specific Target
```powershell
python build_ctk.py --msvc --target ctklib
```

### Parallel Build with Custom Job Count
```powershell
python build_ctk.py --clang --jobs 4
```

### List Available Targets (Clang/Ninja only)
```powershell
python build_ctk.py --clang --list-targets
```

### Build and Install
```powershell
python build_ctk.py --msvc --install --install-prefix "D:/MyInstall"
```

### Verbose Logging (Debug mode)
```powershell
# Enable verbose logging to see detailed output
python build_ctk.py --clang --verbose

# Useful for debugging build issues
python build_ctk.py --msvc --configure-only --verbose
```

## Environment Variables (.env)

Required variables:
- `OPENCV_DIR` - Path to OpenCV build directory
- `GTEST_DIR` - Path to GTest CMake config directory
- `BENCHMARK_DIR` - Path to Google Benchmark CMake config directory

Optional variables:
- `BUILD_DIR_MSVC` - Custom MSVC build directory (default: `build-msvc`)
- `BUILD_DIR_CLANG` - Custom Clang build directory (default: `build-clang`)
- `BUILD_JOBS` - Number of parallel build jobs (default: CPU count)
- `INSTALL_PREFIX` - Default installation directory
- `CMAKE_GENERATOR_MSVC` - CMake generator for MSVC (default: `Visual Studio 17 2022`)
- `CLANG_C_COMPILER` - Path to clang executable (default: `clang`)
- `CLANG_CXX_COMPILER` - Path to clang++ executable (default: `clang++`)

## All Command-Line Options

```
usage: build_ctk.py [-h] (--msvc | --clang) [--debug] [--jobs N] [--clean]
                     [--configure-only] [--build-only] [--target TARGET]
                     [--test] [--install] [--install-prefix PATH]
                     [--list-targets] [--verbose]

Options:
  --msvc                Build using MSVC compiler
  --clang               Build using Clang compiler
  --debug               Build in Debug mode (default: Release)
  --jobs N, -j N        Number of parallel build jobs
  --clean               Clean build directory before building
  --configure-only      Only run CMake configuration
  --build-only          Only build (skip configuration)
  --target TARGET       Build specific target
  --test                Run unit tests after building
  --install             Install the project after building
  --install-prefix PATH Installation prefix
  --list-targets        List available build targets
  --verbose, -v         Verbose build output
```

