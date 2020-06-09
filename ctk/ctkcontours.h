#ifndef CTKCONTOURS_H
#define CTKCONTOURS_H

#include <vector>

#include "ctkpolygon.h"
#include "ctkimage.h"

namespace ctk {

class Contours
{
public:
    Contours();

    int resize(int s);
    int size();

    void add_polygon(Polygon &pol);
    void set_polygon(int idx, Polygon &pol);
    Polygon &polygon(int idx);

    Contours OrientedBoundingBoxes();

    void CalculateContours(BinaryMatrix &img);
    void CalculateApproximateContours(BinaryMatrix &img, int eps=3);

    RgbImage Draw(RgbImage &img);

protected:
    std::vector<Polygon> polys_;
    std::vector<cv::Vec4i> hierarchy_;
};

}
#endif // CTKCONTOURS_H
