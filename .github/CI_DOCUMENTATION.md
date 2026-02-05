# GitHub Actions CI/CD Documentation

This document describes the continuous integration and deployment workflows for the CTK project.

## Workflows Overview

### 1. CI Build and Test (`ci.yml`)

**Trigger:** Push to `develop`/`main`, Pull Requests
**Purpose:** Validate code on all platforms

**Build Matrix:**
- **Windows:** MSVC (Visual Studio 2022), Clang/LLVM with Ninja
- **Linux:** GCC 11

**Steps:**
1. Checkout code
2. Set up Python environment
3. Install platform-specific dependencies **via system package managers** (fast!)
4. Configure CTK with CMake
5. Build CTK
6. Run unit tests
7. Upload logs on failure

**Performance:**
- **Linux:** ~30 seconds for dependencies (apt-get)
- **Windows:** ~5 minutes for dependencies (vcpkg binary cache) + Clang installation
- **Total CI time:** ~8-12 minutes per platform

See [CI_OPTIMIZATION.md](CI_OPTIMIZATION.md) for details.

**Status Badge:**
```markdown
[![CI Build and Test](https://github.com/lmvcruz/ctk/actions/workflows/ci.yml/badge.svg)](https://github.com/lmvcruz/ctk/actions/workflows/ci.yml)
```

### 2. Build Release (`build-release.yml`)

**Trigger:** Release creation, Manual workflow dispatch
**Purpose:** Build distributable artifacts

**Outputs:**
- `ctk-windows-x64.tar.gz`
- `ctk-linux-x64.tar.gz`
- `ctk-macos-arm64.tar.gz`

**Steps:**
1. Build optimized Release configuration
2. Install to staging directory
3. Package with README and LICENSE
4. Create compressed archives
5. Upload as artifacts
6. Attach to GitHub release (if release trigger)

**Manual Trigger:**
```bash
# Via GitHub UI: Actions → Build Release Artifacts → Run workflow
# Specify version tag: v0.1.0
```

### 3. Code Quality Checks (`code-quality.yml`)

**Trigger:** Push, Pull Requests
**Purpose:** Enforce code standards

**Checks:**
- **clang-format:** C++ code formatting (Google style)
- **cppcheck:** Static analysis for C++ code
- **flake8/black/pylint:** Python linting for build scripts

**Configuration:**
- C++ formatting: Google style (fallback)
- Python: max line length 100, ignore E203/W503

### 4. Dependency Management

**Dependency Versions (configurable in workflow env):**
- OpenCV: 4.10.0
- GTest: 1.15.2
- Google Benchmark: 1.9.0

**Update Dependencies:**
Edit workflow files and change `env` section:
```yaml
env:
  OPENCV_VERSION: '4.11.0'  # Update here
  GTEST_VERSION: '1.16.0'
  BENCHMARK_VERSION: '1.10.0'
```

## CI Cache Management

**Cache Keys:**
- `{os}-opencv-{version}-{compiler}` - OpenCV builds
- `{os}-gtest-{version}` - GTest installations
- `{os}-benchmark-{version}` - Benchmark installations

**Clear Cache:**
If builds fail due to corrupted cache:
1. Go to Actions → Caches
2. Delete specific cache entries
3. Re-run workflow

## Local Testing

Before pushing, test locally:

```bash
# Test on your platform
python build_ctk.py --msvc --clean --test  # Windows
python build_ctk.py --clang --clean --test # Linux/macOS

# Run code quality checks
black --check build_ctk.py
flake8 build_ctk.py --max-line-length=100
pylint build_ctk.py
```

## Workflow Secrets

No secrets currently required. All builds use public dependencies.

## Troubleshooting CI Failures

### Build Failures

**Symptom:** CMake configuration fails
**Solution:**
- Check dependency versions in workflow
- Verify CMakeLists.txt compatibility
- Review uploaded build logs

**Symptom:** Tests fail on specific platform
**Solution:**
- Check platform-specific code paths
- Review test output in Actions logs
- Add platform guards if needed

### Cache Issues

**Symptom:** Build takes too long
**Solution:** Verify caches are being hit (check logs)

**Symptom:** Weird build errors after dependency update
**Solution:** Clear caches and rebuild

### Code Quality Failures

**Symptom:** clang-format check fails
**Solution:**
```bash
# Auto-format C++ code
clang-format -i ctk/**/*.cpp ctk/**/*.h
```

**Symptom:** Python linting fails
**Solution:**
```bash
# Auto-format Python
black build_ctk.py
# Fix issues manually based on pylint output
```

**Email Notifications:**
Configure in GitHub Settings → Notifications
