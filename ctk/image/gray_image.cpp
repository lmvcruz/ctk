#include "ctk/image/gray_image.h"

#include <opencv2/highgui.hpp>

#include "ctk/image/binary_image.h"
#include "ctk/image/rgb_image.h"

namespace ctk
{

/**
 * @brief GrayImage::GrayImage  Default Constructor
 */
GrayImage::GrayImage() {
    type = CV_8UC1;
    ch_size = 1;
    invert_channels_ = false;
}

/**
 * @brief GrayImage::GrayImage - Copy Constructor
 * @param that reference to existing GrayImage object
 */
GrayImage::GrayImage(const GrayImage &that) {
    if (that.data.type()!=CV_8UC1 || that.data.channels()!=1) throw  incompatible_parameters();
    type = that.type;
    ch_size = that.ch_size;
    invert_channels_ = false;
    data = that.data.clone();
}

/**
 * @brief GrayImage::GrayImage - Copy Constructor
 * @param that  reference to existing AbstractImage object
 */
GrayImage::GrayImage(const AbstractImage<uchar> &that) {
    if (that.GetData().channels()==3) {
        cv::cvtColor(that.GetData(), data, cv::COLOR_RGB2GRAY);
    } else {
        data = that.GetData().clone();
    }
    type = CV_8UC1;
    ch_size = 1;
    invert_channels_ = false;
    if (data.type()!=CV_8UC1 || data.channels()!=1) throw  incompatible_parameters();
}

/**
 * @brief GrayImage::GrayImage
 * @param d
 */
GrayImage::GrayImage(cv::Mat &d)  {
    if (d.channels()==3) {
        cv::cvtColor(d, data, cv::COLOR_RGB2GRAY);
    }
    else {
        data = d.clone();
    }
    type = CV_8UC1;
    ch_size = 1;
    invert_channels_ = false;
    if (data.type()!=CV_8UC1 || data.channels()!=1) throw  incompatible_parameters();
}


/**
 * @brief GrayImage::operator = Operator Copy
 * @param that reference to existing GrayImage object
 * @return Updated GrayImage
 */
GrayImage &GrayImage::operator=(const GrayImage &that) {
    if (that.data.type()!=CV_8UC1 || that.data.channels()!=1) throw  incompatible_parameters();
    type = that.type;
    ch_size = that.ch_size;
    invert_channels_ = false;
    data = that.data.clone();
    return *this;
}

/**
 * @brief GrayImage::operator =  Operator Copy
 * @param that reference to cv::Mat matrix
 * @return Updated GrayImage
 */
GrayImage &GrayImage::operator=(const cv::Mat &that) {
    if (that.channels()==3) {
        cv::cvtColor(that, data, cv::COLOR_RGB2GRAY);
    } else {
        data = that.clone();
    }
    type = that.type();
    ch_size = that.channels();
    invert_channels_ = false;
    if (data.type()!=CV_8UC1 || data.channels()!=1) throw  incompatible_parameters();
    return *this;
}

/**
 * @brief GrayImage::operator =  Operator Copy
 * @param that  reference to existing AbstractImage object
 * @return Updated GrayImage
 */
GrayImage &GrayImage::operator=(const AbstractImage<uchar> &that) {
    if (that.GetData().channels()==3) {
        cv::cvtColor(that.GetData(), data, cv::COLOR_RGB2GRAY);
    } else {
        data = that.GetData().clone();
    }
    type = CV_8UC1;
    ch_size = 1;
    invert_channels_ = false;
    if (data.type()!=CV_8UC1 || data.channels()!=1) throw  incompatible_parameters();
    return *this;
}

/**
 * @brief GrayImage::Open Read gray image from file
 * @param filename  string representing the filename
 */
void GrayImage::Open(std::string filename) {
    data = cv::imread(filename, cv::IMREAD_UNCHANGED);
    if (data.channels()==3) {
        cv::cvtColor(data, data, cv::COLOR_RGB2GRAY);
    }
}

/**
 * @brief GrayImage::GetChannels  Get gray image channels
 * @return 1
 */
int GrayImage::GetChannels() {
    return 1;
}

/**
 * @brief GrayImage::toRgbImage - Convert gray image to RGB image
 * @return RGB Image
 */
RgbImage GrayImage::toRgbImage() {
    RgbImage newImage;
    cv::cvtColor(data, newImage.GetData(), cv::COLOR_GRAY2BGR);
    return newImage;
}

/**
 * @brief GrayImage::ApplyBinaryThreshold-  Binarize image according to passed threshold
 * @param t  int representing the desired threshold
 * @return Binary Image resulting from the application of t to the original image
 */
BinaryImage GrayImage::ApplyBinaryThreshold(int t) {
    BinaryImage newImage;
    threshold(data, newImage.GetData(), t, 255, 0);
    return newImage;
}


/**
 * @brief GrayImage::ApplyOtsuThreshold- use Otsu algorithm to choose the optimal threshold value
 * @return Binary Image resulting from the application of the Otsu threshold to the original image
 */
BinaryImage GrayImage::ApplyOtsuThreshold() {
    BinaryImage newImage;
    threshold(data, newImage.GetData(), 0, 255, cv::THRESH_OTSU);
    return newImage;
}

/**
 * @brief GrayImage::ApplyAdaptativeThreshold-  Apply an adaptive threshold to the image
 * @param bs int representing the box size: Size of a pixel neighborhood that is used to calculate a threshold value for the pixel
 * @param c int representing a constant subtracted from the weighted mean
 * @return Binary Image resulting from the adaptive thresholding of the original image
 */

BinaryImage GrayImage::ApplyAdaptativeThreshold(int bs, int c) {
    cv::Mat aux;
    data.convertTo(aux, CV_8UC1);
    cv::adaptiveThreshold(data, aux, 255,
                          cv::ADAPTIVE_THRESH_GAUSSIAN_C,
                          cv::THRESH_BINARY, bs, c);
    return BinaryImage(aux);
}

/**
 * @brief GrayImage::Normalize - Normalize image into a given range
 * @param minv int representing the lower bound of the range
 * @param maxv  int representing the upper bound of the range
 * @return Normalized image
 */
GrayImage GrayImage::Normalize(int minv, int maxv) {
    if (minv < 0) throw  incompatible_parameters();
    if (maxv > 255) throw  incompatible_parameters();
    if (minv<maxv) throw  incompatible_parameters();
    GrayImage norm;
    norm.Create(GetWidth(), GetHeight());
    int cmin = 255;
    int cmax = 0;
    for (auto x = 0; x < data.rows; x++) {
        for (auto y = 0; y < data.cols; y++) {
            int ic = static_cast<int>(Get(x,y));
            cmin = std::min(cmin, ic);
            cmax = std::max(cmax, ic);
        }
    }
    float scale = static_cast<float>(maxv-minv) / static_cast<float>(cmax-cmin);
    for (auto x = 0; x < data.rows; x++) {
        for (auto y = 0; y < data.cols; y++) {
            int ic = static_cast<int>(Get(x,y));
            float c = static_cast<float>(ic-cmin+minv)*scale;
            norm.Set(x,y,static_cast<uchar>(c));
        }
    }
    return norm;
}

/**
 * @brief GrayImage::PickColor- Create binary mask for a given gray value c
 * @param c int representing the desired gray value
 * @return BinaryImage representing a mask of the original image that is 1 when the gray value is c and 0 otherwise
 */
BinaryImage GrayImage::PickColor(int c) {
    BinaryImage mask;
    mask.Create(GetWidth(), GetHeight());
    for (auto x = 0; x < data.rows; x++) {
        for (auto y = 0; y < data.cols; y++) {
            if (static_cast<int>(Get(x,y)) == c) {
                mask.Set(x,y,true);
            } else {
                mask.Set(x,y,false);
            }
        }
    }
    return mask;
}
    
} // namespace ctk
