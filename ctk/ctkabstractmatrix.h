#ifndef CTKABSTRACTMATRIX_H
#define CTKABSTRACTMATRIX_H

#include <string>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include "ctkexceptions.h"

namespace ctk {

/**
 *  @brief CtkAbstractMatrix TODO
 */
template<class T>
class AbstractMatrix
{
protected:
    /**
     * @brief matrix elements type
     */
    int type;

    /**
     * @brief ch_size number of matrix channels
     */
    int ch_size;

    /**
     * @brief data matrix data
     */
    cv::Mat data;

public:
    /**
     * @brief Default Constructor
     */
    AbstractMatrix() {
        type = -1;
        ch_size = -1;
    }

    /**
     * @brief Parameterized Constructor
     * @param d Reference to a cv::Mat array
     */
    AbstractMatrix(cv::Mat& d) {
        type = d.type();
        ch_size = d.channels();
        data = d.clone();
    }

    /**
     * @brief Copy Constructor
     * @param that Reference to an existing AbstractMatrix object
     */
    AbstractMatrix(const AbstractMatrix& that) {
        type = that.type;
        ch_size = that.ch_size;
        data = that.data.clone();
    }

    /**
     * @brief ~CtkAbstractMatrix Destructor
     */
    virtual ~AbstractMatrix() {}

    /**
     * @brief Create  Create AbstractMatrix
     * @param w  int representing the number of cols
     * @param h  int representing the number of rows
     */
    virtual void Create(int w, int h) {
        if (w>0 && h>0) {
            if (type==-1) throw invalid_type();
            data = cv::Mat(h, w, type);
        }
        else if (w<0 || h<0) {
            throw std::bad_alloc();
        }
    }

    /**
     * @brief Create  Create AbstractMatrix
     * @param w  int representing the number of cols
     * @param h  int representing the number of rows
     * @param vec  vector with matrix elements
     */
    virtual void Create(int w, int h, std::vector<T> &vec) {
        if (w>0 && h>0) {
            if (type==-1) throw invalid_type();
            data = cv::Mat(h, w, type);
            int i=-1;
            for (auto it=begin(); it!=end(); ++it) *it = vec[++i];
        }
        else if (w<0 || h<0) {
            throw std::bad_alloc();
        }
    }

    /**
     * @brief get_data  Access matrix data
     * @return data
     */
    cv::Mat& get_data() {
        return data;
    }

    /**
     * @brief get_data  Access matrix data
     * @return data
     */
    const cv::Mat& get_data() const {
        return data;
    }

    /**
     * @brief cols  Get nº of columns in matrix
     * @return  nº of columns in matrix
     */
    int cols() const{
        return data.cols;
    }

    /**
     * @brief width  Get nº of columns in matrix
     * @return  nº of columns in matrix
     */
    int width()  const{
        return data.cols;
    }

    /**
     * @brief rows  Get nº of rows in matrix
     * @return nº of rows in matrix
     */
    int rows() const{
        return data.rows;
    }

    /**
     * @brief height  Get nº of rows in matrix
     * @return nº of rows in matrix
     */
    int height() const{
        return data.rows;
    }

    /**
     * @brief size   Get matrix size
     * @return  matrix size (nº of rows x nº of columns
     */
    int size() const{
        return data.rows*data.cols;
    }

    /**
     * @brief channels  Get nº of channels in matrix
     * @return  nº of channels in matrix
     */
    int channels() const{
        return ch_size;
    }

    /**
     * @brief checkChannel  Check if ch_size parameter is correctly assigned
     * @return  Boolean true if ch_size corresponds to number of channels in matrix.
     */
    bool CheckChannel() const{
        return (ch_size==data.channels());
    }

    /**
     * @brief Fill Fill all elements of the matrix according to the received parameter
     * @param v value used to fill the matrix
     */
    void Fill(T v) { //TODO: test and benchmark this method
        for (auto it=begin(); it!=end(); ++it) *it = v;
    }

    /**
     * @brief get  Get a specific matrix element
     * @param x  int representing the column index
     * @param y  int representing the row index
     * @return  Matrix element at row y and column x
     */
    virtual T get(int x, int y) const {
        return data.at<T>(y,x);
    }


    /**
     * @brief safe_get   Get a specific matrix element with protections
     * @param x  int representing the column index
     * @param y  int representing the row index
     * @return  Matrix element at row y and column x
     */
    virtual T safe_get(int x, int y) {
        if (x<0 || x>=data.cols || y<0 || y>=data.rows) {
            throw std::out_of_range("Exception thrown in AbstractMatyrix::safe_get");
        }
        return data.at<T>(y,x);
    }

    /**
     * @brief set  Setting the value of a specific matrix element
     * @param x  int representing the column index
     * @param y  int representing the row index
     * @param v  desired value
     */
    virtual void set(int x, int y, T v) {
        data.at<T>(y,x) = v;
    }

    /**
     * @brief safe_set  Setting the value of a specific matrix element with protections
     * @param x  int representing the column index
     * @param y  int representing the row index
     * @param v  desired value
     */
    virtual void safe_set(int x, int y, T v) {
        if (x<0 || x>=data.cols || y<0 || y>=data.rows) {
            throw std::out_of_range("Exception thrown in AbstractMatyrix::safe_set");
        }
        data.at<T>(y,x) = v;
    }

    /**
     * @brief begin Get the first element of the matrix
     * @return  matrix element at position (0,0)
     */
    T* begin() {
        return &data.at<T>(0,0);
    }

    /**
     * @brief end Get the last element of the matrix
     * @return  matrix element at position (nº rows , nº columns)
     */
    T* end() {
        return &data.at<T>(data.rows*data.cols);
    }

    /**
     * @brief operator ==
     * @param that  reference to an existing AbstractMatrix
     * @return boolean, true if all elements in both AbstractMatrixes are equal.
     */
    bool operator==(const AbstractMatrix<T> &that) {
        if (data.rows!=that.rows()) return false;
        if (data.cols!=that.cols()) return false;
        for (auto y=0; y<data.rows; y++) {
            for (auto x=0; x<data.cols; x++) {
                if (data.at<T>(y,x)!=that.get(x,y)) return false;
            }
        }
        return true;
    }

    /**
     * @brief operator != TODO
     * @param that reference to an existing AbstractMatrix
     * @return boolean, false if all elements in both AbstractMatrixes are equal.
     */
    bool operator!=(const AbstractMatrix<T> &that) {
        return !(*this==that);
    }

    virtual void Open(std::string filename) = 0;
    virtual void Save(std::string filename) = 0;
    virtual void Show() = 0;
};
}

#endif // CTKABSTRACTMATRIX_H
