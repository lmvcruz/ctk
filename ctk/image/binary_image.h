#pragma once

#include <opencv2/highgui.hpp>

#include "ctk/image/abstract_image.h"

namespace ctk {

class BinaryImage : public AbstractImage<bool> {
public:
    BinaryImage();
    BinaryImage(const BinaryImage& that);
    BinaryImage(const AbstractImage<bool>& that);
    BinaryImage(const cv::Mat& d);
    BinaryImage(int w, int h, bool v=false);
    BinaryImage(int w, int h, const std::vector<bool>& d);

    BinaryImage &operator=(const BinaryImage& that);

    void CreateAndFill(int w, int h, bool v);

    void Fill(bool v);
    void Set(int x, int y, bool v) override;
    bool Get(int x, int y) const override;

    //TODO: implement SafeGet and SafeSet

    BinaryImage Not() const;
    BinaryImage And(const BinaryImage& that) const;
    BinaryImage Or(const BinaryImage& that) const;
    BinaryImage Xor(const BinaryImage& that) const;

    //TODO: Implement Self methods of Logic Operations

    int CountTrues() const;
    int CountFalses() const;

    //TODO: test and benchmark these methods;
    //TODO: replace type by an internal enum
    BinaryImage Erode(int size, int etype=cv::MORPH_RECT) const;
    void SelfErode(int size, int etype=cv::MORPH_RECT);
    BinaryImage Dilate(int size, int etype=cv::MORPH_RECT) const;
    void SelfDilate(int size, int etype=cv::MORPH_RECT);

    BinaryImage Warp(const std::vector<PointD> &pts, 
                const std::vector<PointD> &refs, int w, int h) const;

    int Compare(int x, int y, const ctk::BinaryImage &that) const;
    ctk::PointI FindBestMatch(const ctk::BinaryImage &that) const;
    ctk::PointI FindBestMatch(int xi, int xf, int yi, int yf, 
                              const ctk::BinaryImage &that) const;

    void Open(std::string filename);
    void Save(std::string filename) const override;

    RgbImage ToRgbImage() const;
};

} // namespace ctk 
