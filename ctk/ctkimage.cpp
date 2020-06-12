#include "ctkimage.h"

#include <iostream>
#include <vector>

#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <opencv2/calib3d.hpp>
#include <opencv2/core/types_c.h>

namespace ctk {

/**
 * @brief GrayImage::GrayImage - Default Constructor
 */
GrayImage::GrayImage()
{
    type = CV_8UC1;
    ch_size = 1;
    invertchannels = false;
}

/**
 * @brief GrayImage::GrayImage - Copy Constructor
 * @param that reference to existing GrayImage object
 */
GrayImage::GrayImage(const GrayImage &that)
{
    assert(that.data.type()==CV_8UC1 && that.data.channels()==1);
    type = that.type;
    ch_size = that.ch_size;
    invertchannels = false;
    data = that.data.clone();
}

/**
 * @brief GrayImage::GrayImage - Copy Constructor
 * @param that  reference to existing AbstractImage object
 */
GrayImage::GrayImage(const AbstractImage<uchar> &that)
{
    assert(that.get_data().type()==CV_8UC1
           && that.get_data().channels()==1);
    type = CV_8UC1;
    ch_size = 1;
    invertchannels = false;
    data = that.get_data().clone();
}

/**
 * @brief GrayImage::GrayImage
 * @param d
 */
GrayImage::GrayImage(cv::Mat &d) : AbstractImage<uchar>(d){
    assert(d.type()==CV_8UC1 && d.channels()==1);
}


/**
 * @brief GrayImage::operator =
 * @param that reference to existing GrayImage object
 * @return Updated GrayImage
 */
GrayImage &GrayImage::operator=(const GrayImage &that)
{
    assert(that.data.type()==CV_8UC1 && that.data.channels()==1);
    type = that.type;
    ch_size = that.ch_size;
    invertchannels = false;
    data = that.data.clone();
    return *this;
}

/**
 * @brief GrayImage::operator =
 * @param that reference to cv::Mat matrix
 * @return Updated GrayImage
 */
GrayImage &GrayImage::operator=(const cv::Mat &that)
{
    assert(that.type()==CV_8UC1 && that.channels()==1);
    type = that.type();
    ch_size = that.channels();
    invertchannels = false;
    data = that.clone();
    return *this;
}

/**
 * @brief GrayImage::operator =
 * @param that  reference to existing AbstractImage object
 * @return Updated GrayImage
 */
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

/**
 * @brief GrayImage::channels
 * @return 1
 */
int GrayImage::channels()
{
    return 1;
}

/**
 * @brief GrayImage::toRgbImage - Convert gray image to RGB image
 * @return RGB Image
 */
RgbImage GrayImage::toRgbImage()
{
    RgbImage newImage;
    cv::cvtColor(data, newImage.get_data(), cv::COLOR_GRAY2BGR);
    return newImage;
}

/**
 * @brief GrayImage::ApplyBinaryThreshold  - Binarize gray image according to passed threshold
 * @param t  int representing the threshold
 * @return Binary image resulting from applying the threshold to the Gray Image
 */
BinaryMatrix GrayImage::ApplyBinaryThreshold(int t)
{
    BinaryMatrix newImage;
    threshold(data, newImage.get_data(), t, 255, 0);
    return newImage;
}

/**
 * @brief GrayImage::ApplyOtsuThreshold - Binarize gray image using Otsu threshold
 * @return Resulting Binary image
 */
BinaryMatrix GrayImage::ApplyOtsuThreshold()
{
    BinaryMatrix newImage;
    threshold(data, newImage.get_data(), 0, 255, cv::THRESH_OTSU);
    return newImage;
}


/**
 * @brief GrayImage::ApplyAdaptativeThreshold
 * @param bs int representing the size of a pixel neighborhood that is used to calculate a threshold value for the pixel
 * @param c int representing the constant subtracted from the weighted mean (Gaussian window)
 * @return Resulting Binary image
 */
BinaryMatrix GrayImage::ApplyAdaptativeThreshold(int bs, int c)
{
    cv::Mat aux;
    data.convertTo(aux, CV_8UC1);
    cv::adaptiveThreshold(data, aux, 255,
                          cv::ADAPTIVE_THRESH_GAUSSIAN_C,
                          cv::THRESH_BINARY, bs, c);
    return BinaryMatrix(aux);
}


/**
 * @brief GrayImage::Normalize - Normalize image into a given range
 * @param minv int representing the lower bound of the range
 * @param maxv  int representing the upper bound of the range
 * @return Normalized image
 */
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


/**
 * @brief GrayImage::PickColor
 * @param c int representing the desired gray level
 * @return BinaryMatrix representing a mask of the original image which is 1 for the desired gray level and 0 otherwise
 */
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

/**
 * @brief ColorImage::ColorImage - Default Constructor
 */
ColorImage::ColorImage()
{
    type = CV_8UC3;
    ch_size = 3;
    invertchannels = false;
}

/**
 * @brief ColorImage::ColorImage - Copy Construtor
 * @param that reference to an existing
 */
ColorImage::ColorImage(const ColorImage &that)
{
    assert(that.data.type()==CV_8UC3 && that.data.channels()==3);
    type = that.type;
    ch_size = that.ch_size;
    invertchannels = false;
    data = that.data.clone();
}

/**
 * @brief ColorImage::ColorImage - Copy Construtor
 * @param that  reference to an AbstractImage
 */
ColorImage::ColorImage(const AbstractImage<cv::Vec3b> &that)
{
    assert(that.get_data().type()==CV_8UC3
           && that.get_data().channels()==3);
    type = CV_8UC3;
    ch_size = 3;
    invertchannels = false;
    data = that.get_data().clone();
}

/**
 * @brief ColorImage::ColorImage
 * @param d
 */
ColorImage::ColorImage(cv::Mat &d) : AbstractImage<cv::Vec3b>(d){
    assert(d.type()==CV_8UC3 && d.channels()==3);
}

/**
 * @brief ColorImage::channels
 * @return 3
 */
int ColorImage::channels()
{
    return 3;
}

/**
 * @brief RgbImage::RgbImage
 */
RgbImage::RgbImage() : ColorImage()
{
    invertchannels = true;
}

/**
 * @brief RgbImage::RgbImage - Copy Construtor
 * @param that reference to an existing RgbImage
 */
RgbImage::RgbImage(const RgbImage &that)
{
    assert(that.data.type()==CV_8UC3 && that.data.channels()==3);
    type = that.type;
    ch_size = that.ch_size;
    invertchannels = true;
    data = that.data.clone();
}

/**
 * @brief RgbImage::RgbImage - Copy Construtor
 * @param that  reference to an existing AbstractImage
 */
RgbImage::RgbImage(const AbstractImage<cv::Vec3b> &that)
{
    assert(that.get_data().type()==CV_8UC3
           && that.get_data().channels()==3);
    type = CV_8UC3;
    ch_size = 3;
    invertchannels = true;
    data = that.get_data().clone();
}

/**
 * @brief RgbImage::RgbImage
 * @param d
 */
RgbImage::RgbImage(cv::Mat &d) : ColorImage(d){
    assert(d.type()==CV_8UC3 && d.channels()==3);
}

/**
 * @brief RgbImage::Create - Create RgbImage
 * @param w int representing image width
 * @param h int representing image hight
 */
void RgbImage::Create(int w, int h)
{
    ColorImage::Create(w,h);
}

/**
 * @brief RgbImage::set - Set value of image pixel
 * @param x int representing the row index
 * @param y int representing the column index
 * @param r int representing the desired red value
 * @param g int representing the desired green value
 * @param b int representing the desired blue value
 */
void RgbImage::set(int x, int y, int r, int g, int b)
{
    AbstractMatrix<cv::Vec3b>::set(x, y, cv::Vec3b(r,g,b));
}

/**
 * @brief RgbImage::safe_set - Set value of image pixel
 * @param x int representing the row index
 * @param y int representing the column index
 * @param r int representing the desired red value
 * @param g int representing the desired green value
 * @param b int representing the desired blue value
 */
void RgbImage::safe_set(int x, int y, int r, int g, int b)
{
    AbstractMatrix<cv::Vec3b>::safe_set(x, y, cv::Vec3b(r,g,b));
}

/**
 * @brief RgbImage::safe_set
 * @param i
 * @param r
 * @param g
 * @param b
 */
void RgbImage::safe_set(int i, int r, int g, int b)
{
    AbstractImage<cv::Vec3b>::safe_set(i, cv::Vec3b(r,g,b));
}

/**
 * @brief RgbImage::set
 * @param i
 * @param r
 * @param g
 * @param b
 */
void RgbImage::set(int i, int r, int g, int b)
{
    AbstractImage<cv::Vec3b>::set(i, cv::Vec3b(r,g,b));
}

/**
 * @brief RgbImage::red Get red value of a pixel
 * @param x int representing the row index
 * @param y int representing the column index
 * @return int representing the red value of the pixel at (x,y)
 */
int RgbImage::red(int x, int y)
{
    return AbstractMatrix<cv::Vec3b>::get(x,y)[0];
}

/**
 * @brief RgbImage::green Get green value of a pixel
 * @param x int representing the row index
 * @param y int representing the column index
 * @return int representing the green value of the pixel at (x,y)
 */
int RgbImage::green(int x, int y)
{
    return AbstractMatrix<cv::Vec3b>::get(x,y)[1];
}


/**
 * @brief RgbImage::blue Get blue value of a pixel
 * @param x int representing the row index
 * @param y int representing the column index
 * @return int representing the blue value of the pixel at (x,y)
 */
int RgbImage::blue(int x, int y)
{
    return AbstractMatrix<cv::Vec3b>::get(x,y)[2];
}

/**
 * @brief RgbImage::get_pixel
 * @param x int representing the row index
 * @param y int representing the column index
 * @return Point representing the pixel at (x,y)
 */
PointI RgbImage::get_pixel(int x, int y)
{
    return PointI(red(x,y), green(x,y), blue(x,y));
}

/**
 * @brief RgbImage::Quantize
 * @param q
 * @param iter
 * @param eps
 * @param attempts
 * @param qtype
 * @return
 */
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

/**
 * @brief RgbImage::PickColor - Produce image mask for a given color
 * @param r int representing the red value of the desired color
 * @param g int representing the green value of the desired color
 * @param b int representing the blue value of the desired color
 * @return BinaryMatrix representing a mask of the original image which is 1 for the desired gray level and 0 otherwise
 */
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

std::vector<Polygon> RgbImage::Contours()
{
    BinaryMatrix bin = toGrayImage().ApplyOtsuThreshold();
    //
    std::vector<std::vector<cv::Point> > cv_contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(bin.get_data(), cv_contours, hierarchy,
                     cv::RETR_TREE, cv::CHAIN_APPROX_TC89_KCOS);
    //
    std::vector<Polygon> ctk_contours;
    ctk_contours.resize(cv_contours.size());
    for (auto i=0; i<cv_contours.size(); i++) {
        ctk_contours[i] = cv_contours[i];
    }
    return ctk_contours;
}

std::vector<Polygon> RgbImage::ApproximateContours(int eps)
{
    BinaryMatrix bin = toGrayImage().ApplyOtsuThreshold();
    //
    std::vector<std::vector<cv::Point> > cv_contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(bin.get_data(), cv_contours, hierarchy,
                     cv::RETR_TREE, cv::CHAIN_APPROX_TC89_KCOS);
    //
    std::vector<Polygon> ctk_contours;
    ctk_contours.resize(cv_contours.size());
    for (auto i=0; i<cv_contours.size(); i++) {
        std::vector<cv::Point> approx;
        approxPolyDP(cv::Mat(cv_contours[i]), approx, eps, true);
        ctk_contours[i] = approx;
    }
    return ctk_contours;
}

//TODO: write tests and benchmark
RgbImage RgbImage::Warp(std::vector<PointD> &pts, std::vector<PointD> &refs,
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

