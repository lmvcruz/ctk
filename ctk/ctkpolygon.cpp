#include "ctkpolygon.h"

#include "opencv2/imgproc.hpp"

namespace ctk {

/**
 * @brief Polygon::Polygon Default constructor.
 */
Polygon::Polygon()
{
}



/**
 * @brief Polygon::Polygon Copy constructor. Takes a reference to an existing polygon object as input
 * and uses it to intialize another polygon object
 * @param that  reference to an existing polygon object
 */
Polygon::Polygon(const Polygon &that)
{
    data_ = that.data_;
    cvdata_ = that.cvdata_;
}


/**
 * @brief Polygon::Polygon Parameterized constructor.
 * @param d
 */

Polygon::Polygon(std::vector<PointD> &d)
{
    data_ = d; /*!< Sets data_ to the passed vector of Point objects */
    cvdata_.resize(d.size()); /*!< Resizes cvdata to the size of the passed vector */
    for (auto i=0; i<d.size(); i++) {
        /*!Assigns the value of x and y of each element in cv_data to the value of x_ and y_
 of the respective element in the passed vector*/
        cvdata_[i].x = d[i].getX();
        cvdata_[i].y = d[i].getY();
    }
}

//! Parameterized constructor.
/*! Takes a reference to a vector of cv::Points as input
 * and uses it to intialize another polygon object. */

Polygon::Polygon(std::vector<cv::Point> &cvd)
{
    cvdata_ = cvd;/*!< Sets cvdata_ to the passed vector of cv::Points */
    data_.resize(cvd.size()); /*!< Resizes data_ to the size of the passed vector */
    for (auto i=0; i<cvd.size(); i++) {
        /*!Assigns the value of x and y of each element in data_ to the value of x and y
 of the respective element in the passed vector ??????????? */
        data_[i].setX(cvd[i].x);
        data_[i].setY(cvd[i].y);
    }
}

//! Destructor.

Polygon::~Polygon()
{
    data_.clear();
    cvdata_.clear();
}

//! Overload of = operator given a Polygon object
/*! Sets the attributes data_ and cvdata_ to copies of the respective
 *  attributes in the passed object
 *  Returns the update Polygon object*/

Polygon &Polygon::operator=(const Polygon &that)
{
    data_ = that.data_;
    cvdata_ = that.cvdata_;
    return *this;
}

//! Overload of = operator given a vector of Point objects
/*! Sets the attribute data_ to the passed vector
 *  Assigns the value of x and y of each element in cvdata_ to the value of x_ and y_
 of the respective element in the passed vector
 *  Returns the update Polygon object */

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

//! Overload of = operator given a vector of cv::Points
/*! Sets the attribute cvdata_ to the passed vector
 *  Assigns the value of x_ and y_ of each element in cvdata_ to the value of x_ and y_
 of the respective element in the passed vector
 *  Returns the update Polygon object */

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

//! Add a Point Object to the Polygonn
   /*!
     \param &pt reference to the Point object to be added.
   */
void Polygon::add_point(PointD &pt)
{
    data_.push_back(pt);  /*!< Adds pt to data_ */
    cvdata_.push_back(cv::Point(pt.getX(), pt.getY())); /*!< Creates a new cv::Point from pt and adds it to cvdata_ */
}

//! Add a Point to the Polygonn
   /*!
     \param x a double indicating the x coordinate of the new Point.
     \param y a double indicating the y coordinate of the new Point.
   */
/*! Creates a Point object and a cv::Point and adds them to data_ and cvdata_ respectively */

void Polygon::add_point(double x, double y)
{
    data_.push_back(PointD(x,y));
    cvdata_.push_back(cv::Point(x, y));
}

//! Set a Point in the Polygonn
   /*!
     \param idx a int indicating the index of the point to be set.
     \param &pt reference to the Point object.
   */
/*! Sets the point at index idx in data_ to the passed Point */
/*! Creates a new cv::Point with the x_ and y_ from the passed Point object and
 * sets the point at index idx in cvdata_ to this new point */


void Polygon::set_point(int idx, PointD &pt)
{
    data_[idx] = pt;
    cvdata_[idx] = cv::Point(pt.getX(), pt.getY());
}


//! Set a Point in the Polygonn
   /*!
     \param idx a int indicating the index of the point to be set.
     \param x double indicating the new x coordinate.
     \param y double indicating the new y coordinate.
   */

void Polygon::set_point(int idx, double x, double y)
{
    data_[idx] = PointD(x,y);
    cvdata_[idx] = cv::Point(x,y);
}

//! Get a Point in the Polygonn
   /*!
     \param i a int indicating the index of the point to be set.
     \return The de point at index i in data_
   */

PointD &Polygon::point(int i)
{
    return data_[i];
}

//! Get the data of the Polygonn
   /*!
     \return The de attribute data_
   */
std::vector<PointD> &Polygon::get_data()
{
    return data_;
}

//! Get the data of the Polygonn
   /*!
     \return The de attribute cvdata_
   */
std::vector<cv::Point> &Polygon::get_cvdata()
{
    return cvdata_;
}

//! Resize the Polygonn
   /*!
     \param s a int indicating the new size of the polygon.
   */
void Polygon::Resize(int s)
{
    data_.resize(s);
    cvdata_.resize(s);
}

//! Get the size of the Polygonn
   /*!
     \return The size of the attribute data_
   */
int Polygon::size()
{
    return data_.size();
}

//! Get the size of the Polygonn
   /*!
     \return The contour area of the Polygon.
   */
double Polygon::Area()
{
    return contourArea(cvdata_);
}

//! Get the size of the Polygonn
   /*!
     \return The perimeter of the Polygon.
   */
double Polygon::Perimeter()
{
    return arcLength(cvdata_, true);
}

//! Reduce the Polygon ????
   /*!
     \param epsilon int specifying the approximation accuracy. The maximum distance between the original polygon and its approximation.
     \return A reduced Polygon.
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

void Polygon::SelfReduce(int epsilon)
{
    approxPolyDP(cv::Mat(cvdata_), cvdata_, epsilon, true);
    data_.resize(cvdata_.size());
    for (auto i=0; i<cvdata_.size(); i++) {
        data_[i].setX(cvdata_[i].x);
        data_[i].setX(cvdata_[i].x);
    }
}

//! Rotates the Polygon
   /*!
     \param sh int specifying the nº of points to rotate the polygon by
     \return A reduced Polygon.
   */

Polygon Polygon::Shift(int sh)
{
    Polygon new_poly(*this);
    std::rotate(new_poly.data_.begin(), new_poly.data_.begin()+sh, new_poly.data_.end());
    std::rotate(new_poly.cvdata_.begin(), new_poly.cvdata_.begin()+sh, new_poly.cvdata_.end());
    return new_poly;
}


//! Rotates the Polygon
   /*!
     \param sh int specifying the nº of points to rotate the polygon by
   */

void Polygon::SelfShift(int sh)
{
    std::rotate(data_.begin(), data_.begin()+sh, data_.end());
    std::rotate(cvdata_.begin(), cvdata_.begin()+sh, cvdata_.end());
}

}
