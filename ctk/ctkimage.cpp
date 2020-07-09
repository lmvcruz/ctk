#include "ctkimage.h"

#include <vector>

#include <opencv2/calib3d.hpp>
#include <opencv2/core/types_c.h>

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
    assert(that.data.type()==CV_8U && that.data.channels()==1);
    type = that.type;
    ch_size = that.ch_size;
    data = that.data.clone();
}

/**
 * @brief BinaryImage::BinaryImage  Copy Constructor
 * @param that  Reference to an existing AbstractImage object
 */
BinaryImage::BinaryImage(const AbstractImage<bool> &that) {
    assert(that.get_data().type()==CV_8U
           && that.get_data().channels()==1);
    type = CV_8U;
    ch_size = 1;
    data = that.get_data().clone();
}

/**
 * @brief BinaryImage::BinaryImage
 * @param d
 */
BinaryImage::BinaryImage(cv::Mat &d): AbstractImage<bool>(d) {
    assert(d.type()==CV_8U && d.channels()==1);
}

/**
 * @brief BinaryImage::BinaryImage Constructor that create and fill the image
 * @param w width of the image
 * @param h height of the image
 */
BinaryImage::BinaryImage(int w, int h, bool v)
{
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
    assert(that.data.type()==CV_8U && that.data.channels()==1);
    type = that.type;
    ch_size = that.ch_size;
    data = that.data.clone();
    return *this;
}

/**
 * @brief BinaryImage::CreateAndFill
 * @param w
 * @param h
 * @param v
 */
void BinaryImage::CreateAndFill(int w, int h, bool v)
{
    //TODO: test it
    AbstractMatrix::Create(w,h);
    AbstractMatrix::Fill(v*255);
}

/**
 * @brief BinaryImage::Fill
 * @param v
 */
void BinaryImage::Fill(bool v)
{
    //TODO: test it
    AbstractMatrix::Fill(v*255);
}
/**
 * @brief BinaryImage::set  Set value of a specific pixel in the image
 * @param x  int representing column index
 * @param y  int representing row index
 * @param v  bool representing the desired value
 */
void BinaryImage::set(int x, int y, bool v) {
    data.at<uchar>(y,x) = v*255;
}

/**
 * @brief BinaryImage::get  Get value of a specific pixel in the image
 * @param x  int representing column index
 * @param y  int representing row index
 * @return image value at position (y,x)
 */
bool BinaryImage::get(int x, int y) {
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
            aux.set(x,y, 1-get(x,y));
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
            aux.set(x,y, get(x,y)&&that.get(x,y));
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
            aux.set(x,y, get(x,y)||that.get(x,y));
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
            aux.set(x,y, get(x,y)^that.get(x,y));
        }
    }
    return aux;
}

/**
 * @brief BinaryImage::countTrues
 * @return  int representing the number of image pixels with true value (>0)
 */
int BinaryImage::countTrues() {
    int count = 0;
    for (int x = 0; x < data.cols; x++) {
        for (int y = 0; y < data.rows; y++) {
            if (get(x,y)) count++;
        }
    }
    return count;
}

/**
 * @brief BinaryImage::countFalses
 * @return  int representing the number of image pixels with false value (0)
 */
int BinaryImage::countFalses() {
    int count = 0;
    for (int x = 0; x < data.cols; x++) {
        for(int y = 0; y < data.rows; y++) {
            if (!get(x,y)) count++;
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
    //TODO: replace assert to exceptions
    assert(pts.size()==refs.size());
    assert(pts.size()>=4);
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
int BinaryImage::Compare(int x, int y, BinaryImage &that)
{
    int dist = 0;
    for (int xx=0; xx<that.width(); xx++) {
        for (int yy=0; yy<that.height(); yy++) {
            if ((x+xx>=width()) || (y+yy>=height())) dist++;
            else if (get(x+xx,y+yy)==that.get(xx,yy)) dist++;
        }
    }
    return dist;
}

//TODO: add mirrorerd and toroidal comparisons
PointI BinaryImage::FindBestMatch(BinaryImage &that)
{
    PointI bp(-1,-1);
    int bd = INT_MAX;
    for (int x=0; x<width()-that.width(); x++) {
        for (int y=0; y<height()-that.height(); y++) {
            int d = Compare(x,y,that);
            if (d<bd) {
                bd = d;
                bp.set(x,y);
            }
        }
    }
    return bp;
}

PointI BinaryImage::FindBestMatch(int xi, int xf, int yi, int yf, BinaryImage &that)
{
    PointI bp(-1,-1);
    int bd = INT_MAX;
    for (int x=xi; x<=xf; x++) {
        for (int y=yi; y<=yf; y++) {
            int d = Compare(x,y,that);
            if (d<bd) {
                bd = d;
                bp.set(x,y);
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
 * @brief BinaryImage::Show  Show BinaryImage TODO
 */
void BinaryImage::Show() {
    std::cout << "TODO" << std::endl;
}


/**
 * @brief BinaryImage::toRgbImage  Convert BinaryImage to RGB Image
 * @return Resulting RGB Image
 */
RgbImage BinaryImage::toRgbImage() {
    RgbImage newImage;
    cv::cvtColor(data, newImage.get_data(), cv::COLOR_GRAY2RGB);
    return newImage;

}

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
    assert(that.data.type()==CV_8UC1 && that.data.channels()==1); //TODO replace with exception
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
    if (that.get_data().channels()==3) {
        cv::cvtColor(that.get_data(), data, cv::COLOR_RGB2GRAY);
    } else {
        data = that.get_data().clone();
    }
    type = CV_8UC1;
    ch_size = 1;
    invert_channels_ = false;
    assert(data.type()==CV_8UC1 && data.channels()==1);
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
    assert(data.type()==CV_8UC1 && data.channels()==1);
}


/**
 * @brief GrayImage::operator = Operator Copy
 * @param that reference to existing GrayImage object
 * @return Updated GrayImage
 */
GrayImage &GrayImage::operator=(const GrayImage &that) {
    assert(that.data.type()==CV_8UC1 && that.data.channels()==1);  //TODO replace with exception
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
    assert(data.type()==CV_8UC1 && data.channels()==1);  //TODO replace with exception
    return *this;
}

/**
 * @brief GrayImage::operator =  Operator Copy
 * @param that  reference to existing AbstractImage object
 * @return Updated GrayImage
 */
GrayImage &GrayImage::operator=(const AbstractImage<uchar> &that) {
    if (that.get_data().channels()==3) {
        cv::cvtColor(that.get_data(), data, cv::COLOR_RGB2GRAY);
    } else {
        data = that.get_data().clone();
    }
    type = CV_8UC1;
    ch_size = 1;
    invert_channels_ = false;
    assert(data.type()==CV_8UC1 && data.channels()==1);
    return *this;
}

/**
 * @brief GrayImage::Open
 * @param filename
 */
void GrayImage::Open(std::string filename)
{
    data = cv::imread(filename, cv::IMREAD_UNCHANGED);
    if (data.channels()==3) cv::cvtColor(data, data, cv::COLOR_RGB2GRAY);
}

/**
 * @brief GrayImage::channels  Get gray image channels
 * @return 1
 */
int GrayImage::channels() {
    return 1;
}

/**
 * @brief GrayImage::toRgbImage - Convert gray image to RGB image
 * @return RGB Image
 */
RgbImage GrayImage::toRgbImage() {
    RgbImage newImage;
    cv::cvtColor(data, newImage.get_data(), cv::COLOR_GRAY2BGR);
    return newImage;
}

/**
 * @brief GrayImage::ApplyBinaryThreshold-  Binarize image according to passed threshold
 * @param t  int representing the desired threshold
 * @return Binary Image resulting from the application of t to the original image
 */
BinaryImage GrayImage::ApplyBinaryThreshold(int t) {
    BinaryImage newImage;
    threshold(data, newImage.get_data(), t, 255, 0);
    return newImage;
}


/**
 * @brief GrayImage::ApplyOtsuThreshold- use Otsu algorithm to choose the optimal threshold value
 * @return Binary Image resulting from the application of the Otsu threshold to the original image
 */
BinaryImage GrayImage::ApplyOtsuThreshold() {
    BinaryImage newImage;
    threshold(data, newImage.get_data(), 0, 255, cv::THRESH_OTSU);
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
    //TODO: replace asserts to exceptions
    assert(minv>=0);
    assert(maxv<=255);
    assert(minv<maxv);
    GrayImage norm;
    norm.Create(width(), height());
    int cmin = 255;
    int cmax = 0;
    for (auto x = 0; x < data.rows; x++) {
        for (auto y = 0; y < data.cols; y++) {
            int ic = static_cast<int>(get(x,y));
            cmin = std::min(cmin, ic);
            cmax = std::max(cmax, ic);
        }
    }
    float scale = static_cast<float>(maxv-minv) / static_cast<float>(cmax-cmin);
    for (auto x = 0; x < data.rows; x++) {
        for (auto y = 0; y < data.cols; y++) {
            int ic = static_cast<int>(get(x,y));
            float c = static_cast<float>(ic-cmin+minv)*scale;
            norm.set(x,y,static_cast<uchar>(c));
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
    mask.Create(width(), height());
    for (auto x = 0; x < data.rows; x++) {
        for (auto y = 0; y < data.cols; y++) {
            if (static_cast<int>(get(x,y)) == c) {
                mask.set(x,y,true);
            } else {
                mask.set(x,y,false);
            }
        }
    }
    return mask;
}

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
    assert(that.data.type()==CV_8UC3 && that.data.channels()==3); //TODO: replace with exception
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
    assert(that.get_data().type()==CV_8UC3
           && that.get_data().channels()==3); //TODO: replace with exception
    type = CV_8UC3;
    ch_size = 3;
    invert_channels_ = false;
    data = that.get_data().clone();
}

/**
 * @brief ColorImage::ColorImage
 * @param d
 */
ColorImage::ColorImage(cv::Mat &d) : AbstractImage<cv::Vec3b>(d) {
    assert(d.type()==CV_8UC3 && d.channels()==3); //TODO: replace with exception
}

/**
 * @brief ColorImage::channels Get color image channels
 * @return 3
 */
int ColorImage::channels() {
    return 3;
}

/**
 * @brief RgbImage::RgbImage
 */
RgbImage::RgbImage() : ColorImage() {
    invert_channels_ = true;
}

/**
 * @brief RgbImage::RgbImage - Copy Construtor
 * @param that reference to an existing RgbImage
 */
RgbImage::RgbImage(const RgbImage &that) {
    assert(that.data.type()==CV_8UC3 && that.data.channels()==3); //TODO: replace with exception
    type = that.type;
    ch_size = that.ch_size;
    invert_channels_ = true;
    data = that.data.clone();
}

/**
 * @brief RgbImage::RgbImage - Copy Construtor
 * @param that  reference to an existing AbstractImage
 */
RgbImage::RgbImage(const AbstractImage<cv::Vec3b> &that) {
    assert(that.get_data().type()==CV_8UC3
           && that.get_data().channels()==3); //TODO: replace with exception
    type = CV_8UC3;
    ch_size = 3;
    invert_channels_ = true;
    data = that.get_data().clone();
}

/**
 * @brief RgbImage::RgbImage
 * @param d
 */
RgbImage::RgbImage(cv::Mat &d) : ColorImage(d) {
    assert(d.type()==CV_8UC3 && d.channels()==3); //TODO: replace with exception
}

/**
 * @brief RgbImage::Create - Create RgbImage
 * @param w  int representing the image width (number of columns)
 * @param h  int representing the image hight (number of rows)
 */
void RgbImage::Create(int w, int h) {
    ColorImage::Create(w,h);
}

/**
 * @brief RgbImage::set - Set value of image pixel
 * @param x int representing the column index
 * @param y int representing the row index
 * @param r int representing the desired red value
 * @param g int representing the desired green value
 * @param b int representing the desired blue value
 */
void RgbImage::set(int x, int y, int r, int g, int b) {
    unsigned char ucr = static_cast<unsigned char>(r);
    unsigned char ucg = static_cast<unsigned char>(g);
    unsigned char ucb = static_cast<unsigned char>(b);
    AbstractMatrix<cv::Vec3b>::set(x, y, cv::Vec3b(ucr,ucg,ucb));
}

/**
 * @brief RgbImage::safe_set - Set value of image pixel
 * @param x int representing the column index
 * @param y int representing the row index
 * @param r int representing the desired red value
 * @param g int representing the desired green value
 * @param b int representing the desired blue value
 */
void RgbImage::safe_set(int x, int y, int r, int g, int b) {
    unsigned char ucr = static_cast<unsigned char>(r);
    unsigned char ucg = static_cast<unsigned char>(g);
    unsigned char ucb = static_cast<unsigned char>(b);
    AbstractMatrix<cv::Vec3b>::safe_set(x, y, cv::Vec3b(ucr,ucg,ucb));
}

/**
 * @brief RgbImage::safe_iset
 * @param i int representing the desired index in vector indices_
 * @param r int representing the desired red value
 * @param g int representing the desired green value
 * @param b int representing the desired blue value
 */
void RgbImage::safe_iset(int i, int r, int g, int b) {
    unsigned char ucr = static_cast<unsigned char>(r);
    unsigned char ucg = static_cast<unsigned char>(g);
    unsigned char ucb = static_cast<unsigned char>(b);
    AbstractImage<cv::Vec3b>::safe_iset(i, cv::Vec3b(ucr,ucg,ucb));
}

/**
 * @brief RgbImage::set
 * @param i int representing the desired index in vector indices_
 * @param r int representing the desired red value
 * @param g int representing the desired green value
 * @param b int representing the desired blue value
 */
void RgbImage::set(int i, int r, int g, int b) {
    unsigned char ucr = static_cast<unsigned char>(r);
    unsigned char ucg = static_cast<unsigned char>(g);
    unsigned char ucb = static_cast<unsigned char>(b);
    AbstractImage<cv::Vec3b>::iset(i, cv::Vec3b(ucr,ucg,ucb));
}

/**
 * @brief RgbImage::red Get red value of a pixel
 * @param x int representing the row index
 * @param y int representing the column index
 * @return int representing the red value of the pixel at (x,y)
 */
int RgbImage::red(int x, int y) {
    return AbstractMatrix<cv::Vec3b>::get(x,y)[0];
}

/**
 * @brief RgbImage::green Get green value of a pixel
 * @param x int representing the row index
 * @param y int representing the column index
 * @return int representing the green value of the pixel at (x,y)
 */
int RgbImage::green(int x, int y) {
    return AbstractMatrix<cv::Vec3b>::get(x,y)[1];
}


/**
 * @brief RgbImage::blue Get blue value of a pixel
 * @param x int representing the row index
 * @param y int representing the column index
 * @return int representing the blue value of the pixel at (x,y)
 */
int RgbImage::blue(int x, int y) {
    return AbstractMatrix<cv::Vec3b>::get(x,y)[2];
}

/**
 * @brief RgbImage::get_pixel
 * @param x int representing the row index
 * @param y int representing the column index
 * @return Point representing the pixel at (x,y)
 */
PointI RgbImage::get_pixel(int x, int y) {
    return PointI(red(x,y), green(x,y), blue(x,y));
}

/**
 * @brief RgbImage::Quantize
 * @param q int representing the number of clusters for the kmeans algorithm
 * @param iter int representing the maximum number of iterations for the termination criteria in the kmeans algorithm
 * @param eps float representing the desired accuracy for the termination criteria in the kmeans algorithm
 * @param attempts int representing the number of times the kmeans algorithm is executed using different initial labellings
 * @param qtype int specifying the method of selecting the first centers
 * @return RgbImage obtained after kmeans clustering of original image
 */
RgbImage RgbImage::Quantize(int q, int iter, float eps, int attempts, int qtype) {
    RgbImage cluster(data);
    cv::Mat vals;
    cluster.data.convertTo(vals,CV_32F);
    vals = vals.reshape(1,vals.total());

    cv::Mat labels, centers;
    cv::TermCriteria crit(CV_TERMCRIT_ITER, iter, eps);
    kmeans(vals, q, labels, crit, attempts, qtype, centers);
    // reshape both to a single row of Vec3f pixels:
    centers = centers.reshape(3,centers.rows);
    vals = vals.reshape(3,vals.rows);
    // replace pixel values with their center value:
    cv::Vec3f *p = vals.ptr<cv::Vec3f>();
    for (size_t i = 0; i < vals.rows; i++) {
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
 * @brief RgbImage::PickColor  Get binary mask for specified color
 * @param r int representing the red value
 * @param g int representing the green value
 * @param b int representing the blue value
 * @return BinaryImage consisting of a mask of the original image which is 1 for the passed color and 0 otherwise
 */
BinaryImage RgbImage::PickColor(int r, int g, int b) {
    BinaryImage mask;
    mask.Create(width(), height());
    for (auto x = 0; x < data.rows; x++) {
        for (auto y = 0; y < data.cols; y++) {
            if ((red(x,y) == r) && (green(x,y) == g) && (blue(x,y) == b)) {
                mask.set(x,y,true);
            } else {
                mask.set(x,y,false);
            }
        }
    }
    return mask;
}

/**
 * @brief RgbImage::Project
 * @param colors vector of PointI where each element represents a color
 * @return GrayImage for each pixel in the original image assigns the index of the most similar color in the passed vector
 */
GrayImage RgbImage::Project(std::vector<PointI> &colors) {
    // TODO: replace it to an exception
    assert(colors.size()<=256);

    GrayImage mask;
    mask.Create(width(), height());
    for (auto x = 0; x < data.rows; x++) {
        for (auto y = 0; y < data.cols; y++) {
            int idx = -1;
            float dist = FLT_MAX;
            for (auto i = 0; i < colors.size(); i++) {
                float d = colors[i].Distance(get_pixel(x,y));
                if (d < dist) {
                    dist = d;
                    idx = i;
                }
            }
            mask.set(x, y, idx);
        }
    }
    return mask;
}

/**
 * @brief RgbImage::Contours Get image contours
 * @return vector of Polygons with the image contours
 */
std::vector<Polygon> RgbImage::Contours() {
    BinaryImage bin = toGrayImage().ApplyOtsuThreshold();

    std::vector<std::vector<cv::Point> > cv_contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(bin.get_data(), cv_contours, hierarchy,
                     cv::RETR_TREE, cv::CHAIN_APPROX_TC89_KCOS);

    std::vector<Polygon> ctk_contours;
    ctk_contours.resize(cv_contours.size());
    for (auto i=0; i<cv_contours.size(); i++) {
        ctk_contours[i] = cv_contours[i];
    }
    return ctk_contours;
}

/**
 * @brief RgbImage::ApproximateContours  Get approximate image contours
 * @param eps int specifying the approximation accuracy. The maximum distance between the original polygon and its approximation.
 * @return vector of Polygons with the approximate image contours
 */
std::vector<Polygon> RgbImage::ApproximateContours(int eps) {
    BinaryImage bin = toGrayImage().ApplyOtsuThreshold();

    std::vector<std::vector<cv::Point> > cv_contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(bin.get_data(), cv_contours, hierarchy,
                     cv::RETR_TREE, cv::CHAIN_APPROX_TC89_KCOS);

    std::vector<Polygon> ctk_contours;
    ctk_contours.resize(cv_contours.size());
    for (auto i = 0; i < cv_contours.size(); i++) {
        std::vector<cv::Point> approx;
        approxPolyDP(cv::Mat(cv_contours[i]), approx, eps, true);
        ctk_contours[i] = approx;
    }
    return ctk_contours;
}

//TODO: write tests and benchmark
/**
 * @brief RgbImage::Warp  Applies a perspective transformation to the image
 * @param pts  vector of PointD representing the coordinates of the points in the original plane
 * @param refs  vector of PointD representing the coordinates of the points in the target plane
 * @param w  int representing the width of the output image
 * @param h  int representing the hight of the output image
 * @return RgbImage resulting of the transformation
 */
RgbImage RgbImage::Warp(std::vector<PointD> &pts, std::vector<PointD> &refs, int w, int h) {
    //TODO: replace assert to exceptions
    assert(pts.size() == refs.size());
    assert(pts.size() >= 4);

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
    if (pts.size() > 4) {
        homo_mat = cv::findHomography(cv_pts, cv_refs,cv::RANSAC);
    } else {
        homo_mat = cv::findHomography(cv_pts, cv_refs);
    }
    //
    RgbImage rect;
    cv::warpPerspective(data, rect.get_data(), homo_mat, cv::Size(w,h));
    return rect;
}

/**
 * @brief RgbImage::toGrayImage  convert to gray image
 * @return GrayImage
 */
GrayImage RgbImage::toGrayImage() {
    GrayImage newImage;
    cv::cvtColor(data, newImage.get_data(), cv::COLOR_RGB2GRAY);
    return newImage;
}

/**
 * @brief RgbImage::DrawPolygon
 * @param pol  Polygon respresenting the contour to draw
 * @return RgbImage image with drawn contour
 */
RgbImage RgbImage::DrawPolygon(Polygon &pol) {
    std::vector<std::vector<cv::Point>> cv_conts;
    cv_conts.resize(1);
    cv_conts[0] = pol.get_cvdata();
    std::cout << cv_conts[0].size() << " " << contourArea(cv_conts[0]) << std::endl;

    RgbImage new_img(data);
    cv::Mat &new_mat = new_img.get_data();
    const int  kThickness  = 2;
    const int  kLineType   = 8;
    cv::Scalar color = cv::Scalar(rand()%255, rand()%255, rand()%255);
    cv::drawContours(new_mat,cv_conts, 0, color, kThickness, kLineType);
    return new_img;
}

}

