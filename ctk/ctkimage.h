#ifndef CTKABSTRACTIMAGE_H
#define CTKABSTRACTIMAGE_H

#include <iostream>

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "ctkabstractmatrix.h"
#include "ctkbinarymatrix.h"
#include "ctkpoint.h"
#include "ctkpolygon.h"

namespace ctk {

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
    std::vector<int> indices;
    int currIterIdx;

    bool invertchannels;

public:
    using AbstractMatrix<T>::get;
    using AbstractMatrix<T>::set;

    /**
     * @brief AbstractImage
     */
    AbstractImage() {
        AbstractMatrix<T>::type = -1;
        AbstractMatrix<T>::ch_size = -1;
        //
        invertchannels = false;
    }

    /**
     * @brief AbstractImage TODO
     * @param d TODO
     */
    AbstractImage(cv::Mat &d) : AbstractMatrix<T>(d){
        AbstractMatrix<T>::type = d.type();
        AbstractMatrix<T>::ch_size = d.channels();
        //
        invertchannels = false;
    }

    /**
     * @brief ~AbstractImage TODO
     */
    virtual ~AbstractImage(){}

    /**
     * @brief startScanIndices TODO
     */
    void startScanIndices() {
        int w = AbstractMatrix<T>::width();
        int h = AbstractMatrix<T>::height();
        indices.resize(AbstractMatrix<T>::size());
        for (unsigned int y=0; y<h; y++) {
            for (unsigned int x=0; x<w; x++) {
                indices[y*w+x] = y*w+x;
            }
        }
    }

    /**
     * @brief startSnakeIndices TODO
     */
    void startSnakeIndices() {
        int w = AbstractMatrix<T>::width();
        int h = AbstractMatrix<T>::height();
        indices.resize(AbstractMatrix<T>::size());
        for (int y=0; y<h; y++) {
            for (int x=0; x<w; x++) {
                indices[y*w+x] = y*w+x;
            }
        }
        for (int y=0; y<h; y++) {
            for (int x=0; x<w; x++) {
                indices[y*w+x] = y*w+x;
            }
            y++;
            if (y<h) {
                for (int x=0; x<w; x++) {
                    indices[y*w+x] = y*w + w-1-x;
                }
            }
        }
    }

    /**
     * @brief startSpiralIndices TODO
     */
    void startSpiralIndices() {
        int w = AbstractMatrix<T>::width();
        int h = AbstractMatrix<T>::height();
        indices.resize(AbstractMatrix<T>::size());
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
            indices[ptIndex] = y*w+x;
            ptIndex++;
        }
    }

    /**
     * @brief startSnailIndices TODO
     */
    void startSnailIndices() {
        int w = AbstractMatrix<T>::width();
        int h = AbstractMatrix<T>::height();
        int s = w*h;
        indices.resize(s);
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
            indices[i] = y*w+x;
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
    void startCustomIndices(std::vector<int> &vec) {
        indices = vec;
    }

    /**
     * @brief isIndices TODO
     * @return  TODO
     */
    bool isIndices() {
        return (indices.size()>0);
    }

    /**
     * @brief get TODO
     * @param i TODO
     * @return  TODO
     */
    virtual T get(int i) {
        int y = indices[i]/AbstractMatrix<T>::data.cols;
        int x = indices[i]%AbstractMatrix<T>::data.rows;
        return AbstractMatrix<T>::get(x,y);
    }

    /**
     * @brief safe_get TODO
     * @param i TODO
     * @return TODO
     */
    virtual T safe_get(int i) {
        if (!isIndices()) startScanIndices();
        if (i<0 || i>=indices.size()) {
            throw std::out_of_range("Exception thrown in AbstractImage::safe_set");
        }
        int y = indices[i]/AbstractMatrix<T>::data.cols;
        int x = indices[i]%AbstractMatrix<T>::data.rows;
        return AbstractMatrix<T>::get(x,y);
    }

    /**
     * @brief set TODO
     * @param i TODO
     * @param v TODO
     */
    virtual void set(int i, T v) {
        int y = indices[i]/AbstractMatrix<T>::data.cols;
        int x = indices[i]%AbstractMatrix<T>::data.rows;
        AbstractMatrix<T>::set(x,y,v);
    }

    /**
     * @brief safe_set TODO
     * @param i TODO
     * @param v TODO
     */
    virtual void safe_set(int i, T v) {
        if (!isIndices()) startScanIndices();
        if (i<0 || i>=indices.size()) {
            throw std::out_of_range("Exception thrown in AbstractImage::safe_set");
        }
        int y = indices[i]/AbstractMatrix<T>::data.cols;
        int x = indices[i]%AbstractMatrix<T>::data.rows;
        AbstractMatrix<T>::set(x,y,v);
    }

    /**
     * @brief Crop TODO
     * @param x TODO
     * @param y TODO
     * @param w TODO
     * @param h TODO
     * @return  TODO
     */
    AbstractImage<T> Crop(int x, int y, int w, int h) {
        cv::Rect roi(x,y,w,h);
        cv::Mat aux = AbstractMatrix<T>::data(roi);
        return AbstractImage<T>(aux);
    }

    /**
     * @brief SelfCrop TODO
     * @param x TODO
     * @param y TODO
     * @param w TODO
     * @param h TODO
     */
    void SelfCrop(int x, int y, int w, int h) {
        cv::Rect roi(x,y,w,h);
        AbstractMatrix<T>::data = AbstractMatrix<T>::data(roi).clone();
    }

    /**
     * @brief FlipHorizontally TODO
     * @return  TODO
     */
    AbstractImage<T> FlipHorizontally() {
        cv::Mat aux;
        cv::flip(AbstractMatrix<T>::data, aux, +1);
        return AbstractImage<T>(aux);
    }

    /**
     * @brief SelfFlipHorizontally TODO
     */
    void SelfFlipHorizontally()
    {
        cv::flip(AbstractMatrix<T>::data, AbstractMatrix<T>::data, +1);
    }

    /**
     * @brief FlipVertically TODO
     * @return  TODO
     */
    AbstractImage<T> FlipVertically() {
        cv::Mat aux;
        cv::flip(AbstractMatrix<T>::data, aux, 0);
        return AbstractImage<T>(aux);
    }

    /**
     * @brief SelfFlipVertically TODO
     */
    void SelfFlipVertically()
    {
        cv::flip(AbstractMatrix<T>::data, AbstractMatrix<T>::data, 0);
    }

    /**
     * @brief FlipBoth TODO
     * @return  TODO
     */
    AbstractImage<T> FlipBoth() {
        cv::Mat aux;
        cv::flip(AbstractMatrix<T>::data, aux, -1);
        return AbstractImage<T>(aux);
    }

    /**
     * @brief SelfFlipBoth TODO
     */
    void SelfFlipBoth()
    {
        cv::flip(AbstractMatrix<T>::data, AbstractMatrix<T>::data, -1);
    }

    /**
     * @brief Rotate90 TODO
     * @return  TODO
     */
    AbstractImage<T> Rotate90() {
        cv::Mat aux;
        cv::transpose(AbstractMatrix<T>::data, aux);
        cv::flip(aux, aux, +1);
        return AbstractImage<T>(aux);
    }

    /**
     * @brief SelfRotate90 TODO
     */
    void SelfRotate90()
    {
        cv::transpose(AbstractMatrix<T>::data, AbstractMatrix<T>::data);
        cv::flip(AbstractMatrix<T>::data, AbstractMatrix<T>::data, +1);
    }

    /**
     * @brief Rotate180 TODO
     * @return  TODO
     */
    AbstractImage<T> Rotate180() {
        cv::Mat aux;
        cv::flip(AbstractMatrix<T>::data, aux, -1);
        return AbstractImage<T>(aux);
    }

    /**
     * @brief SelfRotate180 TODO
     */
    void SelfRotate180()
    {
        cv::flip(AbstractMatrix<T>::data, AbstractMatrix<T>::data, -1);
    }

    /**
     * @brief Rotate270 TODO
     * @return  TODO
     */
    AbstractImage<T> Rotate270() {
        cv::Mat aux;
        cv::transpose(AbstractMatrix<T>::data, aux);
        cv::flip(aux, aux, 0);
        return AbstractImage<T>(aux);
    }

    /**
     * @brief SelfRotate270 TODO
     */
    void SelfRotate270()
    {
        cv::transpose(AbstractMatrix<T>::data, AbstractMatrix<T>::data);
        cv::flip(AbstractMatrix<T>::data, AbstractMatrix<T>::data, 0);
    }

    AbstractImage<T> resize(int nw, int nh) {
        cv::Mat aux;
        cv::resize(AbstractMatrix<T>::data, aux, cv::Size(nw,nh), cv::INTER_CUBIC);
        return AbstractImage<T>(aux);
    }

    /**
     * @brief Open TODO
     * @param filename TODO
     */
    void Open(std::string filename) {
        AbstractMatrix<T>::data = cv::imread(filename, cv::IMREAD_UNCHANGED);
        if (invertchannels) {
            cv::cvtColor(AbstractMatrix<T>::data,
                         AbstractMatrix<T>::data,
                         cv::COLOR_RGB2BGR);
        }
    }

    /**
     * @brief Save TODO
     * @param filename TODO
     */
    void Save(std::string filename) {
        cv::imwrite(filename, AbstractMatrix<T>::data);
        if(invertchannels) {
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
        std::cout << "TODO" << std::endl;
    }
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

    BinaryMatrix ApplyBinaryThreshold(int t=127);
    BinaryMatrix ApplyOtsuThreshold();
    BinaryMatrix ApplyAdaptativeThreshold(int bs=5, int c=1);

    GrayImage Truncate(int t=128);

    GrayImage Normalize(int minv, int maxv);
    BinaryMatrix PickColor(int c);

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
    void safe_set(int i, int r, int g, int b);
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


    BinaryMatrix PickColor(int r, int g, int b);
    GrayImage Project(std::vector<PointI> &centers);

    // TODO: create a classe for contours (avoiding copy to PointI)
//    std::vector<std::vector<PointI> > Contours();
//    std::vector<std::vector<PointI> > ApproximateContours(int eps=3);
    std::vector<Polygon> Contours();
    std::vector<Polygon> ApproximateContours(int eps=3);
    RgbImage Warp(std::vector<PointD> &pts, std::vector<PointD> &refs, int w, int h);

    GrayImage toGrayImage();
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
