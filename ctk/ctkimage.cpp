#include "ctkimage.h"

#include <iostream>

#include "opencv2/imgproc.hpp"

namespace ctk {

GrayImage::GrayImage()
{
    type = CV_8UC1;
    ch_size = 1;
    invertchannels = false;
}

GrayImage::GrayImage(const GrayImage &that)
{
    assert(that.data.type()==CV_8UC1 && that.data.channels()==1);
    type = that.type;
    ch_size = that.ch_size;
    invertchannels = false;
    data = that.data.clone();
}

GrayImage::GrayImage(const AbstractImage<uchar> &that)
{
    assert(that.get_data().type()==CV_8UC1
           && that.get_data().channels()==1);
    type = CV_8UC1;
    ch_size = 1;
    invertchannels = false;
    data = that.get_data().clone();
}

GrayImage::GrayImage(cv::Mat &d) : AbstractImage<uchar>(d){
    assert(d.type()==CV_8UC1 && d.channels()==1);
}

GrayImage &GrayImage::operator=(const GrayImage &that)
{
    assert(that.data.type()==CV_8UC1 && that.data.channels()==1);
    type = that.type;
    ch_size = that.ch_size;
    invertchannels = false;
    data = that.data.clone();
    return *this;
}

GrayImage &GrayImage::operator=(const cv::Mat &that)
{
    assert(that.type()==CV_8UC1 && that.channels()==1);
    type = that.type();
    ch_size = that.channels();
    invertchannels = false;
    data = that.clone();
    return *this;
}

GrayImage &GrayImage::operator=(const AbstractImage<uchar> &that)
{
    assert(that.get_data().type()==CV_8UC1
           && that.get_data().channels()==1);
    type = CV_8UC1;
    ch_size = 1;
    invertchannels = false;
    data = that.get_data().clone();
    return *this;
}

int GrayImage::channels()
{
    return 1;
}

RgbImage GrayImage::toRgbImage()
{
    RgbImage newImage;
    cv::cvtColor(data, newImage.get_data(), cv::COLOR_GRAY2BGR);
    return newImage;
}

BinaryMatrix GrayImage::ApplyBinaryThreshold(int t)
{
    BinaryMatrix newImage;
    threshold(data, newImage.get_data(), t, 255, 0);
    return newImage;
}

BinaryMatrix GrayImage::ApplyOtsuThreshold()
{
    BinaryMatrix newImage;
    threshold(data, newImage.get_data(), 0, 255, cv::THRESH_OTSU);
    return newImage;
}

BinaryMatrix GrayImage::ApplyAdaptativeThreshold(int bs, int c)
{
    cv::Mat aux;
    data.convertTo(aux, CV_8UC1);
    cv::adaptiveThreshold(data, aux, 255,
                          cv::ADAPTIVE_THRESH_GAUSSIAN_C,
                          cv::THRESH_BINARY, bs, c);
    return BinaryMatrix(aux);
}

ColorImage::ColorImage()
{
    type = CV_8UC3;
    ch_size = 3;
    invertchannels = false;
}

ColorImage::ColorImage(const ColorImage &that)
{
    assert(that.data.type()==CV_8UC3 && that.data.channels()==3);
    type = that.type;
    ch_size = that.ch_size;
    invertchannels = false;
    data = that.data.clone();
}

ColorImage::ColorImage(const AbstractImage<cv::Vec3b> &that)
{
    assert(that.get_data().type()==CV_8UC3
           && that.get_data().channels()==3);
    type = CV_8UC3;
    ch_size = 3;
    invertchannels = false;
    data = that.get_data().clone();
}

ColorImage::ColorImage(cv::Mat &d) : AbstractImage<cv::Vec3b>(d){
    assert(d.type()==CV_8UC3 && d.channels()==3);
}

int ColorImage::channels()
{
    return 3;
}

RgbImage::RgbImage() : ColorImage()
{
    invertchannels = true;
}

RgbImage::RgbImage(const RgbImage &that)
{
    assert(that.data.type()==CV_8UC3 && that.data.channels()==3);
    type = that.type;
    ch_size = that.ch_size;
    invertchannels = true;
    data = that.data.clone();
}

RgbImage::RgbImage(const AbstractImage<cv::Vec3b> &that)
{
    assert(that.get_data().type()==CV_8UC3
           && that.get_data().channels()==3);
    type = CV_8UC3;
    ch_size = 3;
    invertchannels = true;
    data = that.get_data().clone();
}

RgbImage::RgbImage(cv::Mat &d) : ColorImage(d){
    assert(d.type()==CV_8UC3 && d.channels()==3);
}

void RgbImage::Create(int w, int h)
{
    ColorImage::Create(w,h);
}

void RgbImage::set(int x, int y, int r, int g, int b)
{
    AbstractMatrix<cv::Vec3b>::set(x, y, cv::Vec3b(r,g,b));
}

void RgbImage::safe_set(int x, int y, int r, int g, int b)
{
    AbstractMatrix<cv::Vec3b>::safe_set(x, y, cv::Vec3b(r,g,b));
}

void RgbImage::safe_set(int i, int r, int g, int b)
{
    AbstractImage<cv::Vec3b>::safe_set(i, cv::Vec3b(r,g,b));
}

void RgbImage::set(int i, int r, int g, int b)
{
    AbstractImage<cv::Vec3b>::set(i, cv::Vec3b(r,g,b));
}

int RgbImage::red(int x, int y)
{
    return AbstractMatrix<cv::Vec3b>::get(x,y)[0];
}

int RgbImage::green(int x, int y)
{
    return AbstractMatrix<cv::Vec3b>::get(x,y)[1];
}

int RgbImage::blue(int x, int y)
{
    return AbstractMatrix<cv::Vec3b>::get(x,y)[2];
}

GrayImage RgbImage::toGrayImage()
{
    GrayImage newImage;
    cv::cvtColor(data, newImage.get_data(), cv::COLOR_RGB2GRAY);
    return newImage;
}

}

