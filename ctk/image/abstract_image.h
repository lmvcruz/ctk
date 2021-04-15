#pragma once

#include <iostream>
#include <vector>

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "ctk/geometry/point.h"
#include "ctk/geometry/polygon.h"
#include "ctk/matrix/abstract_matrix.h"
#include "ctk/misc/spatial_ordering.h"

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
class AbstractImage : public AbstractMatrix<T> {
protected:
    std::vector<unsigned int> indices;
    int curr_iter_idx;
    bool invert_channels = false;

public:
    using AbstractMatrix<T>::Get;
    using AbstractMatrix<T>::Set;
    using AbstractMatrix<T>::GetWidth;
    using AbstractMatrix<T>::GetHeight;

    /**
     * @brief AbstractImage Default Constructor
     */
    AbstractImage() = default;

    /**
     * @brief AbstractImage Parameterized Constructor
     * @param d matrix
     */
    AbstractImage(cv::Mat &d) : AbstractMatrix<T>(d) {
        AbstractMatrix<T>::type = d.type();
        AbstractMatrix<T>::ch_size = d.channels();
    }

    /**
     * @brief ~AbstractImage Destructor
     */
    virtual ~AbstractImage() = default;

    /**
     * @brief startScanIndices Generate scan indices
     */
    void StartScanIndices() {
        unsigned int w = static_cast<unsigned int>(
                                    AbstractMatrix<T>::GetWidth());
        unsigned int h = static_cast<unsigned int>(
                                    AbstractMatrix<T>::GetHeight());
        auto points = getScanOrderVector(w, h);
        InitIndicesFromPointVector(points);
    }

    /**
     * @brief startSnakeIndices Generate snake indices
     */
    void StartSnakeIndices() {
        unsigned int w = static_cast<unsigned int>(
                                    AbstractMatrix<T>::GetWidth());
        unsigned int h = static_cast<unsigned int>(
                                    AbstractMatrix<T>::GetHeight());
        auto points = getSnakeOrderVector(w, h);
        InitIndicesFromPointVector(points);
    }

    /**
     * @brief startSpiralIndices Generate spiral indices
     */
    void StartSpiralIndices() {
        unsigned int w = static_cast<unsigned int>(
                                    AbstractMatrix<T>::GetWidth());
        unsigned int h = static_cast<unsigned int>(
                                    AbstractMatrix<T>::GetHeight());
        auto points = getSpiralOrderVector(w, h);
        InitIndicesFromPointVector(points);
    }

    /**
     * @brief startSnailIndices Generate snail indices
     */
    void StartSnailIndices() {
        unsigned int w = static_cast<unsigned int>(
                                    AbstractMatrix<T>::GetWidth());
        unsigned int h = static_cast<unsigned int>(
                                    AbstractMatrix<T>::GetHeight());
        auto points = getSnailOrderVector(w, h);
        InitIndicesFromPointVector(points);
    }

    /**
     * @brief startCustomIndices Generate Custom indices
     * @param vec vector of unsigned int with the desired indices
     */
    void StartCustomIndices(std::vector<unsigned int> &vec) {
        indices = vec;
    }

    /**
     * @brief StartCustomIndices  Generate Custom indices
     * @param vec  vector of int with the desired indices
     */
    void StartCustomIndices(std::vector<int> &vec) {
        indices.resize(vec.size());
        for (auto i = 0; i < vec.size(); ++i) {
            indices[i] = static_cast<unsigned int>(vec[i]);
        }
    }

    /**
     * @brief IsIndices checks the object will iterate over 
     * pre-defined indices
     * @return  true if the attribute indices is filled
     */
    bool IsIndices() {
        return (indices.size() > 0);
    }

    /**
     * @brief Get  Get specific element in AbstractMatrix
     * @param i int representing the desired index in vector indices
     * @return AbstractMatrix element at  position = indices(i)
     */
    T IGet(int i) {
        unsigned int ui = static_cast<unsigned int>(i);
        int int_indx = static_cast<int>(indices[ui]);
        int y = int_indx/AbstractMatrix<T>::data.cols;
        int x = int_indx%AbstractMatrix<T>::data.rows;
        return AbstractMatrix<T>::Get(x, y);
    }

    /**
     * @brief SafeGet Get specific element in AbstractMatrix
     * @param i int representing the desired index in vector indices
     * @return AbstractMatrix element at  position = indices(i)
     */
    T SafeIGet(int i) {
        if (!IsIndices()) StartScanIndices();
        int isize = static_cast<int>(indices.size());
        if (i < 0 || i >= isize) {
            throw std::out_of_range("Exception thrown in AbstractImage::SafeSet");
        }
        unsigned int ui = static_cast<unsigned int>(i);
        int iidx = static_cast<int>(indices[ui]);
        int x = iidx % AbstractMatrix<T>::data.rows;
        int y = iidx / AbstractMatrix<T>::data.cols;
        return AbstractMatrix<T>::Get(x, y);
    }

    /**
     * @brief Set  Set specific element in AbstractMatrix
     * @param i int representing the desired index in vector indices
     * @param v desired value
     */
    void ISet(int i, T v) {
        unsigned int ui = static_cast<unsigned int>(i);
        int iidx = static_cast<int>(indices[ui]);
        int y = iidx / AbstractMatrix<T>::data.cols;
        int x = iidx % AbstractMatrix<T>::data.rows;
        AbstractMatrix<T>::Set(x, y, v);
    }

    /**
     * @brief safe_iset  Set specific element in AbstractMatrix
     * @param i int representing the desired index in vector indices
     * @param v desired value
     */
    void SafeISet(int i, T v) {
        if (!IsIndices()) StartScanIndices();
        int isize = static_cast<int>(indices.size());
        if (i < 0 || i >= isize) {
            throw std::out_of_range("Exception thrown in AbstractImage::SafeSet");
        }
        unsigned int ui = static_cast<unsigned int>(i);
        int iidx = static_cast<int>(indices[ui]);
        int y = iidx / AbstractMatrix<T>::data.cols;
        int x = iidx % AbstractMatrix<T>::data.rows;
        AbstractMatrix<T>::Set(x, y, v);
    }

    /**
     * @brief Crop the image according to the region of interest
     * @param x int representing the x coordinate of the top-left corner
     * @param y int representing the y coordinate of the top-left corner
     * @param w width of the rectangle
     * @param h height of the rectangle
     * @return  Cropped image containing the desired rgion
     */
    AbstractImage<T> Crop(int x, int y, int w, int h) {
        cv::Rect roi(x, y, w, h);
        cv::Mat aux = AbstractMatrix<T>::data(roi);
        return AbstractImage<T>(aux);
    }

    /**
     * @brief SelfCrop the image according to the region of interest
     * @param x int representing the x coordinate of the top-left corner
     * @param y int representing the y coordinate of the top-left corner
     * @param w width of the rectangle
     * @param h height of the rectangle
     */
    void SelfCrop(int x, int y, int w, int h) {
        cv::Rect roi(x, y, w, h);
        AbstractMatrix<T>::data = AbstractMatrix<T>::data(roi).clone();
    }

    /**
     * @brief CopyFrom Copy a block of a provided image into self data
     * @param ox int the start x coordinate in this image where data will be placed
     * @param oy int the start y coordinate in this image where data will be placed
     * @param tx int the start x coordinate in that image where data will be gotten
     * @param ty int the start y coordinate in that image where data will be gotten
     * @param w width of the copied data (if -1 will be the entire image)
     * @param h height of the copied data (if -1 will be the entire image)
     */
    void CopyFrom(AbstractImage<T>& that, int ox, int oy, int tx, int ty, int w=-1, int h=-1) {
        if (w == -1 or h == -1) {
            w = that.GetWidth();
            h = that.GetHeight();
        }
        w = std::min(w, GetWidth() - ox);
        w = std::min(w, that.GetWidth() - tx);
        h = std::min(h, GetHeight() - oy);
        h = std::min(h, that.GetHeight() - ty);
        // TODO: replace this loop by memcpy
        for (int x = 0; x < w; ++x) {
            for (int y = 0; y < h; ++y) {
                Set(ox + x, oy + y, that.Get(tx + x, ty + y));
            }
        }
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
    void SelfFlipHorizontally() {
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
    void SelfFlipVertically() {
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
    void SelfFlipBoth() {
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
    void SelfRotate90() {
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
    void SelfRotate180() {
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
    void SelfRotate270() {
        cv::transpose(AbstractMatrix<T>::data, AbstractMatrix<T>::data);
        cv::flip(AbstractMatrix<T>::data, AbstractMatrix<T>::data, 0);
    }

    /**
     * @brief Resize - change image size
     * @param nw int representing new width
     * @param nh int representing new hight
     * @return Resized image
     */
    AbstractImage<T> Resize(int nw, int nh) {
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
        if (invert_channels) {
            cv::cvtColor(AbstractMatrix<T>::data,
                         AbstractMatrix<T>::data,
                         cv::COLOR_RGB2BGR);
        }
    }

    /**
     * @brief Save Save information to file
     * @param filename string with filename
     */
    void Save(std::string filename) {
        cv::imwrite(filename, AbstractMatrix<T>::data);
        if(invert_channels) {
            cv::Mat aux;
            cv::cvtColor(AbstractMatrix<T>::data,
                         aux, cv::COLOR_RGB2BGR);
            cv::imwrite(filename, aux);
        }
    }

private:
    void InitIndicesFromPointVector(std::vector<PointI>& points) {
        int w = AbstractMatrix<T>::GetWidth();
        int h = AbstractMatrix<T>::GetHeight();
        indices.resize(static_cast<unsigned int>(AbstractMatrix<T>::GetSize()));
        for (size_t ii = 0; ii < points.size(); ++ii) {
            int idx = points[ii].getY()*w+points[ii].getX();
            indices[ii] = static_cast<unsigned int>(idx);
        }
    }
};


class ColorImage : public AbstractImage<cv::Vec3b> {
public:
    ColorImage();
    ColorImage(const ColorImage& that);
    ColorImage(const AbstractImage<cv::Vec3b>& that);
    ColorImage(cv::Mat& d);

    virtual ~ColorImage(){}

    int GetChannels();
};

//TODO: NEXT SPRINT
//class HsvImage : public ColorImage
//{
//public:
//    HsvImage() = default;

//    void create(int w, int h);

//    using AbstractMatrix<cv::Vec3b>::set;
//    void Set(int x, int y, int h, int s, int v);
//    void Set(int i, int h, int s, int v);
//    int hue(int x, int y);
//    int saturation(int x, int y);
//    int value(int x, int y);

//    RgbImage ToRgbImage();

//    friend class RgbImage;
//};

//TODO: NEXT SPRINT
//class HlsImage : public ColorImage
//{
//public:
//    HlsImage() = default;

//    void create(int w, int h);

//    using AbstractMatrix<cv::Vec3b>::set;
//    void Set(int x, int y, int h, int l, int s);
//    void Set(int i, int h, int l, int s);
//    int hue(int x, int y);
//    int luminance(int x, int y);
//    int saturation(int x, int y);

//    RgbImage ToRgbImage();

//    friend class RgbImage;
//};

//TODO: NEXT SPRINT
//class LabImage : public ColorImage
//{
//public:
//    LabImage() = default;

//    void create(int w, int h);

//    using AbstractMatrix<cv::Vec3b>::set;
//    void Set(int x, int y, int l, int a, int b);
//    void Set(int i, int l, int a, int b);
//    int lightness(int x, int y);
//    int a_value(int x, int y);
//    int b_value(int x, int y);

//    RgbImage ToRgbImage();

//    friend class RgbImage;
//};

//TODO: NEXT SPRINT (Use only one RgbaImage class
//class ColorAlphaImage : public AbstractImage<cv::Vec4b>
//{
//public:
//    ColorAlphaImage();
//    virtual ~ColorAlphaImage(){}

//    int GetChannels();

//    void fill();
//};

//TODO: NEXT SPRINT
//class RgbaImage : public ColorAlphaImage
//{
//public:
//    RgbaImage() = default;

//    using AbstractMatrix<cv::Vec4b>::set;
//    void Set(int x, int y, int r, int g, int b, int a);
//    void Set(int i, int r, int g, int b, int a);
//    int red(int x, int y);
//    int Green(int x, int y);
//    int Blue(int x, int y);
//    int alpha(int x, int y);

//    GrayImage ToGrayImage();
//    RgbImage ToRgbImage();

//    friend class RgbImage;
//};

} // namespace ctk
