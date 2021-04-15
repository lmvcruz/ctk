#include "ctk/image/abstract_image.h"

#include <opencv2/calib3d.hpp>
#include <opencv2/core/types_c.h>

#include "ctk/image/rgb_image.h"
#include "ctk/image/binary_image.h"

namespace ctk {

/**
 * @brief ColorImage::ColorImage - Default Constructor
 */
ColorImage::ColorImage() {
    type = CV_8UC3;
    ch_size = 3;
    invert_channels_ = false;
}

/**
 * @brief ColorImage::ColorImage - Copy Construtor
 * @param that reference to an existing ColorImage object
 */
ColorImage::ColorImage(const ColorImage &that) {
    if (that.data.type()!=CV_8UC3 || that.data.channels()!=3) throw  incompatible_parameters();
    type = that.type;
    ch_size = that.ch_size;
    invert_channels_ = false;
    data = that.data.clone();
}

/**
 * @brief ColorImage::ColorImage - Copy Construtor
 * @param that  reference to an AbstractImage
 */
ColorImage::ColorImage(const AbstractImage<cv::Vec3b> &that) {
    if (that.GetData().type()!=CV_8UC3 || that.GetData().channels()!=3) throw  incompatible_parameters();
    type = CV_8UC3;
    ch_size = 3;
    invert_channels_ = false;
    data = that.GetData().clone();
}

/**
 * @brief ColorImage::ColorImage
 * @param d
 */
ColorImage::ColorImage(cv::Mat &d) : AbstractImage<cv::Vec3b>(d) {
    if (d.type()!=CV_8UC3 || d.channels()!=3) throw  incompatible_parameters();
}

/**
 * @brief ColorImage::channels Get color image channels
 * @return 3
 */
int ColorImage::GetChannels() {
    return 3;
}

} // namespace ctk 
