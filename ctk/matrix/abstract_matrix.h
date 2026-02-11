#pragma once

#include <algorithm>
#include <iostream>
#include <span>
#include <string>
#include <string_view>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include "ctk/core/exceptions.h"

namespace ctk
{

    /**
     * @brief Abstract base class for matrix operations wrapping OpenCV's cv::Mat.
     *
     * AbstractMatrix provides a type-safe, modern C++ interface for matrix operations.
     * It serves as a base class for specialized matrix types (numeric, binary, image).
     *
     * @tparam T The element type stored in the matrix (e.g., double, float, uchar).
     *
     * @note This class follows the Rule of Five for proper resource management.
     * @note Derived classes must implement Open() and Save() for file I/O.
     *
     * @example
     * @code
     * class NumericMatrix : public AbstractMatrix<double> {
     *     // Implementation
     * };
     * @endcode
     */
    template <class T>
    class AbstractMatrix
    {
    protected:
        /**
         * @brief OpenCV type identifier for matrix elements.
         * @details Set to -1 by default (invalid). Must be set by derived classes
         *          before calling Create() (e.g., CV_64F for double, CV_8UC1 for uchar).
         */
        int type = -1;

        /**
         * @brief Number of channels in the matrix.
         * @details Typically 1 for grayscale/numeric, 3 for RGB, 4 for RGBA.
         */
        int ch_size = -1;

        /**
         * @brief Underlying OpenCV matrix storing the data.
         */
        cv::Mat data;

    public:
        /**
         * @brief Default constructor.
         * @details Creates an empty, uninitialized matrix. Call Create() to allocate.
         */
        AbstractMatrix() = default;

        /**
         * @brief Constructs a matrix by copying data from a cv::Mat.
         * @param d The source cv::Mat to copy from.
         * @note Creates a deep copy of the input matrix.
         */
        AbstractMatrix(const cv::Mat &d)
            : type(d.type()), ch_size(d.channels()), data(d.clone())
        {
        }

        /**
         * @brief Constructs a matrix by moving data from a cv::Mat.
         * @param d The source cv::Mat to move from.
         * @note Zero-copy operation; the source matrix becomes empty.
         */
        AbstractMatrix(cv::Mat &&d) noexcept
            : type(d.type()), ch_size(d.channels()), data(std::move(d))
        {
        }

        /**
         * @brief Copy constructor.
         * @param that The source AbstractMatrix to copy from.
         * @note Creates a deep copy of all matrix data.
         */
        AbstractMatrix(const AbstractMatrix &that)
            : type(that.type), ch_size(that.ch_size), data(that.data.clone())
        {
        }

        /**
         * @brief Move constructor.
         * @param that The source AbstractMatrix to move from.
         * @note Zero-copy operation; the source matrix becomes empty.
         */
        AbstractMatrix(AbstractMatrix &&that) noexcept
            : type(that.type), ch_size(that.ch_size), data(std::move(that.data))
        {
        }

        /**
         * @brief Copy assignment operator.
         * @param that The source AbstractMatrix to copy from.
         * @return Reference to this matrix.
         * @note Creates a deep copy; self-assignment is handled safely.
         */
        AbstractMatrix &operator=(const AbstractMatrix &that)
        {
            if (this != &that)
            {
                type = that.type;
                ch_size = that.ch_size;
                data = that.data.clone();
            }
            return *this;
        }

        /**
         * @brief Move assignment operator.
         * @param that The source AbstractMatrix to move from.
         * @return Reference to this matrix.
         * @note Zero-copy operation; self-assignment is handled safely.
         */
        AbstractMatrix &operator=(AbstractMatrix &&that) noexcept
        {
            if (this != &that)
            {
                type = that.type;
                ch_size = that.ch_size;
                data = std::move(that.data);
            }
            return *this;
        }

        /**
         * @brief Virtual destructor.
         * @details Default destructor; cv::Mat handles its own memory cleanup.
         */
        virtual ~AbstractMatrix() = default;

        /**
         * @brief Allocates matrix storage with specified dimensions.
         * @param w Width (number of columns). Must be positive.
         * @param h Height (number of rows). Must be positive.
         * @throws invalid_type If the matrix type has not been set (type == -1).
         * @throws std::bad_alloc If width or height is negative.
         * @note If both w and h are zero, no allocation occurs.
         */
        virtual void Create(int w, int h)
        {
            if (w > 0 && h > 0)
            {
                if (type == -1)
                    throw invalid_type();
                data = cv::Mat(h, w, type);
            }
            else if (w < 0 || h < 0)
            {
                throw std::bad_alloc();
            }
        }

        /**
         * @brief Allocates matrix and initializes with values from a span.
         * @param w Width (number of columns). Must be positive.
         * @param h Height (number of rows). Must be positive.
         * @param values Span containing initial values in row-major order.
         * @throws invalid_type If the matrix type has not been set.
         * @throws std::bad_alloc If width or height is negative.
         * @warning The span must contain at least w*h elements.
         * @note Accepts any contiguous container (vector, array, C-array) via implicit conversion.
         */
        virtual void Create(int w, int h, std::span<const T> values)
        {
            if (w > 0 && h > 0)
            {
                if (type == -1)
                    throw invalid_type();
                data = cv::Mat(h, w, type);
                const auto count = static_cast<size_t>(w * h);
                std::copy_n(values.data(), std::min(count, values.size()), begin());
            }
            else if (w < 0 || h < 0)
            {
                throw std::bad_alloc();
            }
        }

        /**
         * @brief Returns a mutable reference to the underlying cv::Mat.
         * @return Reference to the internal cv::Mat data.
         * @warning Direct modification may invalidate internal state.
         */
        cv::Mat &GetData()
        {
            return data;
        }

        /**
         * @brief Returns a const reference to the underlying cv::Mat.
         * @return Const reference to the internal cv::Mat data.
         */
        const cv::Mat &GetData() const
        {
            return data;
        }

        /**
         * @brief Returns the number of columns.
         * @return Column count (width).
         */
        [[nodiscard]] int GetCols() const noexcept
        {
            return data.cols;
        }

        /**
         * @brief Returns the matrix width (alias for GetCols).
         * @return Width in pixels/elements.
         */
        [[nodiscard]] int GetWidth() const noexcept
        {
            return data.cols;
        }

        /**
         * @brief Returns the number of rows.
         * @return Row count (height).
         */
        [[nodiscard]] int GetRows() const noexcept
        {
            return data.rows;
        }

        /**
         * @brief Returns the matrix height (alias for GetRows).
         * @return Height in pixels/elements.
         */
        [[nodiscard]] int GetHeight() const noexcept
        {
            return data.rows;
        }

        /**
         * @brief Returns the total number of elements.
         * @return Total element count (rows * cols).
         */
        [[nodiscard]] int GetSize() const noexcept
        {
            return data.rows * data.cols;
        }

        /**
         * @brief Returns the number of channels.
         * @return Channel count (1 for grayscale, 3 for RGB, etc.).
         */
        [[nodiscard]] int GetChannels() const noexcept
        {
            return ch_size;
        }

        /**
         * @brief Validates channel count consistency.
         * @return True if stored channel count matches actual cv::Mat channels.
         */
        [[nodiscard]] bool CheckChannel() const noexcept
        {
            return ch_size == data.channels();
        }

        /**
         * @brief Fills the entire matrix with a single value.
         * @param v The value to fill with.
         */
        virtual void Fill(T v)
        {
            std::fill(begin(), end(), v);
        }

        /**
         * @brief Retrieves an element at the specified position (unchecked).
         * @param x Column index (0-based).
         * @param y Row index (0-based).
         * @return The element value at position (x, y).
         * @warning No bounds checking; undefined behavior if out of range.
         * @see SafeGet() for bounds-checked access.
         */
        virtual T Get(int x, int y) const
        {
            return data.at<T>(y, x);
        }

        /**
         * @brief Retrieves an element with bounds checking.
         * @param x Column index (0-based).
         * @param y Row index (0-based).
         * @return The element value at position (x, y).
         * @throws std::out_of_range If indices are out of bounds.
         */
        virtual T SafeGet(int x, int y) const
        {
            if (x < 0 || x >= data.cols || y < 0 || y >= data.rows)
            {
                throw std::out_of_range("Exception thrown in AbstractMatrix::SafeGet");
            }
            return data.at<T>(y, x);
        }

        /**
         * @brief Sets an element at the specified position (unchecked).
         * @param x Column index (0-based).
         * @param y Row index (0-based).
         * @param v The value to set.
         * @warning No bounds checking; undefined behavior if out of range.
         * @see SafeSet() for bounds-checked access.
         */
        virtual void Set(int x, int y, T v)
        {
            data.at<T>(y, x) = v;
        }

        /**
         * @brief Sets an element with bounds checking.
         * @param x Column index (0-based).
         * @param y Row index (0-based).
         * @param v The value to set.
         * @throws std::out_of_range If indices are out of bounds.
         */
        virtual void SafeSet(int x, int y, T v)
        {
            if (x < 0 || x >= data.cols || y < 0 || y >= data.rows)
            {
                throw std::out_of_range("Exception thrown in AbstractMatrix::SafeSet");
            }
            data.at<T>(y, x) = v;
        }

        /**
         * @brief Returns an iterator to the beginning.
         * @return Pointer to the first element.
         */
        T *begin() noexcept
        {
            return data.ptr<T>(0);
        }

        /**
         * @brief Returns a const iterator to the beginning.
         * @return Const pointer to the first element.
         */
        const T *begin() const noexcept
        {
            return data.ptr<T>(0);
        }

        /**
         * @brief Returns an iterator to the end.
         * @return Pointer to one past the last element.
         */
        T *end() noexcept
        {
            return data.ptr<T>(0) + (data.rows * data.cols);
        }

        /**
         * @brief Returns a const iterator to the end.
         * @return Const pointer to one past the last element.
         */
        const T *end() const noexcept
        {
            return data.ptr<T>(0) + (data.rows * data.cols);
        }

        /**
         * @brief Equality comparison operator.
         * @param that The matrix to compare with.
         * @return True if dimensions and all elements are equal.
         */
        bool operator==(const AbstractMatrix<T> &that) const
        {
            if (data.rows != that.GetRows())
                return false;
            if (data.cols != that.GetCols())
                return false;
            for (auto y = 0; y < data.rows; ++y)
            {
                for (auto x = 0; x < data.cols; ++x)
                {
                    if (data.at<T>(y, x) != that.Get(x, y))
                        return false;
                }
            }
            return true;
        }

        /**
         * @brief Inequality comparison operator.
         * @param that The matrix to compare with.
         * @return True if dimensions or any elements differ.
         */
        bool operator!=(const AbstractMatrix<T> &that) const
        {
            return !(*this == that);
        }

        /**
         * @brief Loads matrix data from a file.
         * @param filename Path to the input file.
         * @note Pure virtual; must be implemented by derived classes.
         */
        virtual void Open(std::string_view filename) = 0;

        /**
         * @brief Saves matrix data to a file.
         * @param filename Path to the output file.
         * @note Pure virtual; must be implemented by derived classes.
         */
        virtual void Save(std::string_view filename) const = 0;
    };

}
