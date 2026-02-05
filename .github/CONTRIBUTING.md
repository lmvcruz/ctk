# Contributing to CTK

Thank you for your interest in contributing to CTK! This document provides guidelines and instructions for contributing.

## Development Setup

### Prerequisites

- CMake 3.5 or higher
- C++17 compatible compiler (MSVC 2019+, GCC 11+, Clang 14+)
- Python 3.11+ (for build script)
- Git

### Getting Started

1. **Fork and clone the repository**
   ```bash
   git clone https://github.com/yourusername/ctk.git
   cd ctk
   ```

2. **Create a feature branch**
   ```bash
   git checkout -b feature/your-feature-name
   ```

3. **Set up environment**
   ```bash
   # Copy environment template
   cp .env.example .env

   # Edit .env with your local paths
   # Install Python dependencies
   pip install -r requirements.txt
   ```

4. **Build the project**
   ```bash
   # Windows with MSVC
   python build_ctk.py --msvc

   # Linux/macOS with system compiler
   python build_ctk.py --clang
   ```

## Build and Test

### Building

Use the build script for consistent builds:

```bash
# Full build with tests
python build_ctk.py --msvc --test

# Clean build
python build_ctk.py --clang --clean

# Debug build
python build_ctk.py --msvc --debug
```

### Running Tests

```bash
# Build and run tests
python build_ctk.py --msvc --test

# Or run tests manually
cd build-msvc/ctkunittests/Release
./unittests.exe
```

### Code Style

- Follow C++17 best practices
- Use meaningful variable and function names
- Add comments for complex logic
- Keep functions focused and reasonably sized

## Continuous Integration

All pull requests must pass:
- ✅ Build on Windows, Linux, and macOS
- ✅ All unit tests passing
- ✅ Code quality checks (cppcheck, clang-format)
- ✅ Python linting (for build scripts)

## Submitting Changes

1. **Commit your changes**
   ```bash
   git add .
   git commit -m "feat: add your feature description"
   ```

   Use conventional commit messages:
   - `feat:` - New feature
   - `fix:` - Bug fix
   - `docs:` - Documentation changes
   - `test:` - Test additions/changes
   - `refactor:` - Code refactoring
   - `perf:` - Performance improvements
   - `chore:` - Maintenance tasks

2. **Push to your fork**
   ```bash
   git push origin feature/your-feature-name
   ```

3. **Create a Pull Request**
   - Go to the original repository
   - Click "New Pull Request"
   - Select your fork and branch
   - Fill in the PR template with:
     - Description of changes
     - Related issues
     - Testing performed
     - Screenshots (if UI changes)

## Pull Request Guidelines

- Keep PRs focused on a single feature or fix
- Update documentation if needed
- Add tests for new functionality
- Ensure CI builds pass
- Respond to review comments promptly
- Rebase on latest `develop` before merging

## Reporting Issues

When reporting bugs, please include:
- OS and version
- Compiler and version
- Steps to reproduce
- Expected vs actual behavior
- Relevant logs or screenshots

## Questions?

Feel free to open an issue for questions or discussions!
