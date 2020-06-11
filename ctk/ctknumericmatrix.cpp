#include "ctknumericmatrix.h"

#include <iostream>
#include <iomanip>

#include <opencv2/highgui.hpp>

namespace ctk {

/**
 * @brief NumericMatrix::NumericMatrix Default Constructor
 */
NumericMatrix::NumericMatrix()
{
    type = CV_64F;
    ch_size = 1;
}

/**
 * @brief NumericMatrix::NumericMatrix
 * @param d
 */
NumericMatrix::NumericMatrix(cv::Mat &d) : AbstractMatrix<double>(d){
    assert(d.type()==CV_64F && d.channels()==1);
}

/**
 * @brief NumericMatrix::NumericMatrix Parameterized Constructor
 * @param w  int indicating the number of rows
 * @param h  int indicating the number of columns
 * @param d  vector of double with matrix elements
 */
NumericMatrix::NumericMatrix(int w, int h, std::vector<double> &d)
{
    type = CV_64F;
    ch_size = 1;
    Create(w, h);
    //
    int i=-1;
    for (auto it=begin(); it!=end(); ++it) *it = d[++i];
}


/**
 * @brief NumericMatrix::NumericMatrix  Copy Constructor
 * @param that  Reference to an existing NumericMatrix object
 */
NumericMatrix::NumericMatrix(const NumericMatrix &that)
{
    assert(that.data.type()==CV_64F && that.data.channels()==1);
    type = that.type;
    ch_size = that.ch_size;
    data = that.data.clone();
}


/**
 * @brief NumericMatrix::operator =
 * @param that  Reference to an existing NumericMatrix object
 * @return Updated NumericMatrix
 */
NumericMatrix &NumericMatrix::operator=(const NumericMatrix &that)
{
    assert(that.data.type()==CV_64F && that.data.channels()==1);
    type = that.type;
    ch_size = that.ch_size;
    data = that.data.clone();
    return *this;
}


/**
 * @brief NumericMatrix::Create  Create NumericMatrix
 * @param w  int indicating the number of rows
 * @param h  int indicating the number of coumns
 * @param vec  vector of ints with matrix elements
 */
void NumericMatrix::Create(int w, int h, std::vector<int> &vec) {
    if (w>0 && h>0) {
        if (type==-1) throw invalid_type();
        data = cv::Mat(h, w, type);
        int i=-1;
        for (auto it=begin(); it!=end(); ++it)
            *it = static_cast<double>(vec[++i]);
    }
    else if (w<0 || h<0) {
        throw std::bad_alloc();
    }
}


/**
 * @brief NumericMatrix::Open  Read data from a file into the NumeriMatrix
 * @param filename
 */
void NumericMatrix::Open(std::string filename)
{
    data = cv::imread(filename, cv::IMREAD_ANYDEPTH);
}

/**
 * @brief NumericMatrix::Save  Save data of the numeric matrix into a file
 * @param filename
 */
void NumericMatrix::Save(std::string filename)
{
    cv::imwrite(filename, data);
}


/**
 * @brief NumericMatrix::Show  Print elements in the Numeric Matrix
 */
void NumericMatrix::Show()
{
    for (int y=0; y<data.rows; y++) {
        std::cout << "{";
        for (int x=0; x<data.cols; x++) {
            std::cout << std::setprecision(3) << data.at<double>(y,x);
            if (x<data.cols-1) std::cout << ", ";
        }
        std::cout << "}" << std::endl;
    }
}


/**
 * @brief NumericMatrix::operator +
 * @param that  Reference to an existing NumericMatrix object
 * @return NumericMatrix resulting from the sum with the passed matrix
 */
NumericMatrix NumericMatrix::operator+(const NumericMatrix &that) {
    cv::Mat res = data + that.data;
    return NumericMatrix(res);
}

/**
 * @brief NumericMatrix::operator +=
 * @param that Reference to an existing NumericMatrix object
 */
void NumericMatrix::operator+=(const NumericMatrix &that)
{
    data += that.data;
}


/**
 * @brief NumericMatrix::operator -
 * @param that  Reference to an existing NumericMatrix object
 * @return NumericMatrix resulting from the subtraction with the passed matrix
 */
NumericMatrix NumericMatrix::operator-(const NumericMatrix &that)
{
    cv::Mat res = data - that.data;
    return NumericMatrix(res);
}

/**
 * @brief NumericMatrix::operator -=
 * @param that Reference to an existing NumericMatrix object
 */
void NumericMatrix::operator-=(const NumericMatrix &that)
{
    data -= that.data;
}


/**
 * @brief NumericMatrix::operator *
 * @param that  Reference to an existing NumericMatrix object
 * @return NumericMatrix resulting from the multiplication with the passed matrix
 */
NumericMatrix NumericMatrix::operator*(const NumericMatrix &that)
{
    assert(data.cols==that.rows());
    cv::Mat res = data * that.data;
    return NumericMatrix(res);
}

/**
 * @brief NumericMatrix::operator *=
 * @param that  Reference to an existing NumericMatrix object
 */
void NumericMatrix::operator*=(const NumericMatrix &that)
{
    assert(data.cols==that.rows());
    data *= that.data;
}


/**
 * @brief NumericMatrix::operator /
 * @param that  Reference to an existing NumericMatrix object
 * @return NumericMatrix resulting from the division with the passed matrix
 */
NumericMatrix NumericMatrix::operator/(const NumericMatrix &that)
{
    assert(data.cols==that.rows());
    assert(that.cols()==that.rows() && that.cols()>0);
    assert(std::fabs(cv::determinant(that.data))>FLT_EPSILON);
    cv::Mat res = data * that.data.inv();
    return NumericMatrix(res);
}

/**
 * @brief NumericMatrix::operator /=
 * @param that  Reference to an existing NumericMatrix object
 */
void NumericMatrix::operator/=(const NumericMatrix &that)
{
    assert(data.cols==that.rows());
    assert(that.cols()==that.rows() && that.cols()>0);
    assert(std::fabs(cv::determinant(that.data))>FLT_EPSILON);
    data *= that.data.inv();
}


/**
 * @brief NumericMatrix::operator +
 * @param v  double constant
 * @return NumericMatrix resulting from the addition of v to each element in the matrix
 */
NumericMatrix NumericMatrix::operator+(const double v)
{
    cv::Mat res = data + v;
    return NumericMatrix(res);
}


/**
 * @brief NumericMatrix::operator +=
 * @param v double constant
 */
void NumericMatrix::operator+=(const double v)
{
    data += v;
}


/**
 * @brief NumericMatrix::operator -
 * @param v double constant
 * @return  NumericMatrix resulting from the subtraction of v to each element in the matrix
 */
NumericMatrix NumericMatrix::operator-(const double v)
{
    cv::Mat res = data - v;
    return NumericMatrix(res);
}


/**
 * @brief NumericMatrix::operator -=
 * @param v double constant
 */
void NumericMatrix::operator-=(const double v)
{
    data -= v;
}


/**
 * @brief NumericMatrix::operator *
 * @param v double constant
 * @return NumericMatrix resulting from the multiplication of v and each element in the matrix
 */
NumericMatrix NumericMatrix::operator*(const double v)
{
    cv::Mat res = data * v;
    return NumericMatrix(res);
}


/**
 * @brief NumericMatrix::operator *=
 * @param v double constant
 */
void NumericMatrix::operator*=(const double v)
{
    data *= v;
}

/**
 * @brief NumericMatrix::operator /
 * @param v  double constant
 * @return NumericMatrix resulting from the diovision of each element in the matrix by v
 */
NumericMatrix NumericMatrix::operator/(const double v)
{
    assert(std::fabs(v)>FLT_EPSILON);
    cv::Mat res = data / v;
    return NumericMatrix(res);
}

/**
 * @brief NumericMatrix::operator /=
 * @param v  double constant
 */
void NumericMatrix::operator/=(const double v)
{
    assert(std::fabs(v)>FLT_EPSILON);
    data /= v;
}


/**
 * @brief NumericMatrix::Determinant
 * @return the determinant of the Numeric Matrix (double)
 */
double NumericMatrix::Determinant()
{
    return cv::determinant(data);
}


/**
 * @brief NumericMatrix::Invert
 * @return The NumericMatrix resulting from the inversion of a given NumericMatrix
 */
NumericMatrix NumericMatrix::Invert()
{
    assert(std::fabs(Determinant())>FLT_EPSILON);
    cv::Mat res = data.inv();
    return NumericMatrix(res);
}


/**
 * @brief NumericMatrix::SelfInvert  invert the NumericMatrix
 */
void NumericMatrix::SelfInvert()
{
    assert(std::fabs(Determinant())>FLT_EPSILON);
    data = data.inv();
}


/**
 * @brief NumericMatrix::Transpose
 * @return The NumericMatrix resulting from the transpose of a given NumericMatrix
 */
NumericMatrix NumericMatrix::Transpose()
{
    cv::Mat res = data.t();
    return NumericMatrix(res);
}

/**
 * @brief NumericMatrix::SelfTranspose  transpose the NumericMatrix
 */
void NumericMatrix::SelfTranspose()
{
    data = data.t();
}

}

