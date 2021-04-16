#pragma once

#include <vector>

#include "ctk/geometry/polygon.h"
#include "ctk/image/binary_image.h"
#include "ctk/image/rgb_image.h"

namespace ctk {

class Contours {
public:
    Contours() = default;
    ~Contours() = default;

    void Resize(int s);
    int GetSize();

    void AddPolygon(Polygon &pol);
    void SetPolygon(int idx, Polygon &pol);
    Polygon &GetPolygon(int idx);

    Contours OrientedBoundingBoxes();

    void CalculateContours(BinaryImage &img);
    void CalculateApproximateContours(BinaryImage &img, int eps=3);

    RgbImage Draw(BinaryImage &img);
    RgbImage Draw(RgbImage &img);

protected:
    std::vector<Polygon> polys;
    std::vector<cv::Vec4i> hierarchy;
};

} // namespace ctk 
