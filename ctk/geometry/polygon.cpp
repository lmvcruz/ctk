#include "ctk/geometry/polygon.h"

#include "opencv2/imgproc.hpp"

namespace ctk {

/**
 * @brief Polygon::Polygon  Copy constructor. Takes a reference to an existing polygon object as input
 * and uses it to intialize another polygon object
 * @param that  reference to an existing polygon object
 */
Polygon::Polygon(const Polygon &that) {
    points = that.points;
    cvpoints = that.cvpoints;
}

/**
 * @brief Polygon::Polygon  Parameterized constructor.
 * @param pts  vector of Point objects
 */
Polygon::Polygon(const std::vector<PointD> &pts) {
    points = pts;
    cvpoints.resize(pts.size());
    for (auto i = 0; i < pts.size(); i++) {
        cvpoints[i].x = pts[i].GetX();
        cvpoints[i].y = pts[i].GetY();
    }
}

/**
 * @brief Polygon::Polygon  Parameterized constructor
 * @param cvd  vector of cv::Points
 */
Polygon::Polygon(const std::vector<cv::Point> &cvd) {
    cvpoints = cvd;
    points.resize(cvd.size());
    for (auto i  =0; i < cvd.size(); i++) {
        points[i].SetX(cvd[i].x);
        points[i].SetY(cvd[i].y);
    }
}

/**
 * @brief Polygon::~Polygon Destructor
 */
Polygon::~Polygon() {
    points.clear();
    cvpoints.clear();
}


/**
 * @brief Polygon::operator =  Copy operator given a polgygon
 * @param that  reference to an existing polygon object
 * @return the  updated Polygon object
 */
Polygon &Polygon::operator=(const Polygon &that) {
    points = that.points;
    cvpoints = that.cvpoints;
    return *this;
}

/**
 * @brief Polygon::operator =  Copy operator given a polgygon
 * @param pts  vector of Point objects
 * @return the  updated Polygon object
 */
Polygon &Polygon::operator=(const std::vector<PointD> &pts) {
    points = pts;
    cvpoints.resize(pts.size());
    for (auto i = 0; i < pts.size(); ++i) {
        cvpoints[i].x = pts[i].GetX();
        cvpoints[i].y = pts[i].GetY();
    }
    return *this;
}

/**
 * @brief Polygon::operator =  Copy operator given a vector of cv::Points
 * @param cvd  vector of cv::Points
 * @return the  updated Polygon object
 */
Polygon &Polygon::operator=(const std::vector<cv::Point> &cvd) {
    cvpoints = cvd;
    points.resize(cvd.size());
    for (auto i = 0; i < cvd.size(); ++i) {
        points[i].SetX(cvd[i].x);
        points[i].SetY(cvd[i].y);
    }
    return *this;
}

/**
 * @brief Polygon::operator [] TODO
 * @param i
 * @return
 */
PointD &Polygon::operator[](int i)
{
    // TODO: test it
    // TODO: Safe access?
    return points[i];
}

/**
 * @brief Polygon::AddPoint  Add a Point to the Polygon
 * @param pt  reference to the Point object to be added.
 */
void Polygon::AddPoint(PointD &pt) {
    points.push_back(pt);
    cvpoints.push_back(cv::Point(pt.GetX(), pt.GetY()));
}

/**
 * @brief Polygon::AddPoint  Add a Point to the Polygon
 * @param x  a double indicating the x coordinate of the new Point.
 * @param y  a double indicating the y coordinate of the new Point.
 */
void Polygon::AddPoint(double x, double y) {
    points.push_back(PointD(x, y));
    cvpoints.push_back(cv::Point(x, y));
}

/**
 * @brief Polygon::SetPoint  Set a Point in the Polygon
 * @param idx  an int indicating the index of the point to be set.
 * @param pt  reference to the Point object with the new information.
 */
void Polygon::SetPoint(int idx, PointD &pt) {
    points[idx] = pt;
    cvpoints[idx] = cv::Point(pt.GetX(), pt.GetY());
}


/**
 * @brief Polygon::SetPoint  Set a Point in the Polygon
 * @param idx  an int indicating the index of the point to be set.
 * @param x  double indicating the new x coordinate.
 * @param y  double indicating the new y coordinate.
 */
void Polygon::SetPoint(int idx, double x, double y) {
    points[idx] = PointD(x, y);
    cvpoints[idx] = cv::Point(x, y);
}

/**
 * @brief Polygon::GetPoint  Get a Point in the Polygon
 * @param i  an int indicating the index of the point to get.
 * @return The de point at index i in points
 */
PointD &Polygon::GetPoint(int i) {
    return points[i];
}

/**
 * @brief Polygon::GetData  Get the Point vector points of the Polygon
 * @return The Polygon attribute points
 */
std::vector<PointD> &Polygon::GetData() {
    return points;
}

/**
 * @brief Polygon::GetData  Get the Point vector points of the Polygon
 * @return The Polygon attribute points
 */
const std::vector<PointD> &Polygon::GetData() const {
    return points;
}

/**
 * @brief Polygon::GetCvData  Get the cv::Point vector cvpoints of the Polygon
 * @return The Polygon attribute cvpoints
 */
std::vector<cv::Point> &Polygon::GetCvData() {
    return cvpoints;
}

/**
 * @brief Polygon::GetCvData  Get the cv::Point vector cvpoints of the Polygon
 * @return The Polygon attribute cvpoints
 */
const std::vector<cv::Point> &Polygon::GetCvData() const {
    return cvpoints;
}

/**
 * @brief Polygon::Resize  Resize the Polygon
 * @param s  an int indicating the new size of the polygon.
 */
void Polygon::Resize(int s) {
    points.resize(s);
    cvpoints.resize(s);
}

/**
 * @brief Polygon::size  Get the size of the Polygon
 * @return The size of the vector points
 */
int Polygon::size() {
    return points.size();
}

/**
 * @brief Polygon::Area  Get the area of the Polygon
 * @return The contour area of the Polygon.
 */
double Polygon::Area() {
    return contourArea(cvpoints);
}

/**
 * @brief Polygon::Perimeter  Get the perimeter of the Polygon
 * @return  The perimeter of the Polygon.
 */
double Polygon::Perimeter() {
    return arcLength(cvpoints, true);
}

/**
 * @brief Polygon::Reduce  Reduce the nº of points in Polygon
 * @param epsilon  int specifying the approximation accuracy. The maximum distance between the original polygon and its approximation.
 * @return Polygon with less points
 */
Polygon Polygon::Reduce(int epsilon) {
    Polygon new_poly;
    // Approximate a curve or a polygon with another curve/polygon 
    // with less vertices so that the distance between them is less or 
    // equal to the specified precision
    approxPolyDP(cv::Mat(cvpoints), new_poly.cvpoints, epsilon, true); 
    new_poly.points.resize(new_poly.cvpoints.size());
    for (auto i = 0; i < new_poly.cvpoints.size(); ++i) {
        new_poly.points[i].SetX(new_poly.cvpoints[i].x);
        new_poly.points[i].SetX(new_poly.cvpoints[i].x);
    }
    return new_poly;
}

/**
 * @brief Polygon::SelfReduce  Reduce the nº of points in Polygon
 * @param epsilon  int specifying the approximation accuracy. The maximum distance between the original polygon and its approximation.
 */
void Polygon::SelfReduce(int epsilon) {
    approxPolyDP(cv::Mat(cvpoints), cvpoints, epsilon, true);
    points.resize(cvpoints.size());
    for (auto i = 0; i < cvpoints.size(); ++i) {
        points[i].SetX(cvpoints[i].x);
        points[i].SetX(cvpoints[i].x);
    }
}


/**
 * @brief Polygon::Shift  Shifts the order (arrangement) Polygon vertices in the vectors points and cvpoints
 * @param sh  int specifying the desired shift
 * @return Polygon with the reordered points and cvpoints vectors
 */
Polygon Polygon::Shift(int sh) {
    Polygon new_poly(*this);
    std::rotate(new_poly.points.begin(), new_poly.points.begin()+sh, new_poly.points.end());
    std::rotate(new_poly.cvpoints.begin(), new_poly.cvpoints.begin()+sh, new_poly.cvpoints.end());
    return new_poly;
}


/**
 * @brief Polygon::SelfShift  Shifts the order (arrangement) Polygon vertices in the vectors points and cvpoints
 * @param sh  int specifying the desired shift
 */
void Polygon::SelfShift(int sh) {
    std::rotate(points.begin(), points.begin() + sh, points.end());
    std::rotate(cvpoints.begin(), cvpoints.begin() + sh, cvpoints.end());
}

}
