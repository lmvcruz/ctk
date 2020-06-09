#include "ctkcontours.h"

#include <random>

#include "ctkpolygon.h"

namespace ctk {

Contours::Contours()
{

}

int Contours::resize(int s)
{
    polys_.resize(s);
}

int Contours::size()
{
    return polys_.size();
}

void Contours::add_polygon(Polygon &pol)
{
    polys_.push_back(pol);
}

void Contours::set_polygon(int idx, Polygon &pol)
{
    polys_[idx] = pol;
}

Polygon &Contours::polygon(int idx)
{
    return polys_[idx];
}

Contours Contours::OrientedBoundingBoxes()
{
    Contours boxes;
    boxes.resize(polys_.size());
    for (auto i=0; i<polys_.size(); i++) {
        cv::RotatedRect cv_box;
        cv_box = cv::minAreaRect(cv::Mat(polys_[i].get_cvdata()));
        cv::Point2f vertices[4];
        cv_box.points(vertices);
        Polygon &pol = boxes.polygon(i);
        pol.Resize(4);
        for (int j=0; j<4; j++)
            pol.set_point(j, vertices[j].x, vertices[j].y);

    }
    return boxes;
}

void Contours::CalculateContours(BinaryMatrix &img)
{
    std::vector<std::vector<cv::Point> > cv_contours;
    cv::findContours(img.get_data(), cv_contours, hierarchy_,
                     cv::RETR_TREE, cv::CHAIN_APPROX_TC89_KCOS);
    //
    polys_.resize(cv_contours.size());
    for (auto i=0; i<cv_contours.size(); i++) {
        polys_[i] = cv_contours[i];
    }
}

void Contours::CalculateApproximateContours(BinaryMatrix &img, int eps)
{
    std::vector<std::vector<cv::Point> > cv_contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(img.get_data(), cv_contours, hierarchy,
                     cv::RETR_TREE, cv::CHAIN_APPROX_TC89_KCOS);
    //
    polys_.resize(cv_contours.size());
    for (auto i=0; i<cv_contours.size(); i++) {
        std::vector<cv::Point> approx;
        approxPolyDP(cv::Mat(cv_contours[i]), approx, eps, true);
        polys_[i] = approx;
    }
}

RgbImage Contours::Draw(RgbImage &img)
{
    RgbImage new_img = img;
    cv::Mat &new_mat = new_img.get_data();
    //
    std::vector<std::vector<cv::Point>> cv_conts;
    cv_conts.resize(polys_.size());
    for (auto i=0; i<polys_.size(); i++) {
        cv_conts[i] = polys_[i].get_cvdata();
    }
    for (int i=0; i<polys_.size(); i++) {
        srand(12345);
        const int  kThickness  = 2;
        const int  kLineType   = 8;
        cv::Scalar color = cv::Scalar(rand()%255, rand()%255, rand()%255);
        cv::drawContours(new_mat,cv_conts, i, color, kThickness, kLineType);
    }
    return new_img;
}

}
