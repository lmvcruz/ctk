# AbstractMatrix Refactoring

This document tracks improvements for the `AbstractMatrix` class.

## Benchmarking Strategy

| Branch | Purpose |
|--------|---------|
| `dev/no_change` | Baseline benchmark (from develop, no refactoring) |
| `dev/refactor_abstract_matrix` | Refactored code benchmark |

Results are saved in `misc/abstract_matrix_refactoring/results/`.

---

## Implemented Improvements

### 🔴 Critical (Safety)

- [x] **Fix UB in `end()` iterator** - Use `ptr<T>() + size` instead of `at<T>(size)`
- [x] **Add const iterators** - `begin() const` and `end() const`
- [x] **Rule of Five** - Added move constructor, move assignment, copy assignment

### 🟠 High Priority (Performance)

- [ ] **Use `cv::Mat::setTo()` for `Fill()`** - Replace element-by-element loop (future)
- [x] **Move semantics for cv::Mat constructor** - Added `AbstractMatrix(cv::Mat&&)`
- [x] **Member initializer lists** - All constructors now use init lists

### 🟡 Medium Priority (Modern C++)

- [x] **Add `noexcept`** - To getters and non-throwing methods
- [x] **Add `[[nodiscard]]`** - To getters to prevent ignoring return values
- [ ] **Use `std::string_view`** - For `Open()` and `Save()` parameters (future)

### 🔵 Low Priority (Code Quality)

- [x] **Fix typo** - `"AbstractMatyrix"` → `"AbstractMatrix"` in exception messages
- [ ] **Use `std::span`** - For `Create()` vector parameter (C++20, future)
- [ ] **Use `size_t`** - For size-related return types (future)

---

## Benchmark Results Comparison

### Key Benchmarks (Time in ns, lower is better)

| Benchmark | Baseline | Refactored | Change |
|-----------|----------|------------|--------|
| NM_CreateNumericMatrix/8/8 | 1244 ns | 1099 ns | **-11.7%** ✅ |
| NM_CreateNumericMatrix/32/32 | 16029 ns | 14218 ns | **-11.3%** ✅ |
| NM_Vec2NumericMatrix/8/8 | 357 ns | 222 ns | **-37.8%** ✅ |
| NM_Vec2NumericMatrix/32/32 | 1867 ns | 830 ns | **-55.5%** ✅ |
| NM_CvMat2NumericMatrix/8/8 | 335 ns | 269 ns | **-19.7%** ✅ |
| NM_CvMat2NumericMatrix/32/32 | 475 ns | 375 ns | **-21.1%** ✅ |
| NM_Sum/8 | 996 ns | 792 ns | **-20.5%** ✅ |
| NM_Diff/32 | 1649 ns | 1160 ns | **-29.7%** ✅ |

### Summary

- **Matrix creation**: ~11% faster
- **Vector to Matrix**: ~38-55% faster (major improvement!)
- **cv::Mat to Matrix**: ~20% faster
- **Arithmetic operations**: ~20-30% faster

Full results available in JSON format:
- `results/baseline.json` - Before refactoring
- `results/refactored.json` - After refactoring

---

## How to Run Benchmarks

```bash
# Build with MSVC
python build_ctk.py --msvc

# Run matrices benchmark (ensure DLLs in PATH)
$env:PATH = "D:\playground\opencv\build\bin\Release;D:\playground\benchmark\install\bin;" + $env:PATH
.\build-msvc\benchmark\matrices\Release\matrixbench.exe --benchmark_format=console
```
