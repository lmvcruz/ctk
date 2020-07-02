#ifndef CTKPOLYGON_H
#define CTKPOLYGON_H

#include <vector>

#include "opencv2/highgui.hpp"

#include "ctkpoint.h"

namespace ctk {

class Polygon
{
public:
    //!Creates a Polygon
    Polygon();
    Polygon(const Polygon &that);
    Polygon(std::vector<PointD> &d);
    Polygon(std::vector<cv::Point> &cvd);
    ~Polygon();

    Polygon &operator=(const Polygon &that);
    Polygon &operator=(std::vector<PointD> &d);
    Polygon &operator=(std::vector<cv::Point> &cvd);

    PointD& operator[](int i);

    void add_point(PointD &pt);
    void add_point(double x, double y);
    void set_point(int idx, PointD &pt);
    void set_point(int idx, double x, double y);
    PointD &point(int i);

    std::vector<PointD> &get_data();
    std::vector<cv::Point> &get_cvdata();

    void Resize(int s);
    int size();

    double Area();
    double Perimeter();

    Polygon Reduce(int epsilon=3);
    void SelfReduce(int epsilon=3);

    Polygon Shift(int sh);
    void SelfShift(int sh);

protected:
    std::vector<PointD> data_; /*!< Vector of 2D Point objects as defined in ctkpoint.h */
    std::vector<cv::Point> cvdata_;  /*!< Vector of 2D Point objects from the openCV template class Point */
};

}

#endif // CTKPOLYGON_H
