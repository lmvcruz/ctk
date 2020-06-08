#include "ctkimage.h"

#include <iostream>
#include <vector>

#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <opencv2/calib3d.hpp>
#include <opencv2/core/types_c.h>

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

GrayImage GrayImage::Normalize(int minv, int maxv)
{
    //TODO: replace asserts to exceptions
    assert(minv>=0);
    assert(maxv<=255);
    assert(minv<maxv);
    //
    GrayImage norm;
    norm.Create(width(), height());
    int cmin = 255;
    int cmax = 0;
    for (auto x=0; x<data.rows; x++) {
        for (auto y=0; y<data.cols; y++) {
            int ic = static_cast<int>(get(x,y));
            cmin = std::min(cmin, ic);
            cmax = std::max(cmax, ic);
        }
    }
    float scale = static_cast<float>(maxv-minv) / static_cast<float>(cmax-cmin);
    for (auto x=0; x<data.rows; x++) {
        for (auto y=0; y<data.cols; y++) {
            int ic = static_cast<int>(get(x,y));
            float c = static_cast<float>(ic-cmin+minv)*scale;
            norm.set(x,y,static_cast<int>(c));
//            std::cout << x << " " << y << " " << ic << " " << c << std::endl;
        }
    }
    return norm;
}

BinaryMatrix GrayImage::PickColor(int c)
{
    BinaryMatrix mask;
    mask.Create(width(), height());
    for (auto x=0; x<data.rows; x++) {
        for (auto y=0; y<data.cols; y++) {
//            std::cout << x << " " << y << " " << static_cast<int>(get(x,y)) << " " << c << std::endl;
            if (static_cast<int>(get(x,y))==c) mask.set(x,y,true);
            else mask.set(x,y,false);
        }
    }
    return mask;
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

PointI RgbImage::get_pixel(int x, int y)
{
    return PointI(red(x,y), green(x,y), blue(x,y));
}

RgbImage RgbImage::Quantize(int q, int iter, float eps, int attempts, int qtype)
{
    RgbImage cluster(data);
    cv::Mat vals;
    cluster.data.convertTo(vals,CV_32F);
    vals = vals.reshape(1,vals.total());
    //
    cv::Mat labels, centers;
    cv::TermCriteria crit(CV_TERMCRIT_ITER, iter, eps);
    kmeans(vals, q, labels, crit, attempts, qtype, centers);
    // reshape both to a single row of Vec3f pixels:
    centers = centers.reshape(3,centers.rows);
    vals = vals.reshape(3,vals.rows);
    // replace pixel values with their center value:
    cv::Vec3f *p = vals.ptr<cv::Vec3f>();
    for (size_t i=0; i<vals.rows; i++) {
       int center_id = labels.at<int>(i);
       p[i] = centers.at<cv::Vec3f>(center_id);
    }
    // back to 2d, and uchar:
    cluster.data = vals.reshape(3, cluster.data.rows);
    cluster.data.convertTo(cluster.data, CV_8U);
    cv::cvtColor(cluster.data, cluster.data, cv::COLOR_BGR2RGB);
    return cluster;
}

BinaryMatrix RgbImage::PickColor(int r, int g, int b)
{
    BinaryMatrix mask;
    mask.Create(width(), height());
    for (auto x=0; x<data.rows; x++) {
        for (auto y=0; y<data.cols; y++) {
            if ((red(x,y)==r) && (green(x,y)==g) && (blue(x,y)==b)) mask.set(x,y,true);
            else mask.set(x,y,false);
        }
    }
    return mask;
}

GrayImage RgbImage::Project(std::vector<PointI> &colors)
{
    // TODO: replace it to an exception
    assert(colors.size()<=256);
    //
    GrayImage mask;
    mask.Create(width(), height());
    for (auto x=0; x<data.rows; x++) {
        for (auto y=0; y<data.cols; y++) {
            int idx = -1;
            float dist = FLT_MAX;
            for (auto i=0; i<colors.size(); i++) {
                float d = colors[i].Distance(get_pixel(x,y));
                if (d<dist) {
                    dist = d;
                    idx = i;
                }
            }
            mask.set(x, y, idx);
        }
    }
    return mask;
}

std::vector<std::vector<PointI>> RgbImage::Contours()
{
    BinaryMatrix bin = toGrayImage().ApplyOtsuThreshold();
    //
    std::vector<std::vector<cv::Point> > cv_contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(bin.get_data(), cv_contours, hierarchy,
                     cv::RETR_TREE, cv::CHAIN_APPROX_TC89_KCOS);
    //
    std::vector<std::vector<PointI>> conts;
    conts.resize(cv_contours.size());
    for (auto i=0; i<cv_contours.size(); i++) {
        conts[i].resize(cv_contours[i].size());
        for (auto j=0; j<cv_contours[i].size(); j++) {
            conts[i][j].setX(cv_contours[i][j].x);
            conts[i][j].setY(cv_contours[i][j].y);
        }
    }
    return conts;
}

std::vector<std::vector<PointI> > RgbImage::ApproximateContours(int eps)
{
    BinaryMatrix bin = toGrayImage().ApplyOtsuThreshold();
    //
    std::vector<std::vector<cv::Point> > cv_contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(bin.get_data(), cv_contours, hierarchy,
                     cv::RETR_TREE, cv::CHAIN_APPROX_TC89_KCOS);
    //
    std::vector<std::vector<PointI>> conts;
    conts.resize(cv_contours.size());
    for (auto i=0; i<cv_contours.size(); i++) {
        //TODO: remove it
        std::vector<cv::Point> approx;
        approxPolyDP(cv::Mat(cv_contours[i]), approx, eps, true);
        conts[i].resize(approx.size());
        for (auto j=0; j<approx.size(); j++) {
            conts[i][j].setX(approx[j].x);
            conts[i][j].setY(approx[j].y);
        }
    }
    return conts;
}

//TODO: write tests and benchmark
RgbImage RgbImage::Warp(std::vector<PointI> &pts, std::vector<PointI> &refs,
                        int w, int h)
{
    //TODO: replace assert to exceptions
    assert(pts.size()==refs.size());
    assert(pts.size()>=4);
    //
    std::vector<cv::Point2f> cv_pts;
    cv_pts.resize(pts.size());
    std::vector<cv::Point2f> cv_refs;
    cv_refs.resize(refs.size());
    for (auto i=0; i<pts.size(); i++) {
        cv_pts[i].x = pts[i].getX();
        cv_pts[i].y = pts[i].getY();
        cv_refs[i].x = refs[i].getX();
        cv_refs[i].y = refs[i].getY();
    }
    cv::Mat homo_mat;
    // We assume that size>=4 (verified in the begining of the method)
    if (pts.size()>4) {
        homo_mat = cv::findHomography(cv_pts, cv_refs,cv::RANSAC);
    }
    else {
        homo_mat = cv::findHomography(cv_pts, cv_refs);
    }
    //
    RgbImage rect;
    cv::warpPerspective(data, rect.get_data(), homo_mat, cv::Size(w,h));
    return rect;
}

GrayImage RgbImage::toGrayImage()
{
    GrayImage newImage;
    cv::cvtColor(data, newImage.get_data(), cv::COLOR_RGB2GRAY);
    return newImage;
}

}

