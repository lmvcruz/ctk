#ifndef CTKABSTRACTIMAGE_H
#define CTKABSTRACTIMAGE_H

#include <iostream>

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "ctkabstractmatrix.h"
#include "ctkpoint.h"
#include "ctkpolygon.h"

namespace ctk {

class BinaryImage;
class GrayImage;
class RgbImage;
class HsvImage;
class HlsImage;
class LabImage;
class RgbaImage;
class BgraImage;


/**
 * @brief The AbstractImage class
 */
template <class T>
class AbstractImage : public AbstractMatrix<T>
{
protected:
    std::vector<unsigned int> indices_;
    int curr_iter_idx;

    bool invert_channels_;

public:
    using AbstractMatrix<T>::get;
    using AbstractMatrix<T>::set;

    /**
     * @brief AbstractImage Default Constructor
     */
    AbstractImage() {
        AbstractMatrix<T>::type = -1;
        AbstractMatrix<T>::ch_size = -1;
        //
        invert_channels_ = false;
    }

    /**
     * @brief AbstractImage Parameterized Constructor
     * @param d matrix
     */
    AbstractImage(cv::Mat &d) : AbstractMatrix<T>(d){
        AbstractMatrix<T>::type = d.type();
        AbstractMatrix<T>::ch_size = d.channels();
        //
        invert_channels_ = false;
    }

    /**
     * @brief ~AbstractImage Destructor
     */
    virtual ~AbstractImage(){}

    /**
     * @brief startScanIndices TODO
     */
    void StartScanIndices() {
        int w = AbstractMatrix<T>::width();
        int h = AbstractMatrix<T>::height();
        indices_.resize(static_cast<unsigned int>(AbstractMatrix<T>::size()));
        for (int y=0; y<h; y++) {
            for (int x=0; x<w; x++) {
                unsigned int idx = static_cast<unsigned int>(y*w+x);
                indices_[idx] = idx;
            }
        }
    }

    /**
     * @brief startSnakeIndices TODO
     */
    void StartSnakeIndices() {
        int w = AbstractMatrix<T>::width();
        int h = AbstractMatrix<T>::height();
        indices_.resize(AbstractMatrix<T>::size());
        for (int y=0; y<h; y++) {
            for (int x=0; x<w; x++) {
                indices_[y*w+x] = y*w+x;
            }
        }
        for (int y=0; y<h; y++) {
            for (int x=0; x<w; x++) {
                indices_[y*w+x] = y*w+x;
            }
            y++;
            if (y<h) {
                for (int x=0; x<w; x++) {
                    indices_[y*w+x] = y*w + w-1-x;
                }
            }
        }
    }

    /**
     * @brief startSpiralIndices TODO
     */
    void StartSpiralIndices() {
        int w = AbstractMatrix<T>::width();
        int h = AbstractMatrix<T>::height();
        indices_.resize(AbstractMatrix<T>::size());
        int ptIndex = 0;
        for (int i=0; ptIndex<w*h; i++) {
            int layer = static_cast<int>( std::floor(std::sqrt(float(i))) );
            int indexInLayer = i - layer * (layer + 1);
            int x = layer + std::min(indexInLayer, 0);
            int y = layer - std::max(indexInLayer, 0);
            if (layer % 2 == 0) {
                int tmp = y;
                y = x;
                x = tmp;
            }
            if (x>=w || y>=h) {
                continue;
            }
            indices_[ptIndex] = y*w+x;
            ptIndex++;
        }
    }

    /**
     * @brief startSnailIndices TODO
     */
    void StartSnailIndices() {
        int w = AbstractMatrix<T>::width();
        int h = AbstractMatrix<T>::height();
        int s = w*h;
        indices_.resize(s);
        int y = 0;
        int x = -1;
        int nextturn = w;
        int stepsx = w;
        int stepsy = h-1;
        int inc_c = 1;
        int inc_r = 0;
        int turns = 0;
        for (int i=0; i<s; i++) {
            x += inc_c;
            y += inc_r;
            indices_[i] = y*w+x;
            if (i == nextturn-1) {
                turns += 1;
                if (turns%2==0) {
                    nextturn += stepsx;
                    stepsy -= 1;
                }
                else {
                    nextturn += stepsy;
                    stepsx -= 1;
                }
                int tmp = inc_c;
                inc_c = -inc_r;
                inc_r = tmp;
            }
        }
    }

    /**
     * @brief startCustomIndices TODO
     * @param vec TODO
     */
    void StartCustomIndices(std::vector<unsigned int> &vec) {
        indices_ = vec;
    }

    /**
     * @brief StartCustomIndices
     * @param vec
     */
    void StartCustomIndices(std::vector<int> &vec) {
        indices_.resize(vec.size());
        for (auto i=0; i<vec.size(); i++) {
            indices_[i] = static_cast<unsigned int>(vec[i]);
        }
    }

    /**
     * @brief isIndices TODO
     * @return  TODO
     */
    bool isIndices() {
        return (indices_.size()>0);
    }

    /**
     * @brief get  Get specific element in AbstractMatrix
     * @param i int representing the desired index in vector indices_
     * @return AbstractMatrix element at  position = indices_(i)
     */
    T iget(int i) {
        unsigned int ui = static_cast<unsigned int>(i);
        int int_indx = static_cast<int>(indices_[ui]);
        int y = int_indx/AbstractMatrix<T>::data.cols;
        int x = int_indx%AbstractMatrix<T>::data.rows;
        return AbstractMatrix<T>::get(x,y);
    }

    /**
     * @brief safe_get Get specific element in AbstractMatrix
     * @param i int representing the desired index in vector indices_
     * @return AbstractMatrix element at  position = indices_(i)
     */
    T safe_iget(int i) {
        if (!isIndices()) StartScanIndices();
        int isize = static_cast<int>(indices_.size());
        if (i<0 || i>=isize) {
            throw std::out_of_range("Exception thrown in AbstractImage::safe_set");
        }
        unsigned int ui = static_cast<unsigned int>(i);
        int int_indx = static_cast<int>(indices_[ui]);
        int y = int_indx/AbstractMatrix<T>::data.cols;
        int x = int_indx%AbstractMatrix<T>::data.rows;
        return AbstractMatrix<T>::get(x,y);
    }

    /**
     * @brief set  Set specific element in AbstractMatrix
     * @param i int representing the desired index in vector indices_
     * @param v desired value
     */
    void iset(int i, T v) {
        unsigned int ui = static_cast<unsigned int>(i);
        int int_idx = static_cast<int>(indices_[ui]);
        int y = int_idx/AbstractMatrix<T>::data.cols;
        int x = int_idx%AbstractMatrix<T>::data.rows;
        AbstractMatrix<T>::set(x,y,v);
    }

    /**
     * @brief safe_iset  Set specific element in AbstractMatrix
     * @param i int representing the desired index in vector indices_
     * @param v desired value
     */
    void safe_iset(int i, T v) {
        if (!isIndices()) StartScanIndices();
        int isize = static_cast<int>(indices_.size());
        if (i<0 || i>=isize) {
            throw std::out_of_range("Exception thrown in AbstractImage::safe_set");
        }
        unsigned int ui = static_cast<unsigned int>(i);
        int int_indx = static_cast<int>(indices_[ui]);
        int y = int_indx/AbstractMatrix<T>::data.cols;
        int x = int_indx%AbstractMatrix<T>::data.rows;
        AbstractMatrix<T>::set(x,y,v);
    }

    /**
     * @brief Crop
     * @param x int representing the x coordinate of the top-left corner
     * @param y int representing the y coordinate of the top-left corner
     * @param w width of the rectangle
     * @param h height of the rectangle
     * @return  Cropped image containing the desired rgion
     */
    AbstractImage<T> Crop(int x, int y, int w, int h) {
        cv::Rect roi(x,y,w,h);
        cv::Mat aux = AbstractMatrix<T>::data(roi);
        return AbstractImage<T>(aux);
    }

    /**
     * @brief SelfCrop TODO
     * @param x int representing the x coordinate of the top-left corner
     * @param y int representing the y coordinate of the top-left corner
     * @param w width of the rectangle
     * @param h height of the rectangle
     */
    void SelfCrop(int x, int y, int w, int h) {
        cv::Rect roi(x,y,w,h);
        AbstractMatrix<T>::data = AbstractMatrix<T>::data(roi).clone();
    }

    /**
     * @brief FlipHorizontally
     * @return  Image flipped arround the horizontal axis
     */
    AbstractImage<T> FlipHorizontally() {
        cv::Mat aux;
        cv::flip(AbstractMatrix<T>::data, aux, +1);
        return AbstractImage<T>(aux);
    }

    /**
     * @brief SelfFlipHorizontally - flips the image arround the horizontal axis
     */
    void SelfFlipHorizontally()
    {
        cv::flip(AbstractMatrix<T>::data, AbstractMatrix<T>::data, +1);
    }

    /**
     * @brief FlipVertically
     * @return  Image flipped arround the vertical axis
     */
    AbstractImage<T> FlipVertically() {
        cv::Mat aux;
        cv::flip(AbstractMatrix<T>::data, aux, 0);
        return AbstractImage<T>(aux);
    }

    /**
     * @brief SelfFlipVertically flips the image arround the vertical axis
     */
    void SelfFlipVertically()
    {
        cv::flip(AbstractMatrix<T>::data, AbstractMatrix<T>::data, 0);
    }

    /**
     * @brief FlipBoth
     * @return  Image flipped arround both the vertical and horizontal axis
     */
    AbstractImage<T> FlipBoth() {
        cv::Mat aux;
        cv::flip(AbstractMatrix<T>::data, aux, -1);
        return AbstractImage<T>(aux);
    }

    /**
     * @brief SelfFlipBoth flips image arround both the vertical and horizontal axis
     */
    void SelfFlipBoth()
    {
        cv::flip(AbstractMatrix<T>::data, AbstractMatrix<T>::data, -1);
    }

    /**
     * @brief Rotate90
     * @return  Image rotated by 90º clockwise
     */
    AbstractImage<T> Rotate90() {
        cv::Mat aux;
        cv::transpose(AbstractMatrix<T>::data, aux);
        cv::flip(aux, aux, +1);
        return AbstractImage<T>(aux);
    }

    /**
     * @brief SelfRotate90 rotates image by 90º clockwise
     */
    void SelfRotate90()
    {
        cv::transpose(AbstractMatrix<T>::data, AbstractMatrix<T>::data);
        cv::flip(AbstractMatrix<T>::data, AbstractMatrix<T>::data, +1);
    }

    /**
     * @brief Rotate180
     * @return  Image rotated by 180º clockwise
     */
    AbstractImage<T> Rotate180() {
        cv::Mat aux;
        cv::flip(AbstractMatrix<T>::data, aux, -1);
        return AbstractImage<T>(aux);
    }

    /**
     * @brief SelfRotate180 rotates image by 180º clockwise
     */
    void SelfRotate180()
    {
        cv::flip(AbstractMatrix<T>::data, AbstractMatrix<T>::data, -1);
    }

    /**
     * @brief Rotate270 TODO
     * @return  Image rotated by 270º clockwise
     */
    AbstractImage<T> Rotate270() {
        cv::Mat aux;
        cv::transpose(AbstractMatrix<T>::data, aux);
        cv::flip(aux, aux, 0);
        return AbstractImage<T>(aux);
    }

    /**
     * @brief SelfRotate270 rotates image by 270º clockwise
     */
    void SelfRotate270()
    {
        cv::transpose(AbstractMatrix<T>::data, AbstractMatrix<T>::data);
        cv::flip(AbstractMatrix<T>::data, AbstractMatrix<T>::data, 0);
    }

    /**
     * @brief resize - change image size
     * @param nw int representing new width
     * @param nh int representing new hight
     * @return Resized image
     */
    AbstractImage<T> resize(int nw, int nh) {
        cv::Mat aux;
        cv::resize(AbstractMatrix<T>::data, aux, cv::Size(nw,nh), cv::INTER_CUBIC);
        return AbstractImage<T>(aux);
    }

    /**
     * @brief Open Read information from file
     * @param filename TODO
     */
    void Open(std::string filename) {
        AbstractMatrix<T>::data = cv::imread(filename, cv::IMREAD_UNCHANGED);
        if (invert_channels_) {
            cv::cvtColor(AbstractMatrix<T>::data,
                         AbstractMatrix<T>::data,
                         cv::COLOR_RGB2BGR);
        }
    }

    /**
     * @brief Save Save information to file
     * @param filename TODO
     */
    void Save(std::string filename) {
        cv::imwrite(filename, AbstractMatrix<T>::data);
        if(invert_channels_) {
            cv::Mat aux;
            cv::cvtColor(AbstractMatrix<T>::data,
                         aux, cv::COLOR_RGB2BGR);
            cv::imwrite(filename, aux);
        }
    }

    /**
     * @brief Show TODO
     */
    void Show() {
        //TODO: implement it
        std::cout << "TODO" << std::endl;
    }
};

class BinaryImage : public AbstractImage<bool>
{
public:
    BinaryImage();
    BinaryImage(const BinaryImage& that);
    BinaryImage(const AbstractImage<bool>& that);
    BinaryImage(cv::Mat& d);
    BinaryImage(int w, int h, std::vector<bool>& d);

    BinaryImage &operator=(const BinaryImage& that);

    void set(int x, int y, bool v);
    bool get(int x, int y);

    BinaryImage Not();
    BinaryImage And(BinaryImage& that);
    BinaryImage Or(BinaryImage& that);
    BinaryImage Xor(BinaryImage& that);

    //TODO: Implement Self methods of Logic Operations

    int countTrues();
    int countFalses();

    //TODO: test and benchmark these methods;
    //TODO: replace type by an internal enum
    BinaryImage Erode(int size, int etype=cv::MORPH_RECT);
    void SelfErode(int size, int etype=cv::MORPH_RECT);
    BinaryImage Dilate(int size, int etype=cv::MORPH_RECT);
    void SelfDilate(int size, int etype=cv::MORPH_RECT);

    BinaryImage Warp(std::vector<PointD> &pts, std::vector<PointD> &refs, int w, int h);

    void Open(std::string filename);
    void Save(std::string filename);
    void Show();

    RgbImage toRgbImage();
};

/**
 * @brief The GrayImage class
 */
class GrayImage : public AbstractImage<uchar>
{
public:
    GrayImage();
    GrayImage(const GrayImage& that);
    GrayImage(const AbstractImage<uchar>& that);
    GrayImage(cv::Mat& d);
    virtual ~GrayImage(){}

    GrayImage &operator=(const GrayImage& that);
    GrayImage& operator=(const cv::Mat& that);
    GrayImage &operator=(const AbstractImage<uchar>& that);

    int channels();

    BinaryImage ApplyBinaryThreshold(int t=127);
    BinaryImage ApplyOtsuThreshold();
    BinaryImage ApplyAdaptativeThreshold(int bs=5, int c=1);

    GrayImage Truncate(int t=128);

    GrayImage Normalize(int minv, int maxv);
    BinaryImage PickColor(int c);

    RgbImage toRgbImage();
};


class ColorImage : public AbstractImage<cv::Vec3b>
{
public:
    ColorImage();
    ColorImage(const ColorImage& that);
    ColorImage(const AbstractImage<cv::Vec3b>& that);
    ColorImage(cv::Mat& d);

    virtual ~ColorImage(){}

    int channels();
};

class RgbImage : public ColorImage
{
public:
    using AbstractMatrix<cv::Vec3b>::get;
    using AbstractMatrix<cv::Vec3b>::set;

    RgbImage();
    RgbImage(const RgbImage& that);
    RgbImage(const AbstractImage<cv::Vec3b>& that);
    RgbImage(cv::Mat& d);

    void Create(int w, int h);
    void set(int x, int y, int r, int g, int b);
    void set(int i, int r, int g, int b);

    void safe_set(int x, int y, int r, int g, int b);
    void safe_iset(int i, int r, int g, int b);
    int red(int x, int y);
    int green(int x, int y);
    int blue(int x, int y);

    //TODO: test and benchmark these methods;
    PointI get_pixel(int x, int y);

    //TODO: test and benchmark these methods;
    //TODO: replace type by an internal enum
    RgbImage Quantize(int q, int iter=10, float eps=1.0, int attempts=3,
                      int qtype=cv::KMEANS_PP_CENTERS);
    RgbImage Quantize(std::vector<PointI> &centers, int iter=10,
                      float eps=1.0, int attempts=3);


    BinaryImage PickColor(int r, int g, int b);
    GrayImage Project(std::vector<PointI> &centers);

    // TODO: create a classe for contours (avoiding copy to PointI)
    std::vector<Polygon> Contours();
    std::vector<Polygon> ApproximateContours(int eps=3);
    RgbImage Warp(std::vector<PointD> &pts, std::vector<PointD> &refs, int w, int h);

    GrayImage toGrayImage();

    RgbImage DrawPolygon(Polygon &pol);

    //TODO: NEXT SPRINT
//    HsvImage toHsvImage();
//    HlsImage toHslImage();
//    LabImage toLabImage();
//    RgbaImage toRgbaImage();
//    BgraImage toBgraImage();


//    friend class HsvImage;
//    friend class HlsImage;
//    friend class LabImage;
//    friend class RgbaImage;
//    friend class BgraImage;
};

//TODO: NEXT SPRINT
//class HsvImage : public ColorImage
//{
//public:
//    HsvImage() = default;

//    void create(int w, int h);

//    using AbstractMatrix<cv::Vec3b>::set;
//    void set(int x, int y, int h, int s, int v);
//    void set(int i, int h, int s, int v);
//    int hue(int x, int y);
//    int saturation(int x, int y);
//    int value(int x, int y);

//    RgbImage toRgbImage();

//    friend class RgbImage;
//};

//TODO: NEXT SPRINT
//class HlsImage : public ColorImage
//{
//public:
//    HlsImage() = default;

//    void create(int w, int h);

//    using AbstractMatrix<cv::Vec3b>::set;
//    void set(int x, int y, int h, int l, int s);
//    void set(int i, int h, int l, int s);
//    int hue(int x, int y);
//    int luminance(int x, int y);
//    int saturation(int x, int y);

//    RgbImage toRgbImage();

//    friend class RgbImage;
//};

//TODO: NEXT SPRINT
//class LabImage : public ColorImage
//{
//public:
//    LabImage() = default;

//    void create(int w, int h);

//    using AbstractMatrix<cv::Vec3b>::set;
//    void set(int x, int y, int l, int a, int b);
//    void set(int i, int l, int a, int b);
//    int lightness(int x, int y);
//    int a_value(int x, int y);
//    int b_value(int x, int y);

//    RgbImage toRgbImage();

//    friend class RgbImage;
//};

//TODO: NEXT SPRINT (Use only one RgbaImage class
//class ColorAlphaImage : public AbstractImage<cv::Vec4b>
//{
//public:
//    ColorAlphaImage();
//    virtual ~ColorAlphaImage(){}

//    int channels();

//    void fill();
//};

//TODO: NEXT SPRINT
//class RgbaImage : public ColorAlphaImage
//{
//public:
//    RgbaImage() = default;

//    using AbstractMatrix<cv::Vec4b>::set;
//    void set(int x, int y, int r, int g, int b, int a);
//    void set(int i, int r, int g, int b, int a);
//    int red(int x, int y);
//    int green(int x, int y);
//    int blue(int x, int y);
//    int alpha(int x, int y);

//    GrayImage toGrayImage();
//    RgbImage toRgbImage();

//    friend class RgbImage;
//};

}

#endif // CTKABSTRACTIMAGE_H
