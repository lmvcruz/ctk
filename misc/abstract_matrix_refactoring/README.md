# AbstractMatrix Refactoring

This document tracks improvements for the `AbstractMatrix` class.

## Benchmarking Strategy

| Branch | Purpose |
|--------|---------|
| `dev/no_change` | Baseline benchmark (from develop, no refactoring) |
| `dev/refactor_abstract_matrix` | Refactored code (C++17) |
| `dev/cpp20_std_span` | C++20 with std::span |

Results are saved in `misc/abstract_matrix_refactoring/results/`.

---

## Implemented Improvements

### 🔴 Critical (Safety)

- [x] **Fix UB in `end()` iterator** - Use `ptr<T>() + size` instead of `at<T>(size)`
- [x] **Add const iterators** - `begin() const` and `end() const`
- [x] **Rule of Five** - Added move constructor, move assignment, copy assignment

### 🟠 High Priority (Performance)

- [x] **Use `std::fill()` for `Fill()`** - Replaced element-by-element loop with `std::fill(begin(), end(), v)`
  - Note: `cv::Mat::setTo()` not viable as it doesn't work with vector types like `cv::Vec3b`
- [x] **Move semantics for cv::Mat constructor** - Added `AbstractMatrix(cv::Mat&&)`
- [x] **Member initializer lists** - All constructors now use init lists

### 🟡 Medium Priority (Modern C++)

- [x] **Add `noexcept`** - To getters and non-throwing methods
- [x] **Add `[[nodiscard]]`** - To getters to prevent ignoring return values
- [x] **Use `std::string_view`** - For `Open()` and `Save()` parameters in all derived classes
  - Updated: `NumericMatrix`, `BinaryImage`, `GrayImage`, `AbstractImage<T>`

### 🔵 Low Priority (Code Quality)

- [x] **Fix typo** - `"AbstractMatyrix"` → `"AbstractMatrix"` in exception messages
- [x] **Complete Doxygen documentation** - Full documentation for all public members
- [x] **Use `std::span`** - For `Create()` vector parameter (C++20)
  - Note: `std::vector<bool>` requires special handling (not contiguous)
- [ ] **Use `size_t`** - For size-related return types (future)

---

## Benchmark Results Comparison

### Three-Way Comparison (Baseline vs C++17 Refactored vs C++20 std::span)

| Benchmark | Baseline | C++17 Refactored | C++20 std::span | Baseline → C++17 | C++17 → C++20 |
|-----------|----------|------------------|-----------------|------------------|---------------|
| NM_CreateNumericMatrix/8/8 | 1244 ns | 1099 ns | 1088 ns | **-11.7%** ✅ | **-1.0%** |
| NM_CreateNumericMatrix/32/32 | 16029 ns | 14218 ns | 13184 ns | **-11.3%** ✅ | **-7.3%** ✅ |
| NM_Vec2NumericMatrix/8/8 | 357 ns | 222 ns | 176 ns | **-37.8%** ✅ | **-20.7%** ✅ |
| NM_Vec2NumericMatrix/32/32 | 1867 ns | 830 ns | 279 ns | **-55.5%** ✅ | **-66.4%** ✅ |
| NM_CvMat2NumericMatrix/8/8 | 335 ns | 269 ns | 239 ns | **-19.7%** ✅ | **-11.2%** ✅ |
| NM_CvMat2NumericMatrix/32/32 | 475 ns | 375 ns | ~375 ns | **-21.1%** ✅ | ~0% |

### Summary

**C++17 Refactoring (vs Baseline):**
- **Matrix creation**: ~11% faster
- **Vector to Matrix**: ~38-55% faster (major improvement!)
- **cv::Mat to Matrix**: ~20% faster

**C++20 std::span (vs C++17 Refactored):**
- **Matrix creation**: ~1-7% faster
- **Vector to Matrix**: ~20-66% faster (additional major improvement!)
- **cv::Mat to Matrix**: ~11% faster

**Total Improvement (Baseline → C++20):**
- **Matrix creation**: ~12-18% faster
- **Vector to Matrix**: ~51-85% faster 🚀
- **cv::Mat to Matrix**: ~20-30% faster

Full results available in JSON format:
- `results/baseline.json` - Before refactoring (C++17)
- `results/refactored.json` - After C++17 refactoring
- `results/cpp20_span.json` - C++20 with std::span

---

## How to Run Benchmarks

```bash
# Build with MSVC
python build_ctk.py --msvc

# Run matrices benchmark (ensure DLLs in PATH)
$env:PATH = "D:\playground\opencv\build\bin\Release;D:\playground\benchmark\install\bin;" + $env:PATH
.\build-msvc\benchmark\matrices\Release\matrixbench.exe --benchmark_format=console
```
