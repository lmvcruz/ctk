#include "ctk/img_proc/contours.h"

#include <random>

namespace ctk {

Contours::Contours() {

}

/**
 * @brief Contours::resize resize Polygon vector
 * @param s new size
 */
void Contours::resize(int s) {
    polys_.resize(s);
}

/**
 * @brief Contours::size get size of Polygon vector
 * @return int representing the size of Polygon vector
 */
int Contours::size() {
    return polys_.size();
}

/**
 * @brief Contours::add_polygon Add Polygon to Polygon vector
 * @param pol Polygon to be added
 */
void Contours::add_polygon(Polygon &pol) {
    polys_.push_back(pol);
}

/**
 * @brief Contours::set_polygon Set Polygon in Polygon vector
 * @param idx int representing the index of the element to be set
 * @param pol desired Polygon
 */
void Contours::set_polygon(int idx, Polygon &pol) {
    polys_[idx] = pol;
}

/**
 * @brief Contours::polygon Get Polygon in Polygon vector
 * @param idx int representing the index of the element to be get
 * @return Polygon at index idx
 */
Polygon &Contours::polygon(int idx) {
    return polys_[idx];
}

/**
 * @brief Contours::OrientedBoundingBoxes Get oriented bounding boxes for each Polygon
 * @return Contours object with oriented bounding boxes of the passed Polygons
 */
Contours Contours::OrientedBoundingBoxes() {
    Contours boxes;
    boxes.resize(polys_.size());
    for (auto i = 0; i < polys_.size(); i++) {
        cv::RotatedRect cv_box;
        cv_box = cv::minAreaRect(cv::Mat(polys_[i].get_cvdata()));
        cv::Point2f vertices[4];
        cv_box.points(vertices);
        Polygon &pol = boxes.polygon(i);
        pol.Resize(4);
        for (int j = 0; j < 4; j++) {
            pol.set_point(j, vertices[j].x, vertices[j].y);
        }
    }
    return boxes;
}

/**
 * @brief Contours::CalculateContours Get contours from BinaryImage
 * @param img input BinaryImage
 */
void Contours::CalculateContours(BinaryImage &img) {
    std::vector<std::vector<cv::Point> > cv_contours;
    cv::findContours(img.GetData(), cv_contours, hierarchy_,
                     cv::RETR_TREE, cv::CHAIN_APPROX_TC89_KCOS);
    polys_.resize(cv_contours.size());
    for (auto i = 0; i < cv_contours.size(); i++) {
        polys_[i] = cv_contours[i];
    }
}

/**
 * @brief Contours::CalculateApproximateContours Get approximate contours from BinaryImage
 * @param img input BinaryImage
 * @param eps int specifying the approximation accuracy. The maximum distance between the original contour and its approximation.
 */
void Contours::CalculateApproximateContours(BinaryImage &img, int eps) {
    std::vector<std::vector<cv::Point> > cv_contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(img.GetData(), cv_contours, hierarchy,
                     cv::RETR_TREE, cv::CHAIN_APPROX_TC89_KCOS);
    polys_.resize(cv_contours.size());
    for (auto i = 0; i < cv_contours.size(); i++) {
        std::vector<cv::Point> approx;
        approxPolyDP(cv::Mat(cv_contours[i]), approx, eps, true);
        polys_[i] = approx;
    }
}

/**
 * @brief Contours::Draw Draw contours in BinaryImage
 * @param bin input BinaryImage
 * @return RgbImage with drawn contours
 */
RgbImage Contours::Draw(BinaryImage &bin) {
    RgbImage rgb = bin.ToRgbImage();
    return Draw(rgb);
}

/**
 * @brief Contours::Draw Draw contours in RgbImage
 * @param img input RgbImage
 * @return RgbImage with drawn contours
 */
RgbImage Contours::Draw(RgbImage &img) {
    RgbImage new_img = img;
    cv::Mat &new_mat = new_img.GetData();
    std::vector<std::vector<cv::Point>> cv_conts;
    cv_conts.resize(polys_.size());
    for (auto i = 0; i < polys_.size(); i++) {
        cv_conts[i] = polys_[i].get_cvdata();
    }
    srand(12345);
    for (int i = 0; i < polys_.size(); i++) {
        const int  kThickness  = 2;
        const int  kLineType   = 8;
        cv::Scalar color = cv::Scalar(rand()%255, rand()%255, rand()%255);
        cv::drawContours(new_mat, cv_conts, i, color, kThickness, kLineType);
    }
    return new_img;
}

} // namespace ctk 
