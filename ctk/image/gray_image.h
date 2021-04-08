#pragma once

#include <opencv2/highgui.hpp>

#include "ctk/image/abstract_image.h"

namespace ctk {

/**
 * @brief The GrayImage class
 */
class GrayImage : public AbstractImage<uchar> {
public:
    GrayImage();
    GrayImage(const GrayImage& that);
    GrayImage(const AbstractImage<uchar>& that);
    GrayImage(cv::Mat& d);
    virtual ~GrayImage(){}

    GrayImage &operator=(const GrayImage& that);
    GrayImage& operator=(const cv::Mat& that);
    GrayImage &operator=(const AbstractImage<uchar>& that);

    void Open(std::string filename);

    int channels();

    BinaryImage ApplyBinaryThreshold(int t=127);
    BinaryImage ApplyOtsuThreshold();
    BinaryImage ApplyAdaptativeThreshold(int bs=5, int c=1);

    GrayImage Truncate(int t=128);

    GrayImage Normalize(int minv, int maxv);
    BinaryImage PickColor(int c);

    RgbImage toRgbImage();
};

} // namespace ctk 
