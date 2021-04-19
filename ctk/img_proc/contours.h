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
    int GetSize() const;

    void AddPolygon(const Polygon &pol);
    void SetPolygon(int idx, const Polygon &pol);
    Polygon &GetPolygon(int idx);

    Contours OrientedBoundingBoxes() const;

    void CalculateContours(const BinaryImage &img);
    void CalculateApproximateContours(const BinaryImage &img, int eps=3);

    RgbImage Draw(const BinaryImage &img) const;
    RgbImage Draw(const RgbImage &img) const;

protected:
    std::vector<Polygon> polys;
    std::vector<cv::Vec4i> hierarchy;
};

} // namespace ctk 
