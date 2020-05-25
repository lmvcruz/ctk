#ifndef CTKABSTRACTMATRIX_H
#define CTKABSTRACTMATRIX_H

#include <string>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

namespace ctk {

class invalid_type: public std::exception
{
    virtual const char* what() const noexcept
    {
        return "Invalid type";
    }
};

/**
 *  @brief CtkAbstractMatrix TODO
 */
template<class T>
class AbstractMatrix
{
protected:
    /**
     * @brief type TODO
     */
    int type;

    /**
     * @brief ch_size TODO
     */
    int ch_size;

    /**
     * @brief data TODO
     */
    cv::Mat data;

public:
    /**
     * @brief CtkAbstractMatrix TODO
     */
    AbstractMatrix() {
        type = -1;
        ch_size = -1;
    }

    /**
     * @brief AbstractMatrix TODO
     * @param d TODO
     */
    AbstractMatrix(cv::Mat& d) {
        type = d.type();
        ch_size = d.channels();
        data = d.clone();
    }

    /**
     * @brief AbstractMatrix TODO
     * @param that TODO
     */
    AbstractMatrix(const AbstractMatrix& that) {
        type = that.type;
        ch_size = that.ch_size;
        data = that.data.clone();
    }

    /**
     * @brief ~CtkAbstractMatrix TODO
     */
    virtual ~AbstractMatrix() {}

    /**
     * @brief create TODO
     * @param w TODO
     * @param h TODO
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
     * @brief Create
     * @param w
     * @param h
     * @param vec
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
     * @brief get_data TODO
     * @return TODO
     */
    cv::Mat& get_data() {
        return data;
    }

    /**
     * @brief get_data TODO
     * @return TODO
     */
    const cv::Mat& get_data() const {
        return data;
    }

    /**
     * @brief cols TODO
     * @return  TODO
     */
    int cols() const{
        return data.cols;
    }

    /**
     * @brief width TODO
     * @return  TODO
     */
    int width()  const{
        return data.cols;
    }

    /**
     * @brief rows TODO
     * @return  TODO
     */
    int rows() const{
        return data.rows;
    }

    /**
     * @brief height TODO
     * @return  TODO
     */
    int height() const{
        return data.rows;
    }

    /**
     * @brief size TODO
     * @return  TODO
     */
    int size() const{
        return data.rows*data.cols;
    }

    /**
     * @brief channels TODO
     * @return  TODO
     */
    int channels() const{
        return ch_size;
    }

    /**
     * @brief checkChannel TODO
     * @return  TODO
     */
    bool CheckChannel() const{
        return (ch_size==data.channels());
    }

    /**
     * @brief get TODO
     * @param x TODO
     * @param y TODO
     * @return  TODO
     */
    virtual T get(int x, int y) const {
        return data.at<T>(y,x);
    }


    virtual T safe_get(int x, int y, T v) {
        if (x<0 || x>=data.cols || y<0 || y>=data.rows) {
            throw std::out_of_range("Exception thrown in AbstractMatyrix::safe_get");
        }
        return data.at<T>(y,x);
    }

    /**
     * @brief set TODO
     * @param x TODO
     * @param y TODO
     * @param v TODO
     */
    virtual void set(int x, int y, T v) {
        data.at<T>(y,x) = v;
    }

    /**
     * @brief safe_set
     * @param x
     * @param y
     * @param v
     */
    virtual void safe_set(int x, int y, T v) {
        if (x<0 || x>=data.cols || y<0 || y>=data.rows) {
            throw std::out_of_range("Exception thrown in AbstractMatyrix::safe_set");
        }
        data.at<T>(y,x) = v;
    }

    /**
     * @brief begin TODO
     * @return  TODO
     */
    T* begin() {
        return &data.at<T>(0,0);
    }

    /**
     * @brief end TODO
     * @return  TODO
     */
    T* end() {
        return &data.at<T>(data.rows*data.cols);
    }

    /**
     * @brief operator == TODO
     * @param that TODO
     * @return TODO
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
     * @brief operator == TODO
     * @param that TODO
     * @return TODO
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
