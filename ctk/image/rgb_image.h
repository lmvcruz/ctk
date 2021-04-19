#pragma once

#include <opencv2/highgui.hpp>

#include "ctk/image/abstract_image.h"

namespace ctk {

class RgbImage : public ColorImage {
public:
    using AbstractMatrix<cv::Vec3b>::Get;
    using AbstractMatrix<cv::Vec3b>::Set;

    RgbImage();
    RgbImage(const RgbImage& that);
    RgbImage(const AbstractImage<cv::Vec3b>& that);
    RgbImage(const cv::Mat& d);

    void Create(int w, int h);
    void Fill(int r, int g, int b);
    void CreateAndFill(int w, int h, int r, int g, int b);

    void Set(int x, int y, int r, int g, int b);
    void Set(int i, int r, int g, int b);

    void SafeSet(int x, int y, int r, int g, int b);
    void SafeISet(int i, int r, int g, int b);
    int Red(int x, int y) const;
    int Green(int x, int y) const;
    int Blue(int x, int y) const;

    //TODO: test and benchmark these methods;
    PointI GetPixel(int x, int y) const;

    //TODO: test and benchmark these methods;
    //TODO: replace type by an internal enum
    RgbImage Quantize(int q, int iter=10, float eps=1.0, int attempts=3,
                      int qtype=cv::KMEANS_PP_CENTERS) const;
    RgbImage Quantize(const std::vector<PointI> &centers, int iter=10,
                      float eps=1.0, int attempts=3) const;


    //TODO: evaluate if this method can be in Image (generic for all types of images)
    BinaryImage PickColor(int r, int g, int b) const;
    //TODO: look for a better name for this function
    GrayImage Project(const std::vector<PointI> &centers) const;

    // TODO: create a classe for contours (avoiding copy to PointI)
    std::vector<Polygon> Contours() const;
    std::vector<Polygon> ApproximateContours(int eps=3);
    RgbImage Warp(const std::vector<PointD> &pts, 
                  const std::vector<PointD> &refs, int w, int h) const;

    GrayImage ToGrayImage() const;

    RgbImage DrawPolygon(Polygon &pol) const;

    //RgbImage PutText(std::string content, ctk::PointI position)

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

} // namespace ctk 
