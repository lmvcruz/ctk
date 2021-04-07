#pragma once

#include <vector>

#include "ctk/geometry/polygon.h"
#include "ctk/image/image.h"

namespace ctk {

class Contours
{
public:
    Contours();

    void resize(int s);
    int size();

    void add_polygon(Polygon &pol);
    void set_polygon(int idx, Polygon &pol);
    Polygon &polygon(int idx);

    Contours OrientedBoundingBoxes();

    void CalculateContours(BinaryImage &img);
    void CalculateApproximateContours(BinaryImage &img, int eps=3);

    RgbImage Draw(BinaryImage &img);
    RgbImage Draw(RgbImage &img);

protected:
    std::vector<Polygon> polys_;
    std::vector<cv::Vec4i> hierarchy_;
};

}