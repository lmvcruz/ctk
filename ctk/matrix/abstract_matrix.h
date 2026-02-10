#pragma once

#include <string>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include "ctk/core/exceptions.h"

namespace ctk
{

    /**
     *  @brief CtkAbstractMatrix TODO
     */
    template <class T>
    class AbstractMatrix
    {
    protected:
        /**
         * @brief AbstractMatrix elements type
         */
        int type = -1;

        /**
         * @brief ch_size number of AbstractMatrix channels
         */
        int ch_size = -1;

        /**
         * @brief data AbstractMatrix data
         */
        cv::Mat data;

    public:
        /**
         * @brief Default Constructor
         */
        AbstractMatrix() = default;

        /**
         * @brief Parameterized Constructor
         * @param d Reference to a cv::Mat array
         */
        AbstractMatrix(const cv::Mat &d)
            : type(d.type()), ch_size(d.channels()), data(d.clone())
        {
        }

        /**
         * @brief Move Constructor for cv::Mat
         * @param d Rvalue reference to a cv::Mat array
         */
        AbstractMatrix(cv::Mat &&d) noexcept
            : type(d.type()), ch_size(d.channels()), data(std::move(d))
        {
        }

        /**
         * @brief Copy Constructor
         * @param that Reference to an existing AbstractMatrix
         */
        AbstractMatrix(const AbstractMatrix &that)
            : type(that.type), ch_size(that.ch_size), data(that.data.clone())
        {
        }

        /**
         * @brief Move Constructor
         * @param that Rvalue reference to an existing AbstractMatrix
         */
        AbstractMatrix(AbstractMatrix &&that) noexcept
            : type(that.type), ch_size(that.ch_size), data(std::move(that.data))
        {
        }

        /**
         * @brief Copy Assignment Operator
         * @param that Reference to an existing AbstractMatrix
         * @return Reference to this AbstractMatrix
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
         * @brief Move Assignment Operator
         * @param that Rvalue reference to an existing AbstractMatrix
         * @return Reference to this AbstractMatrix
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
         * @brief ~CtkAbstractMatrix Destructor
         */
        virtual ~AbstractMatrix() = default;

        /**
         * @brief Create  Create AbstractMatrix
         * @param w  int representing the number of cols
         * @param h  int representing the number of rows
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
         * @brief Create  Create AbstractMatrix
         * @param w  int representing the number of cols
         * @param h  int representing the number of rows
         * @param vec  vector with AbstractMatrix elements
         */
        virtual void Create(int w, int h, const std::vector<T> &vec)
        {
            if (w > 0 && h > 0)
            {
                if (type == -1)
                    throw invalid_type();
                data = cv::Mat(h, w, type);
                int i = -1;
                for (auto it = begin(); it != end(); ++it)
                    *it = vec[++i];
            }
            else if (w < 0 || h < 0)
            {
                throw std::bad_alloc();
            }
        }

        /**
         * @brief GetData  Access AbstractMatrix data
         * @return data
         */
        cv::Mat &GetData()
        {
            return data;
        }

        /**
         * @brief GetData  Access AbstractMatrix data
         * @return data
         */
        const cv::Mat &GetData() const
        {
            return data;
        }

        /**
         * @brief cols  Get number of columns
         * @return  int representing the number of columns
         */
        [[nodiscard]] int GetCols() const noexcept
        {
            return data.cols;
        }

        /**
         * @brief width  Get AbstractMatrix width (number of columns)
         * @return int representing the number columns in matrix
         */
        [[nodiscard]] int GetWidth() const noexcept
        {
            return data.cols;
        }

        /**
         * @brief GetRows  Get number of rows
         * @return int representing the number of rows
         */
        [[nodiscard]] int GetRows() const noexcept
        {
            return data.rows;
        }

        /**
         * @brief GetHeight  Get AbstractMatrix height (number of rows)
         * @return int representing the number of rows
         */
        [[nodiscard]] int GetHeight() const noexcept
        {
            return data.rows;
        }

        /**
         * @brief size   Get AbstractMatrix size
         * @return int representing matrix size (nº of rows x nº of columns)
         */
        [[nodiscard]] int GetSize() const noexcept
        {
            return data.rows * data.cols;
        }

        /**
         * @brief channels  Get number of channels
         * @return int representing the number of channels in matrix
         */
        [[nodiscard]] int GetChannels() const noexcept
        {
            return ch_size;
        }

        /**
         * @brief checkChannel  Check if ch_size parameter is correctly assigned
         * @return  boolean true if ch_size corresponds to number of channels in AbstractMatrix.
         */
        [[nodiscard]] bool CheckChannel() const noexcept
        {
            return ch_size == data.channels();
        }

        /**
         * @brief Fill Fill all elements of the AbstractMatrix according to the received parameter
         * @param v value used to fill the AbstractMatrix
         */
        virtual void Fill(T v)
        { // TODO: test and benchmark this method
            for (auto it = begin(); it != end(); ++it)
                *it = v;
        }

        /**
         * @brief Get  Get a specific AbstractMatrix element
         * @param x  int representing the column index
         * @param y  int representing the row index
         * @return  AbstractMatrix element at row y and column x
         */
        virtual T Get(int x, int y) const
        {
            return data.at<T>(y, x);
        }

        /**
         * @brief SafeGet   Get a specific AbstractMatrix element with protections
         * @param x  int representing the column index
         * @param y  int representing the row index
         * @return  AbstractMatrix element at row y and column x
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
         * @brief Set  Setting the value of a specific AbstractMatrix element
         * @param x  int representing the column index
         * @param y  int representing the row index
         * @param v  desired value
         */
        virtual void Set(int x, int y, T v)
        {
            data.at<T>(y, x) = v;
        }

        /**
         * @brief SafeSet  Setting the value of a specific AbstractMatrix element with protections
         * @param x  int representing the column index
         * @param y  int representing the row index
         * @param v  desired value
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
         * @brief begin Get the first element of the AbstractMatrix
         * @return  Pointer to first AbstractMatrix element
         */
        T *begin() noexcept
        {
            return data.ptr<T>(0);
        }

        /**
         * @brief begin Get the first element of the AbstractMatrix (const version)
         * @return  Const pointer to first AbstractMatrix element
         */
        const T *begin() const noexcept
        {
            return data.ptr<T>(0);
        }

        /**
         * @brief end Get past-the-end pointer of the AbstractMatrix
         * @return  Pointer to one past the last element
         */
        T *end() noexcept
        {
            return data.ptr<T>(0) + (data.rows * data.cols);
        }

        /**
         * @brief end Get past-the-end pointer of the AbstractMatrix (const version)
         * @return  Const pointer to one past the last element
         */
        const T *end() const noexcept
        {
            return data.ptr<T>(0) + (data.rows * data.cols);
        }

        /**
         * @brief operator ==
         * @param that  reference to an existing AbstractMatrix
         * @return boolean, true if all elements in both AbstractMatrixes are equal.
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
         * @brief operator != TODO
         * @param that reference to an existing AbstractMatrix
         * @return boolean, false if all elements in both AbstractMatrixes are equal.
         */
        bool operator!=(const AbstractMatrix<T> &that) const
        {
            return !(*this == that);
        }

        virtual void Open(std::string filename) = 0;
        virtual void Save(std::string filename) const = 0;
    };

}
