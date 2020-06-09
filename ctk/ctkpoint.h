#ifndef CTKGEOMETRY_H
#define CTKGEOMETRY_H

#include <cmath>

#include "ctkexceptions.h"

namespace ctk {

//! Creates a template T - point coordinates' type
template<class T>
class Point{
private:
    T x_, y_, z_; /*!< Each point has three attributes: x_,y_,z_ */

public:

    //! Default constructor.
    /*! Creates a new Point object and sets the values od x_,y_,z_ to 0 */
    Point(T x=0, T y=0, T z=0) {
        x_ = x;
        y_ = y;
        z_ = z;
    }

    //! Copy constructor.
    /*! Takes a reference to an existing Point object as input (Point &that)
     * and uses it to intialize another Point object . */
    Point(const Point &that) {
        x_ = that.x_; /*!< the value of x_ is a copy of the value of that.x_ */
        y_ = that.y_; /*!< the value of y_ is a copy of the value of that.y_ */
        z_ = that.z_; /*!< the value of z_ is a copy of the value of that.z_ */
    }

    //! Destructor
    virtual ~Point() {}

    //! Overload of = operator
    /*!  */
    Point& operator=(const Point &that) {
        x_ = that.x_;
        y_ = that.y_;
        z_ = that.z_;
        return *this;
    }

    //! Overload of == operator
    bool operator==(const Point &that) {
        return (*this==that);
    }

    //! Overload of != operator
    bool operator!=(const Point &that) {
        return !(*this==that);
    }

    //! Function to set the values of the attributes x_,y_ and z_
    /*! Takes the desired values x, y and z as input and sets the Point's attributes
    x_,y_ and z_ to those values. The value of z_ is set to 0 by default*/
    void set(T x, T y, T z=0) {
        x_ = x;
        y_ = y;
        z_ = z;
    }

    //! Function to set the value of the attribute x_
    /*! Takes the desired value x and sets the Point's attribute x_ that value.*/
    void setX(T x) {
        x_ = x;
    }

    //! Function to access the value of the attribute x_
    /*! Returns attribute x_ .*/
    T getX() {
        return x_;
    }

    //! Function to set the valus of the attribute y_
    /*! Takes the desired value y and sets the Point's attribute y_ that value.*/
    void setY(T y) {
        y_ = y;
    }

    //! Function to access the value of the attribute y_
    /*! Returns attribute y_ .*/
    T getY() {
        return y_;
    }

    //! Function to set the value of the attribute z_
    /*! Takes the desired value y and sets the Point's attribute z_ that value.*/
    void setZ(T z) {
        z_ = z;
    }

    //! Function to access the value of the attribute y_
    /*! Returns attribute z_ .*/
    int getZ() {
        return z_;
    }

    //! Overload of the addition (+) operator with another Point object
    /*! The sum of two Point objects corresponds to the sum of their corresponding
     * individual attributes x_, y_, z_  .*/
    Point operator+(const Point &that) {
        return Point(x_+that.x_, y_+that.y_, z_+that.z_);
    }

    //! Overload of the addition assignment (+=) operator with another Point object
    /*! The new value of each attribue x_, y_, z_ corresponds to the current value of
      that attribute plus the value of the attribute in the passed Point*/
    void operator+=(const Point &that) {
        x_ += that.x_;
        y_ += that.y_;
        z_ += that.z_;
    }

    //! Overload of the addition (+) operator with a variable of type T
    /*! The sum of a Point object and a variable of type T corresponds to the sum of its
     * individual attributes x_, y_, z_ and the passed variable   .*/
    Point operator+(T v) {
        return Point(x_ + v.x_, y_ + v.y_, z_ + v.z_);
    }

    //! Overload of the addition assignment (+=) operator with a variable of type T
    /*! The new value of each attribue x_, y_, z_ corresponds to the current value of
      that attribute plus the passed variable*/
    void operator+=(T v) {
        x_ += v.x_;
        y_ += v.y_;
        z_ += v.z_;
    }

    //! Overload of the subtraction (-) operator with another Point object
    /*! The sum of two Point objects corresponds to the subtracton of their corresponding
     * individual attributes x_, y_, z_  .*/
    Point operator-(const Point &that) {
        return Point(x_-that.x_, y_-that.y_, z_-that.z_);
    }

    //! Overload of the subtraction assignment (-=) operator with another Point object
    /*! The new value of each attribue x_, y_, z_ corresponds to the current value of
      that attribute minus the value of the attribute in the passed Point*/
    void operator-=(const Point &that) {
        x_ -= that.x_;
        y_ -= that.y_;
        z_ -= that.z_;
    }


    Point operator-(T v) {
        return Point(x_ - v.x_, y_ - v.y_, z_ - v.z_);
    }


    void operator-=(T v) {
        x_ -= v.x_;
        y_ -= v.y_;
        z_ -= v.z_;
    }

    //! Overload of the multiplication (*) operator with another Point object
    /*! The multiplication of two Point objects corresponds to the multiplication of their corresponding
     * individual attributes x_, y_, z_  .*/
    Point operator*(const Point &that) {
        return Point(x_*that.x_, y_*that.y_, z_*that.z_);
    }

    //! Overload of the multiplication assignment (*=) operator with another Point object
    /*! The new value of each attribue x_, y_, z_ corresponds to the current value of
      that attribute multiplied by the value of the attribute in the passed Point*/
    void operator*=(const Point &that) {
        x_ *= that.x_;
        y_ *= that.y_;
        z_ *= that.z_;
    }


    Point operator*(T v) {
        return Point(x_ * v.x_, y_ * v.y_, z_ * v.z_);
    }

    void operator*=(T v) {
        x_ *= v.x_;
        y_ *= v.y_;
        z_ *= v.z_;
    }

    //! Overload of the division (/) operator with another Point object
    /*! The division of two Point objects corresponds to the division of their corresponding
     * individual attributes x_, y_, z_ .*/
    Point operator/(const Point &that) {

        /*!If any attribute of the passed object is zeros an exception is thrown. */
        if((that.x_==0) || (that.y_==0) || (that.z_==0)) {
            throw division_per_zero();
        }
        return Point(x_/that.x_, y_/that.y_, z_/that.z_);
    }

    //! Overload of the division assignment (/=) operator with another Point object
    /*! The new value of each attribue x_, y_, z_ corresponds to the current value of
      that attribute devided by the value of the attribute in the passed Point*/
    void operator/=(const Point &that) {

        /*!If any attribute of the passed object is zeros an exception is thrown. */
        if((that.x_==0) || (that.y_==0) || (that.z_==0)) {
            throw division_per_zero();
        }
        x_ /= that.x_;
        y_ /= that.y_;
        z_ /= that.z_;
    }


    Point operator/(T v) {

        if((v.x_==0) || (v.y_==0) || (v.z_==0)) {
            throw division_per_zero();
        }
        return Point(x_/v.x_, y_/v.y_, z_/v.z_);
    }

    void operator/=(T v) {
        if((v.x_==0) || (v.y_==0) || (v.z_==0)) {
            throw division_per_zero();
        }
        x_ /= v.x_;
        y_ /= v.y_;
        z_ /= v.z_;
    }

    //! ???
    // Mudar para ManhattanDistance()?
    int ManhattanLength() {
        int ml = std::fabs(x_) + std::fabs(x_) + std::fabs(x_);
        return static_cast<int>(ml);
    }

    //! Defines the norm of the point
    double Norm() {
        return std::sqrt(x_*x_ + y_*y_ + z_*z_) ;
    }

    //! Inner product with another Point object
    double inner(const Point &p) {
        return x_*p.x_ + y_*p.y_ + z_*p.z_;
    }

    //! Outter product with another Point object
    Point outter(const Point &p){
        return Point(y_*p.z_ - z_*p.y_,
                     -1*(x_*p.z_ - z_*p.x_),
                     x_*p.y_ - y_*p.x_ );
    }

     //! Euclidean distance to another Point object
    double Distance(const Point &p) {
        return std::sqrt( (x_-p.x_)*(x_-p.x_) + (y_-p.y_)*(y_-p.y_) + (z_-p.z_)*(z_-p.z_) );
    }

    //! Angle formed with two other Point objects
    double Angle(const Point &pa, const Point &pb) {
        double p_pa = Distance(pa);
        double p_pb = Distance(pb);
        double pa_pb = (pa-pb).Norm();

        return std::acos((p_pa*p_pa + p_pb*p_pb + pa_pb*pa_pb)/(2*p_pa*p_pb));
    }

    //! Normalizes the point dividing it by its norm
    //! Returns normalized point
    Point normalize() {
        double n = Norm();
        return *this / n;
    }

    //! Normalizes the point dividing it by its norm
    void SelfNormalize() {
        double n = Norm();
        *this /= n;
    }

};

typedef Point<int> PointI;
typedef Point<double> PointD;

}

#endif // CTKGEOMETRY_H
