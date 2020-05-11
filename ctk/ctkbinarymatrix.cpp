#include "ctkbinarymatrix.h"

#include <iostream>

namespace ctk {

BinaryMatrix::BinaryMatrix()
{
    type = CV_8U;
    ch_size = 1;
}

BinaryMatrix::BinaryMatrix(const BinaryMatrix &that)
{
    assert(that.data.type()==CV_8U && that.data.channels()==1);
    type = that.type;
    ch_size = that.ch_size;
    data = that.data.clone();
}

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

BinaryMatrix::BinaryMatrix(int w, int h, std::vector<bool> &d)
{
    type = CV_8U;
    ch_size = 1;
    Create(w, h);
    //
    int i=-1;
    for (auto it=begin(); it!=end(); ++it) *it = d[++i];
}

BinaryMatrix &BinaryMatrix::operator=(const BinaryMatrix &that)
{
    assert(that.data.type()==CV_8U && that.data.channels()==1);
    type = that.type;
    ch_size = that.ch_size;
    data = that.data.clone();
    return *this;
}

void BinaryMatrix::set(int x, int y, bool v)
{
    data.at<uchar>(y,x) = v*255;
}

bool BinaryMatrix::get(int x, int y)
{
    return (static_cast<int>(data.at<uchar>(y,x))>128);
}

BinaryMatrix BinaryMatrix::Not()
{
    BinaryMatrix aux(*this);
    for (int x=0; x<data.cols; x++) {
        for(int y=0; y<data.rows; y++) {
            aux.set(x,y, 1-get(x,y));
        }
    }
    return aux;
}

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

void BinaryMatrix::Open(std::string filename) {
    AbstractMatrix<bool>::data = cv::imread(filename, cv::IMREAD_UNCHANGED);
}

void BinaryMatrix::Save(std::string filename) {
    cv::imwrite(filename, AbstractMatrix<bool>::data);
}

void BinaryMatrix::Show() {
    std::cout << "TODO" << std::endl;
}

}
