#include "ctkpolygon.h"

#include "opencv2/imgproc.hpp"

namespace ctk {

/**
 * @brief Polygon::Polygon  Default constructor.
 */
Polygon::Polygon()
{
}


/**
 * @brief Polygon::Polygon  Copy constructor. Takes a reference to an existing polygon object as input
 * and uses it to intialize another polygon object
 * @param that  reference to an existing polygon object
 */
Polygon::Polygon(const Polygon &that)
{
    data_ = that.data_;
    cvdata_ = that.cvdata_;
}


/**
 * @brief Polygon::Polygon  Parameterized constructor.
 * @param d  vector of Point objects
 */
Polygon::Polygon(std::vector<PointD> &d)
{
    data_ = d;
    cvdata_.resize(d.size());
    for (auto i=0; i<d.size(); i++) {
        cvdata_[i].x = d[i].getX();
        cvdata_[i].y = d[i].getY();
    }
}


/**
 * @brief Polygon::Polygon  Parameterized constructor
 * @param cvd  vector of cv::Points
 */
Polygon::Polygon(std::vector<cv::Point> &cvd)
{
    cvdata_ = cvd;/*!< Sets cvdata_ to the passed vector of cv::Points */
    data_.resize(cvd.size()); /*!< Resizes data_ to the size of the passed vector */
    for (auto i=0; i<cvd.size(); i++) {
        data_[i].setX(cvd[i].x);
        data_[i].setY(cvd[i].y);
    }
}

/**
 * @brief Polygon::~Polygon Destructor
 */
Polygon::~Polygon()
{
    data_.clear();
    cvdata_.clear();
}


/**
 * @brief Polygon::operator =  Overload of = operator given a Polygon object
 * @param that  reference to an existing polygon object
 * @return the  updated Polygon object
 */
Polygon &Polygon::operator=(const Polygon &that)
{
    data_ = that.data_;
    cvdata_ = that.cvdata_;
    return *this;
}


/**
 * @brief Polygon::operator =  Overload of = operator given a vector of Point objects
 * @param d  vector of Point objects
 * @return the  updated Polygon object
 */
Polygon &Polygon::operator=(std::vector<PointD> &d)
{
    data_ = d;
    cvdata_.resize(d.size());
    for (auto i=0; i<d.size(); i++) {
        cvdata_[i].x = d[i].getX();
        cvdata_[i].y = d[i].getY();
    }
    return *this;
}


/**
 * @brief Polygon::operator =  Overload of = operator given a vector of cv::Points
 * @param cvd  vector of cv::Points
 * @return the  updated Polygon object
 */
Polygon &Polygon::operator=(std::vector<cv::Point> &cvd)
{
    cvdata_ = cvd;
    data_.resize(cvd.size());
    for (auto i=0; i<cvd.size(); i++) {
        data_[i].setX(cvd[i].x);
        data_[i].setY(cvd[i].y);
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
    //TODO: test it
    return data_[i];
}


/**
 * @brief Polygon::add_point  Add a Point to the Polygon
 * @param pt  reference to the Point object to be added.
 */
void Polygon::add_point(PointD &pt)
{
    data_.push_back(pt);
    cvdata_.push_back(cv::Point(pt.getX(), pt.getY()));
}


/**
 * @brief Polygon::add_point  Add a Point to the Polygon
 * @param x  a double indicating the x coordinate of the new Point.
 * @param y  a double indicating the y coordinate of the new Point.
 */
void Polygon::add_point(double x, double y)
{
    data_.push_back(PointD(x,y));
    cvdata_.push_back(cv::Point(x, y));
}


/**
 * @brief Polygon::set_point  Set a Point in the Polygon
 * @param idx  an int indicating the index of the point to be set.
 * @param pt  reference to the Point object with the new information.
 */
void Polygon::set_point(int idx, PointD &pt)
{
    data_[idx] = pt;
    cvdata_[idx] = cv::Point(pt.getX(), pt.getY());
}


/**
 * @brief Polygon::set_point  Set a Point in the Polygon
 * @param idx  an int indicating the index of the point to be set.
 * @param x  double indicating the new x coordinate.
 * @param y  double indicating the new y coordinate.
 */
void Polygon::set_point(int idx, double x, double y)
{
    data_[idx] = PointD(x,y);
    cvdata_[idx] = cv::Point(x,y);
}


/**
 * @brief Polygon::point  Get a Point in the Polygon
 * @param i  an int indicating the index of the point to get.
 * @return The de point at index i in data_
 */
PointD &Polygon::point(int i)
{
    return data_[i];
}


/**
 * @brief Polygon::get_data  Get the Point vector data_ of the Polygon
 * @return The Polygon attribute data_
 */
std::vector<PointD> &Polygon::get_data()
{
    return data_;
}


/**
 * @brief Polygon::get_cvdata  Get the cv::Point vector cvdata_ of the Polygon
 * @return The Polygon attribute cvdata_
 */
std::vector<cv::Point> &Polygon::get_cvdata()
{
    return cvdata_;
}


/**
 * @brief Polygon::Resize  Resize the Polygon
 * @param s  an int indicating the new size of the polygon.
 */
void Polygon::Resize(int s)
{
    data_.resize(s);
    cvdata_.resize(s);
}


/**
 * @brief Polygon::size  Get the size of the Polygon
 * @return The size of the vector data_
 */
int Polygon::size()
{
    return data_.size();
}


/**
 * @brief Polygon::Area  Get the area of the Polygon
 * @return The contour area of the Polygon.
 */
double Polygon::Area()
{
    return contourArea(cvdata_);
}


/**
 * @brief Polygon::Perimeter  Get the perimeter of the Polygon
 * @return  The perimeter of the Polygon.
 */
double Polygon::Perimeter()
{
    return arcLength(cvdata_, true);
}


/**
 * @brief Polygon::Reduce  Reduce the nº of points in Polygon
 * @param epsilon  int specifying the approximation accuracy. The maximum distance between the original polygon and its approximation.
 * @return Polygon with less points
 */
Polygon Polygon::Reduce(int epsilon)
{
    Polygon new_poly;
    approxPolyDP(cv::Mat(cvdata_), new_poly.cvdata_, epsilon, true); //approximate a curve or a polygon with another curve/polygon with less vertices so that the distance between them is less or equal to the specified precision
    //
    new_poly.data_.resize(new_poly.cvdata_.size());
    for (auto i=0; i<new_poly.cvdata_.size(); i++) {
        new_poly.data_[i].setX(new_poly.cvdata_[i].x);
        new_poly.data_[i].setX(new_poly.cvdata_[i].x);
    }
    //
    return new_poly;
}

/**
 * @brief Polygon::SelfReduce  Reduce the nº of points in Polygon
 * @param epsilon  int specifying the approximation accuracy. The maximum distance between the original polygon and its approximation.
 */
void Polygon::SelfReduce(int epsilon)
{
    approxPolyDP(cv::Mat(cvdata_), cvdata_, epsilon, true);
    data_.resize(cvdata_.size());
    for (auto i=0; i<cvdata_.size(); i++) {
        data_[i].setX(cvdata_[i].x);
        data_[i].setX(cvdata_[i].x);
    }
}


/**
 * @brief Polygon::Shift  Shifts the order (arrangement) Polygon vertices in the vectors data_ and cvdata_
 * @param sh  int specifying the desired shift
 * @return Polygon with the reordered data_ and cvdata_ vectors
 */
Polygon Polygon::Shift(int sh)
{
    Polygon new_poly(*this);
    std::rotate(new_poly.data_.begin(), new_poly.data_.begin()+sh, new_poly.data_.end());
    std::rotate(new_poly.cvdata_.begin(), new_poly.cvdata_.begin()+sh, new_poly.cvdata_.end());
    return new_poly;
}


/**
 * @brief Polygon::SelfShift  Shifts the order (arrangement) Polygon vertices in the vectors data_ and cvdata_
 * @param sh  int specifying the desired shift
 */
void Polygon::SelfShift(int sh)
{
    std::rotate(data_.begin(), data_.begin()+sh, data_.end());
    std::rotate(cvdata_.begin(), cvdata_.begin()+sh, cvdata_.end());
}

}
