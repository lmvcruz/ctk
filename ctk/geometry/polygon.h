#pragma once

#include <vector>

#include "opencv2/highgui.hpp"

#include "ctk/geometry/point.h"

namespace ctk {

class Polygon {
public:
    Polygon() = default;
    Polygon(const Polygon &that);
    Polygon(const std::vector<PointD> &d);
    Polygon(const std::vector<cv::Point> &cvd);
    ~Polygon();

    Polygon &operator=(const Polygon &that);
    Polygon &operator=(const std::vector<PointD> &d);
    Polygon &operator=(const std::vector<cv::Point> &cvd);

    PointD& operator[](int i);

    void AddPoint(PointD &pt);
    void AddPoint(double x, double y);
    void SetPoint(int idx, PointD &pt);
    void SetPoint(int idx, double x, double y);
    PointD &GetPoint(int i);

    std::vector<PointD> &GetData();
    const std::vector<PointD> &GetData() const;
    std::vector<cv::Point> &GetCvData();
    const std::vector<cv::Point> &GetCvData() const;

    void Resize(int s);
    int size();

    double Area();
    double Perimeter();

    Polygon Reduce(int epsilon=3);
    void SelfReduce(int epsilon=3);

    Polygon Shift(int sh);
    void SelfShift(int sh);

protected:
    std::vector<PointD> points; /*!< Vector of 2D Point objects as defined in ctkpoint.h */
    std::vector<cv::Point> cvpoints;  /*!< Vector of 2D Point objects from the openCV template class Point */
};

}
