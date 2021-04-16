#pragma once

#include <opencv2/highgui.hpp>

#include "ctk/image/abstract_image.h"

namespace ctk {

class BinaryImage : public AbstractImage<bool> {
public:
    BinaryImage();
    BinaryImage(const BinaryImage& that);
    BinaryImage(const AbstractImage<bool>& that);
    BinaryImage(cv::Mat& d);
    BinaryImage(int w, int h, bool v=false);
    BinaryImage(int w, int h, std::vector<bool>& d);

    BinaryImage &operator=(const BinaryImage& that);

    void CreateAndFill(int w, int h, bool v);

    void Fill(bool v);
    void Set(int x, int y, bool v);
    bool Get(int x, int y);

    //TODO: implement SafeGet and SafeSet

    BinaryImage Not();
    BinaryImage And(BinaryImage& that);
    BinaryImage Or(BinaryImage& that);
    BinaryImage Xor(BinaryImage& that);

    //TODO: Implement Self methods of Logic Operations

    int CountTrues();
    int CountFalses();

    //TODO: test and benchmark these methods;
    //TODO: replace type by an internal enum
    BinaryImage Erode(int size, int etype=cv::MORPH_RECT);
    void SelfErode(int size, int etype=cv::MORPH_RECT);
    BinaryImage Dilate(int size, int etype=cv::MORPH_RECT);
    void SelfDilate(int size, int etype=cv::MORPH_RECT);

    BinaryImage Warp(std::vector<PointD> &pts, std::vector<PointD> &refs, int w, int h);

    int Compare(int x, int y, ctk::BinaryImage &that);
    ctk::PointI FindBestMatch(ctk::BinaryImage &that);
    ctk::PointI FindBestMatch(int xi, int xf, int yi, int yf, ctk::BinaryImage &that);

    void Open(std::string filename);
    void Save(std::string filename);

    RgbImage ToRgbImage();
};

} // namespace ctk 
