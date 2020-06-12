#include "ctkbinarymatrix.h"

#include <iostream>

namespace ctk {

/**
 * @brief BinaryMatrix::BinaryMatrix Default Constructor
 */
BinaryMatrix::BinaryMatrix()
{
    type = CV_8U; // 8-bit unsigned integers ( 0..255 )
    ch_size = 1;
}


/**
 * @brief BinaryMatrix::BinaryMatrix  Copy constructor
 * @param that reference to an existing BinaryMatrix object
 */
BinaryMatrix::BinaryMatrix(const BinaryMatrix &that)
{
    assert(that.data.type()==CV_8U && that.data.channels()==1);
    type = that.type;
    ch_size = that.ch_size;
    data = that.data.clone();
}


/**
 * @brief BinaryMatrix::BinaryMatrix Copy constructor
 * @param that  reference to an existing AbstractMatrix object
 */
BinaryMatrix::BinaryMatrix(const AbstractMatrix<bool> &that)
{
    assert(that.get_data().type()==CV_8U
           && that.get_data().channels()==1);
    type = CV_8U;
    ch_size = 1;
    data = that.get_data().clone();
}

BinaryMatrix::BinaryMatrix(cv::Mat &d): AbstractMatrix<bool>(d){
    assert(d.type()==CV_8U && d.channels()==1);
}

/**
 * @brief BinaryMatrix::BinaryMatrix Parameterized Constructor
 * @param w number of rows
 * @param h number of columns
 * @param d vector of booleans with matrix elements
 */
BinaryMatrix::BinaryMatrix(int w, int h, std::vector<bool> &d)
{
    type = CV_8U;
    ch_size = 1;
    Create(w, h, d);
}

/**
 * @brief BinaryMatrix::operator =
 * @param that  reference to an existing AbstractMatrix object
 * @return Updated Binary Matrix
 */
BinaryMatrix &BinaryMatrix::operator=(const BinaryMatrix &that)
{
    assert(that.data.type()==CV_8U && that.data.channels()==1);
    type = that.type;
    ch_size = that.ch_size;
    data = that.data.clone();
    return *this;
}


/**
 * @brief BinaryMatrix::set set a value in the matrix
 * @param x int representing the column index
 * @param y int representing the row index
 * @param v desired value
 */
void BinaryMatrix::set(int x, int y, bool v)
{
    data.at<uchar>(y,x) = v*255;
}


/**
 * @brief BinaryMatrix::get Get matrix element
 * @param x  int representing the column index
 * @param y  int representing the row index
 * @return matrix element at position (y,x)
 */
bool BinaryMatrix::get(int x, int y)
{
    return (static_cast<int>(data.at<uchar>(y,x))>128);
}


/**
 * @brief BinaryMatrix::Not
 * @return BinaryMatrix were all elements correspond to 1-Original Matrix (Negative Matrix)
 */
BinaryMatrix BinaryMatrix::Not()
{
    BinaryMatrix aux(*this);
    for (int x=0; x<data.cols; x++) {
        for(int y=0; y<data.rows; y++) {
            aux.set(x,y, 1-get(x,y)); //TODO NÃO DEVIA SER set(y,x, 1-get(y,x))??
        }
    }
    return aux;
}


/**
 * @brief BinaryMatrix::And  which yields true if both its operands are true, and false otherwise.
 * @param that  reference to an existing AbstractMatrix object
 * @return  BinaryMatrix resulting from the operation
 */
BinaryMatrix BinaryMatrix::And(BinaryMatrix &that)
{
    BinaryMatrix aux(*this);
    for (int x=0; x<data.cols; x++) {
        for(int y=0; y<data.rows; y++) {
            aux.set(x,y, get(x,y)&&that.get(x,y));
        }
    }
    return aux;
}


/**
 * @brief BinaryMatrix::Or   yields true if either of its operands is true, thus being false only when both operands are false.
 * @param that  reference to an existing AbstractMatrix object
 * @return  BinaryMatrix resulting from the operation
 */
BinaryMatrix BinaryMatrix::Or(BinaryMatrix &that)
{
    BinaryMatrix aux(*this);
    for (int x=0; x<data.cols; x++) {
        for(int y=0; y<data.rows; y++) {
            aux.set(x,y, get(x,y)||that.get(x,y));
        }
    }
    return aux;
}


/**
 * @brief BinaryMatrix::Xor  XOR is true only when an odd number of inputs are true and false otherwise
 * @param that  reference to an existing AbstractMatrix object
 * @return BinaryMatrix resulting from the operation
 */
BinaryMatrix BinaryMatrix::Xor(BinaryMatrix &that)
{
    BinaryMatrix aux(*this);
    for (int x=0; x<data.cols; x++) {
        for(int y=0; y<data.rows; y++) {
            aux.set(x,y, get(x,y)^that.get(x,y));
        }
    }
    return aux;
}

/**
 * @brief BinaryMatrix::countTrues
 * @return int representing the number of true elements in the Binary Matrix
 */
int BinaryMatrix::countTrues()
{
    int count = 0;
    for (int x=0; x<data.cols; x++) {
        for(int y=0; y<data.rows; y++) {
            if (get(x,y)) count++;
        }
    }
    return count;
}


/**
 * @brief BinaryMatrix::countFalses
 * @return int representing the number of false elements in the Binary Matrix
 */
int BinaryMatrix::countFalses()
{
    int count = 0;
    for (int x=0; x<data.cols; x++) {
        for(int y=0; y<data.rows; y++) {
            if (!get(x,y)) count++;
        }
    }
    return count;
}


/**
 * @brief BinaryMatrix::Erode
 * @param size int representing the size of the structuring element
 * @param etype  int representing the shape of the structuring element
 * @return Eroded Binary Matrix
 */
BinaryMatrix BinaryMatrix::Erode(int size, int etype)
{
    cv::Size elsize(2*size+1, 2*size+1);
    cv::Mat element = getStructuringElement(etype, elsize, cv::Point(size,size));
    BinaryMatrix aux;
    cv::erode(data, aux.data, element);
    return aux;
}


/**
 * @brief BinaryMatrix::SelfErode
 * @param size  int representing the size of the structuring element
 * @param etype  int representing the shape of the structuring element
 */
void BinaryMatrix::SelfErode(int size, int etype)
{
    cv::Size elsize(2*size+1, 2*size+1);
    cv::Mat element = getStructuringElement(etype, elsize, cv::Point(size,size));
    cv::erode(data, data, element);
}


/**
 * @brief BinaryMatrix::Dilate
 * @param size  int representing the size of the structuring element
 * @param etype  int representing the type of the structuring element
 * @return Dilated Binary Matrix
 */
BinaryMatrix BinaryMatrix::Dilate(int size, int etype)
{
    cv::Size elsize(2*size+1, 2*size+1);
    cv::Mat element = getStructuringElement(etype, elsize, cv::Point(size,size));
    BinaryMatrix aux;
    cv::dilate(data, aux.data, element);
    return aux;
}


/**
 * @brief BinaryMatrix::SelfDilate
 * @param size  int representing the size of the structuring element
 * @param etype  int representing the type of the structuring element
 */
void BinaryMatrix::SelfDilate(int size, int etype)
{
    cv::Size elsize(2*size+1, 2*size+1);
    cv::Mat element = getStructuringElement(etype, elsize, cv::Point(size,size));
    cv::dilate(data, data, element);
}


/**
 * @brief BinaryMatrix::Open read data in the file into BinaryMatrix
 * @param filename
 */
void BinaryMatrix::Open(std::string filename) {
    AbstractMatrix<bool>::data = cv::imread(filename, cv::IMREAD_UNCHANGED);
}


/**
 * @brief BinaryMatrix::Save save BinaryMatrix data to file
 * @param filename
 */
void BinaryMatrix::Save(std::string filename) {
    cv::imwrite(filename, AbstractMatrix<bool>::data);
}


/**
 * @brief BinaryMatrix::Show show BinaryMatrix
 */
void BinaryMatrix::Show() {
    std::cout << "TODO" << std::endl;


}




}
