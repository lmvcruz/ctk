# AbstractMatrix Refactoring

This document tracks the planned improvements for `AbstractMatrix` class.

## Benchmarking Strategy

| Branch | Purpose |
|--------|---------|
| `dev/no_change` | Baseline benchmark (from develop, no refactoring) |
| `dev/refactor_abstract_matrix` | Refactored code benchmark |

Results are saved in `misc/abstract_matrix_refactoring/results/`.

---

## Planned Improvements

### 🔴 Critical (Safety)

- [ ] **Fix UB in `end()` iterator** - Currently accesses memory beyond bounds
- [ ] **Add const iterators** - `begin() const` and `end() const`
- [ ] **Rule of Five** - Add move constructor, move assignment, copy assignment

### 🟠 High Priority (Performance)

- [ ] **Use `cv::Mat::setTo()` for `Fill()`** - Replace element-by-element loop
- [ ] **Move semantics for cv::Mat constructor** - Avoid unnecessary copies
- [ ] **Member initializer lists** - Use in constructors instead of assignment

### 🟡 Medium Priority (Modern C++)

- [ ] **Add `noexcept`** - To getters and non-throwing methods
- [ ] **Add `[[nodiscard]]`** - To getters to prevent ignoring return values
- [ ] **Use `std::string_view`** - For `Open()` and `Save()` parameters

### 🔵 Low Priority (Code Quality)

- [ ] **Fix typo** - `"AbstractMatyrix"` → `"AbstractMatrix"` in exception messages
- [ ] **Use `std::span`** - For `Create()` vector parameter (C++20)
- [ ] **Use `size_t`** - For size-related return types

---

## Benchmark Results

### Baseline (dev/no_change)

```
[Results will be added after running benchmark]
```

### After Refactoring (dev/refactor_abstract_matrix)

```
[Results will be added after running benchmark]
```

---

## How to Run Benchmarks

```bash
# Build with MSVC
python build_ctk.py --msvc

# Run matrices benchmark
.\build-msvc\benchmark\matrices\Release\matrices.exe --benchmark_format=console
```
