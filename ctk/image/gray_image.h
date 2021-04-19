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
    GrayImage(const cv::Mat& d);
    virtual ~GrayImage() = default;

    GrayImage& operator=(const GrayImage& that);
    GrayImage& operator=(const cv::Mat& that);
    GrayImage& operator=(const AbstractImage<uchar>& that);

    void Open(std::string filename);

    int GetChannels() const;

    BinaryImage ApplyBinaryThreshold(int t=127) const;
    BinaryImage ApplyOtsuThreshold() const;
    BinaryImage ApplyAdaptativeThreshold(int bs=5, int c=1) const;

    GrayImage Truncate(int t=128) const;

    GrayImage Normalize(int minv, int maxv) const;
    BinaryImage PickColor(int c) const;

    RgbImage ToRgbImage() const;
};

} // namespace ctk 
