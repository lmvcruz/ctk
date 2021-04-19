#include "ctk/img_proc/contours.h"

#include <random>

namespace ctk {

/**
 * @brief Contours::resize Resize Polygon vector
 * @param s new size
 */
void Contours::Resize(int s) {
    polys.resize(s);
}

/**
 * @brief Contours::size get size of Polygon vector
 * @return int representing the size of Polygon vector
 */
int Contours::GetSize() const {
    return polys.size();
}

/**
 * @brief Contours::AddPolygon Add Polygon to Polygon vector
 * @param pol Polygon to be added
 */
void Contours::AddPolygon(const Polygon &pol) {
    polys.push_back(pol);
}

/**
 * @brief Contours::SetPolygon Set Polygon in Polygon vector
 * @param idx int representing the index of the element to be set
 * @param pol desired Polygon
 */
void Contours::SetPolygon(int idx, const Polygon &pol) {
    polys[idx] = pol;
}

/**
 * @brief Contours::GetPolygon Get Polygon in Polygon vector
 * @param idx int representing the index of the element to be get
 * @return Polygon at index idx
 */
Polygon &Contours::GetPolygon(int idx) {
    return polys[idx];
}

/**
 * @brief Contours::OrientedBoundingBoxes Get oriented bounding boxes for each Polygon
 * @return Contours object with oriented bounding boxes of the passed Polygons
 */
Contours Contours::OrientedBoundingBoxes() const {
    Contours boxes;
    boxes.Resize(polys.size());
    for (auto i = 0; i < polys.size(); ++i) {
        cv::RotatedRect cv_box;
        cv_box = cv::minAreaRect(cv::Mat(polys[i].GetCvData()));
        cv::Point2f vertices[4];
        cv_box.points(vertices);
        Polygon &pol = boxes.GetPolygon(i);
        pol.Resize(4);
        for (int j = 0; j < 4; ++j) {
            pol.SetPoint(j, vertices[j].x, vertices[j].y);
        }
    }
    return boxes;
}

/**
 * @brief Contours::CalculateContours Get contours from BinaryImage
 * @param img input BinaryImage
 */
void Contours::CalculateContours(const BinaryImage &img) {
    std::vector<std::vector<cv::Point> > cv_contours;
    cv::findContours(img.GetData(), cv_contours, hierarchy,
                     cv::RETR_TREE, cv::CHAIN_APPROX_TC89_KCOS);
    polys.resize(cv_contours.size());
    for (auto i = 0; i < cv_contours.size(); i++) {
        polys[i] = cv_contours[i];
    }
}

/**
 * @brief Contours::CalculateApproximateContours Get approximate contours from BinaryImage
 * @param img input BinaryImage
 * @param eps int specifying the approximation accuracy. The maximum distance between the original contour and its approximation.
 */
void Contours::CalculateApproximateContours(const BinaryImage &img, int eps) {
    std::vector<std::vector<cv::Point> > cv_contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(img.GetData(), cv_contours, hierarchy,
                     cv::RETR_TREE, cv::CHAIN_APPROX_TC89_KCOS);
    polys.resize(cv_contours.size());
    for (auto i = 0; i < cv_contours.size(); i++) {
        std::vector<cv::Point> approx;
        approxPolyDP(cv::Mat(cv_contours[i]), approx, eps, true);
        polys[i] = approx;
    }
}

/**
 * @brief Contours::Draw Draw contours in BinaryImage
 * @param bin input BinaryImage
 * @return RgbImage with drawn contours
 */
RgbImage Contours::Draw(const BinaryImage &bin) const {
    RgbImage rgb = bin.ToRgbImage();
    return Draw(rgb);
}

/**
 * @brief Contours::Draw Draw contours in RgbImage
 * @param img input RgbImage
 * @return RgbImage with drawn contours
 */
RgbImage Contours::Draw(const RgbImage &img) const {
    RgbImage new_img = img;
    cv::Mat &new_mat = new_img.GetData();
    std::vector<std::vector<cv::Point>> cv_conts;
    cv_conts.resize(polys.size());
    for (auto i = 0; i < polys.size(); i++) {
        cv_conts[i] = polys[i].GetCvData();
    }
    srand(12345);
    for (int i = 0; i < polys.size(); i++) {
        const int  kThickness  = 2;
        const int  kLineType   = 8;
        cv::Scalar color = cv::Scalar(rand()%255, rand()%255, rand()%255);
        cv::drawContours(new_mat, cv_conts, i, color, kThickness, kLineType);
    }
    return new_img;
}

} // namespace ctk 
