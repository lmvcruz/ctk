#include "ctk/image/binary_image.h"

#include <opencv2/calib3d.hpp>
#include <opencv2/core/types_c.h>

#include "ctk/image/rgb_image.h"

namespace ctk {

/**
 * @brief BinaryImage::BinaryImage  Default Constructor
 */
BinaryImage::BinaryImage() {
    type = CV_8U; //8-bit single-channel array
    ch_size = 1;
}

/**
 * @brief BinaryImage::BinaryImage Copy Constructor
 * @param that Reference to an existing BinaryImage object
 */
BinaryImage::BinaryImage(const BinaryImage &that) {
    if (that.data.type()!=CV_8U || that.data.channels()!=1) throw  incompatible_parameters();
    type = that.type;
    ch_size = that.ch_size;
    data = that.data.clone();
}

/**
 * @brief BinaryImage::BinaryImage  Copy Constructor
 * @param that  Reference to an existing AbstractImage object
 */
BinaryImage::BinaryImage(const AbstractImage<bool> &that) {
    if (that.GetData().type()!=CV_8U || that.GetData().channels()!=1) throw  incompatible_parameters();
    type = CV_8U;
    ch_size = 1;
    data = that.GetData().clone();
}

/**
 * @brief BinaryImage::BinaryImage
 * @param d
 */
BinaryImage::BinaryImage(cv::Mat &d): AbstractImage<bool>(d) {
    if (d.type()!=CV_8U || d.channels()!=1) throw  incompatible_parameters();
}

/**
 * @brief BinaryImage::BinaryImage Constructor that create and fill the image
 * @param w width of the image
 * @param h height of the image
 */
BinaryImage::BinaryImage(int w, int h, bool v) {
    //TODO: test this method
    type = CV_8U;
    ch_size = 1;
    CreateAndFill(w,h,v);
}

/**
 * @brief BinaryImage::BinaryImage Parameterized Constructor
 * @param w  int representing the image width (number of columns)
 * @param h  int representing the image hight (number of rows)
 * @param d  vector of booleans representing image data
 */
BinaryImage::BinaryImage(int w, int h, std::vector<bool> &d) {
    type = CV_8U;
    ch_size = 1;
    AbstractMatrix::Create(w, h, d);
}

/**
 * @brief BinaryImage::operator =
 * @param that  Reference to an existing BinaryImage object
 * @return Updated BinaryImage
 */
BinaryImage &BinaryImage::operator=(const BinaryImage &that) {
    if (that.data.type()!=CV_8U || that.data.channels()!=1) throw  incompatible_parameters();
    type = that.type;
    ch_size = that.ch_size;
    data = that.data.clone();
    return *this;
}

/**
 * @brief BinaryImage::CreateAndFill Create Binary image of specified size anda value
 * @param w  int representing the desired Binary Image width
 * @param h  int representing the desired Binary Image height
 * @param v  bool representing the value for every pixel in the Binary Image
 */
void BinaryImage::CreateAndFill(int w, int h, bool v) {
    Create(w,h);
    Fill(v);
}

/**
 * @brief BinaryImage::Fill  Set every pixel in the BinaryImage to the passed value
 * @param v  bool representing the value for every pixel in the Binary Image
 */
void BinaryImage::Fill(bool v) {
    uchar conv_val = v*255;
    data = cv::Scalar::all(conv_val);
}
/**
 * @brief BinaryImage::Set  Set value of a specific pixel in the image
 * @param x  int representing column index
 * @param y  int representing row index
 * @param v  bool representing the desired value
 */
void BinaryImage::Set(int x, int y, bool v) {
    data.at<uchar>(y,x) = v*255;
}

/**
 * @brief BinaryImage::Get  Get value of a specific pixel in the image
 * @param x  int representing column index
 * @param y  int representing row index
 * @return image value at position (y,x)
 */
bool BinaryImage::Get(int x, int y) {
    return (static_cast<int>(data.at<uchar>(y,x))>128);
}

/**
 * @brief BinaryImage::Not
 * @return Complement of original image
 */
BinaryImage BinaryImage::Not() {
    BinaryImage aux(*this);
    for (int x = 0; x < data.cols; x++) {
        for(int y = 0; y < data.rows; y++) {
            aux.Set(x,y, 1-Get(x,y));
        }
    }
    return aux;
}

/**
 * @brief BinaryImage::And -   true if both arguments are true and false otherwise
 * @param that reference to an existing BinaryImage object
 * @return BinaryImage resulting from the And operation between the two BinaryImages
 */
BinaryImage BinaryImage::And(BinaryImage &that) {
    BinaryImage aux(*this);
    for (int x = 0; x < data.cols; x++) {
        for(int y = 0; y < data.rows; y++) {
            aux.Set(x,y, Get(x,y)&&that.Get(x,y));
        }
    }
    return aux;
}

/**
 * @brief BinaryImage::Or -   true if any of the arguments are true and false otherwise
 * @param that reference to an existing BinaryImage object
 * @return BinaryImage resulting from the Or operation between the two BinaryImages
 */
BinaryImage BinaryImage::Or(BinaryImage &that) {
    BinaryImage aux(*this);
    for (int x = 0; x < data.cols; x++) {
        for(int y = 0; y < data.rows; y++) {
            aux.Set(x,y, Get(x,y)||that.Get(x,y));
        }
    }
    return aux;
}

/**
 * @brief BinaryImage::Xor- if either input is true, then the result is true, but if both inputs are true, then the result is false
 * @param that reference to an existing BinaryImage object
 * @return BinaryImage resulting from the Xor operation between the two BinaryImages
 */
BinaryImage BinaryImage::Xor(BinaryImage &that) {
    BinaryImage aux(*this);
    for (int x = 0; x < data.cols; x++) {
        for (int y = 0; y < data.rows; y++) {
            aux.Set(x,y, Get(x,y)^that.Get(x,y));
        }
    }
    return aux;
}

/**
 * @brief BinaryImage::CountTrues
 * @return  int representing the number of image pixels with true value (>0)
 */
int BinaryImage::CountTrues() {
    int count = 0;
    for (int x = 0; x < data.cols; x++) {
        for (int y = 0; y < data.rows; y++) {
            if (Get(x,y)) count++;
        }
    }
    return count;
}

/**
 * @brief BinaryImage::CountFalses
 * @return  int representing the number of image pixels with false value (0)
 */
int BinaryImage::CountFalses() {
    int count = 0;
    for (int x = 0; x < data.cols; x++) {
        for(int y = 0; y < data.rows; y++) {
            if (!Get(x,y)) count++;
        }
    }
    return count;
}

/**
 * @brief BinaryImage::Erode  Erode the image with given structuring element
 * @param size  int representing Structuring Element size
 * @param etype int representing Structuring Element shape
 * @return Eroded BinaryImage
 */
BinaryImage BinaryImage::Erode(int size, int etype) {
    cv::Size elsize(2*size+1, 2*size+1);
    cv::Mat element = getStructuringElement(etype, elsize, cv::Point(size,size));
    BinaryImage aux;
    cv::erode(data, aux.data, element);
    return aux;
}

/**
 * @brief BinaryImage::SelfErode  Erode the image with given structuring element
 * @param size  int representing Structuring Element size
 * @param etype int representing Structuring Element shape
 */
void BinaryImage::SelfErode(int size, int etype) {
    cv::Size elsize(2*size+1, 2*size+1);
    cv::Mat element = getStructuringElement(etype, elsize, cv::Point(size,size));
    cv::erode(data, data, element);
}

/**
 * @brief BinaryImage::Dilate  Dilate the image with given structuring element
 * @param size  int representing Structuring Element size
 * @param etype int representing Structuring Element shape
 * @return Dilated BinaryImage
 */
BinaryImage BinaryImage::Dilate(int size, int etype) {
    cv::Size elsize(2*size+1, 2*size+1);
    cv::Mat element = getStructuringElement(etype, elsize, cv::Point(size,size));
    BinaryImage aux;
    cv::dilate(data, aux.data, element);
    return aux;
}

/**
 * @brief BinaryImage::SelfDilate  Dilate the image with given structuring element
 * @param size  int representing Structuring Element size
 * @param etype int representing Structuring Element shape
 */
void BinaryImage::SelfDilate(int size, int etype) {
    cv::Size elsize(2*size+1, 2*size+1);
    cv::Mat element = getStructuringElement(etype, elsize, cv::Point(size,size));
    cv::dilate(data, data, element);
}

/**
 * @brief BinaryImage::Warp  Applies a perspective transformation to the image
 * @param pts  vector of PointD representing the coordinates of the points in the original plane
 * @param refs  vector of PointD representing the coordinates of the points in the target plane
 * @param w  int representing the width of the output image
 * @param h  int representing the hight of the output image
 * @return BinaryImage resulting of the transformation
 */
BinaryImage BinaryImage::Warp(std::vector<PointD> &pts, std::vector<PointD> &refs, int w, int h) {
    if (pts.size() != refs.size()) throw  incompatible_parameters();
    if (pts.size() < 4) throw  incompatible_parameters();
    std::vector<cv::Point2f> cv_pts;
    cv_pts.resize(pts.size());
    std::vector<cv::Point2f> cv_refs;
    cv_refs.resize(refs.size());
    for (auto i = 0; i < pts.size(); i++) {
        cv_pts[i].x = pts[i].getX();
        cv_pts[i].y = pts[i].getY();
        cv_refs[i].x = refs[i].getX();
        cv_refs[i].y = refs[i].getY();
    }
    cv::Mat homo_mat;
    // We assume that size>=4 (verified in the begining of the method)
    if (pts.size()>4) {
        homo_mat = cv::findHomography(cv_pts, cv_refs,cv::RANSAC);
    } else {
        homo_mat = cv::findHomography(cv_pts, cv_refs);
    }
    cv::Mat aux1, aux2;
    data.convertTo(aux1, CV_32F);
    cv::warpPerspective(aux1, aux2, homo_mat, cv::Size(w,h));
    aux2.convertTo(aux2, CV_8U);
    BinaryImage rect(aux2);
    return rect;
}

//TODO: when template is outside is always counted as a distance
/**
 * @brief BinaryImage::Compare
 * @param x
 * @param y
 * @param that
 * @return
 */
int BinaryImage::Compare(int x, int y, BinaryImage &that) {
    int dist = 0;
    for (int xx=0; xx<that.GetWidth(); xx++) {
        for (int yy=0; yy<that.GetHeight(); yy++) {
            if ((x+xx>=GetWidth()) || (y+yy>=GetHeight())) dist++;
            else if (Get(x+xx,y+yy)==that.Get(xx,yy)) dist++;
        }
    }
    return dist;
}

//TODO: add mirrorerd and toroidal comparisons
/**
 * @brief BinaryImage::FindBestMatch
 * @param that
 * @return
 */
PointI BinaryImage::FindBestMatch(BinaryImage &that) {
    PointI bp(-1,-1);
    int bd = INT_MAX;
    for (int x=0; x<GetWidth()-that.GetWidth(); x++) {
        for (int y=0; y<GetHeight()-that.GetHeight(); y++) {
            int d = Compare(x,y,that);
            if (d<bd) {
                bd = d;
                bp.Set(x,y);
            }
        }
    }
    return bp;
}

/**
 * @brief BinaryImage::FindBestMatch
 * @param xi
 * @param xf
 * @param yi
 * @param yf
 * @param that
 * @return
 */
PointI BinaryImage::FindBestMatch(int xi, int xf, int yi, int yf, BinaryImage &that) {
    PointI bp(-1,-1);
    int bd = INT_MAX;
    for (int x=xi; x<=xf; x++) {
        for (int y=yi; y<=yf; y++) {
            int d = Compare(x,y,that);
            if (d<bd) {
                bd = d;
                bp.Set(x,y);
            }
        }
    }
    return bp;
}

/**
 * @brief BinaryImage::Open  Load information from file into BinaryImage
 * @param filename string with the file path
 */
void BinaryImage::Open(std::string filename) {
    AbstractMatrix<bool>::data = cv::imread(filename, cv::IMREAD_UNCHANGED);
}

/**
 * @brief BinaryImage::Save  Save information from BinaryImage into file
 * @param filename   string with the file path
 */
void BinaryImage::Save(std::string filename) {
    cv::imwrite(filename, AbstractMatrix<bool>::data);
}

/**
 * @brief BinaryImage::ToRgbImage  Convert BinaryImage to RGB Image
 * @return Resulting RGB Image
 */
RgbImage BinaryImage::ToRgbImage() {
    RgbImage newImage;
    cv::cvtColor(data, newImage.GetData(), cv::COLOR_GRAY2RGB);
    return newImage;

}

} // namespace ctk
