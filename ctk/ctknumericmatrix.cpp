#include "ctknumericmatrix.h"

#include <iostream>
#include <iomanip>

#include <opencv2/highgui.hpp>

namespace ctk {

NumericMatrix::NumericMatrix()
{
    type = CV_64F;
    ch_size = 1;
}

NumericMatrix::NumericMatrix(cv::Mat &d) : AbstractMatrix<double>(d){
    assert(d.type()==CV_64F && d.channels()==1);
}

NumericMatrix::NumericMatrix(int w, int h, std::vector<double> &d)
{
    type = CV_64F;
    ch_size = 1;
    Create(w, h);
    //
    int i=-1;
    for (auto it=begin(); it!=end(); ++it) *it = d[++i];
}

NumericMatrix::NumericMatrix(const NumericMatrix &that)
{
    assert(that.data.type()==CV_64F && that.data.channels()==1);
    type = that.type;
    ch_size = that.ch_size;
    data = that.data.clone();
}

NumericMatrix &NumericMatrix::operator=(const NumericMatrix &that)
{
    assert(that.data.type()==CV_64F && that.data.channels()==1);
    type = that.type;
    ch_size = that.ch_size;
    data = that.data.clone();
    return *this;
}

void NumericMatrix::Open(std::string filename)
{
    data = cv::imread(filename, cv::IMREAD_ANYDEPTH);
}

void NumericMatrix::Save(std::string filename)
{
    cv::imwrite(filename, data);
}

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

NumericMatrix NumericMatrix::operator+(const NumericMatrix &that) {
    cv::Mat res = data + that.data;
    return NumericMatrix(res);
}

void NumericMatrix::operator+=(const NumericMatrix &that)
{
    data += that.data;
}

NumericMatrix NumericMatrix::operator-(const NumericMatrix &that)
{
    cv::Mat res = data - that.data;
    return NumericMatrix(res);
}

void NumericMatrix::operator-=(const NumericMatrix &that)
{
    data -= that.data;
}

NumericMatrix NumericMatrix::operator*(const NumericMatrix &that)
{
    assert(data.cols==that.rows());
    cv::Mat res = data * that.data;
    return NumericMatrix(res);
}

void NumericMatrix::operator*=(const NumericMatrix &that)
{
    assert(data.cols==that.rows());
    data *= that.data;
}

NumericMatrix NumericMatrix::operator/(const NumericMatrix &that)
{
    assert(data.cols==that.rows());
    assert(that.cols()==that.rows() && that.cols()>0);
    assert(std::fabs(cv::determinant(that.data))>FLT_EPSILON);
    cv::Mat res = data * that.data.inv();
    return NumericMatrix(res);
}

void NumericMatrix::operator/=(const NumericMatrix &that)
{
    assert(data.cols==that.rows());
    assert(that.cols()==that.rows() && that.cols()>0);
    assert(std::fabs(cv::determinant(that.data))>FLT_EPSILON);
    data *= that.data.inv();
}

NumericMatrix NumericMatrix::operator+(const double v)
{
    cv::Mat res = data + v;
    return NumericMatrix(res);
}

void NumericMatrix::operator+=(const double v)
{
    data += v;
}

NumericMatrix NumericMatrix::operator-(const double v)
{
    cv::Mat res = data - v;
    return NumericMatrix(res);
}

void NumericMatrix::operator-=(const double v)
{
    data -= v;
}

NumericMatrix NumericMatrix::operator*(const double v)
{
    cv::Mat res = data * v;
    return NumericMatrix(res);
}

void NumericMatrix::operator*=(const double v)
{
    data *= v;
}

NumericMatrix NumericMatrix::operator/(const double v)
{
    assert(std::fabs(v)>FLT_EPSILON);
    cv::Mat res = data / v;
    return NumericMatrix(res);
}

void NumericMatrix::operator/=(const double v)
{
    assert(std::fabs(v)>FLT_EPSILON);
    data /= v;
}

double NumericMatrix::determinant()
{
    return cv::determinant(data);
}

NumericMatrix NumericMatrix::Invert()
{
    assert(std::fabs(determinant())>FLT_EPSILON);
    cv::Mat res = data.inv();
    return NumericMatrix(res);
}

void NumericMatrix::SelfInvert()
{
    assert(std::fabs(determinant())>FLT_EPSILON);
    data = data.inv();
}

NumericMatrix NumericMatrix::Transpose()
{
    cv::Mat res = data.t();
    return NumericMatrix(res);
}

void NumericMatrix::SelfTranspose()
{
    data = data.t();
}

}

