#pragma once

#include <cmath>

#include "ctk/core/exceptions.h"

namespace ctk {

template<class T>
class Point {
private:
    T x_, y_, z_; /*!< Each point has three attributes: x_,y_,z_ */

public:

    /**
     * @brief Point  Default constructor.
     * @param x  x coordinate, set to 0
     * @param y  y coordinate, set to 0
     * @param z  z coordinate, set to 0
     */
    Point(T x=0, T y=0, T z=0) {
        x_ = x;
        y_ = y;
        z_ = z;
    }

    /**
     * @brief Point Copy constructor.
     * @param that  Reference to an existing Point object
     */
    Point(const Point &that) {
        x_ = that.x_; /*!< the value of x_ is a copy of the value of that.x_ */
        y_ = that.y_; /*!< the value of y_ is a copy of the value of that.y_ */
        z_ = that.z_; /*!< the value of z_ is a copy of the value of that.z_ */
    }

    /**
     * @brief ~Point  Destructor
     */
    virtual ~Point() {}

    /**
     * @brief operator =  Overload of copy operator given another Point object
     * @param that  Reference to an existing Point object
     * @return Updated Point objecy
     */
    Point& operator=(const Point &that) {
        x_ = that.x_;
        y_ = that.y_;
        z_ = that.z_;
        return *this;
    }

    //!
    /**
    * @brief operator ==  Overload of is equal operator given another Point object
    * @param that  Reference to an existing Point object
    * @return boolean indicating the result of the == comparison between the two Points
    */
    bool operator==(Point  const &that ) const  {
        if ((that.x_ != x_) || (that.y_ != y_) || (that.z_ != z_)) {
            return false;
        } else {
            return true;
        }
     //return (*this==that);
    }

    //! Overload of != operator
    /**
    * @brief operator !=  Overload of is different operator given another Point object
    * @param that  Reference to an existing Point object
    * @return boolean indicating the result of the != comparison between the two Points
    */
    bool operator!=(Point const  &that) const {
        return !(*this == that);
    }

    /**
     * @brief set  Function to set the values of the attributes x_,y_ and z_
     * @param x  desired value of x_
     * @param y  desired value of y_
     * @param z  desired value of z_
     */
    void Set(T x, T y, T z=0) {
        x_ = x;
        y_ = y;
        z_ = z;
    }

    /**
     * @brief setX  Function to set the value of the attribute x_
     * @param x  desired value of x_
     */
    void setX(T x) {
        x_ = x;
    }

    /**
     * @brief getX  Function to access the value of the attribute x_
     * @return Attribute x_
     */
    T getX() {
        return x_;
    }

    /**
     * @brief setY  Function to set the valus of the attribute y_
     * @param y  desired value of y_
     */
    void setY(T y) {
        y_ = y;
    }

    /**
     * @brief getY  Function to access the value of the attribute y_
     * @return Attribute y_
     */
    T getY() {
        return y_;
    }

    /**
     * @brief setZ  Function to set the value of the attribute z_
     * @param z  desired value of z_
     */
    void setZ(T z) {
        z_ = z;
    }

    /**
     * @brief getZ  Function to access the value of the attribute z_
     * @return Attribute z_
     */
    T getZ() {
        return z_;
    }

    /**
     * @brief operator +  Overload of the addition operator with another Point object
     * @param that  Reference to an existing Point object
     * @return The sum of two Point objects corresponds to the sum of their corresponding
     * individual attributes x_, y_, z_
     */
    Point operator+(const Point &that) {
        return Point(x_ + that.x_, y_ + that.y_, z_ + that.z_);
    }

    /**
     * @brief operator +=  Overload of the addition assignment operator with another Point object. The new value of each attribue x_, y_, z_ corresponds to the current value of
      that attribute plus the value of the attribute in the passed Point
     * @param that  Reference to an existing Point object
     */
    void operator+=(const Point &that) {
        x_ += that.x_;
        y_ += that.y_;
        z_ += that.z_;
    }

    /**
     * @brief operator +  Overload of the addition operator with a variable of type T
     * @param v  variable of type T
     * @return  The sum of a Point object and a variable of type T corresponds to the sum of their corresponding
     * individual attributes x_, y_, z_
     */
    Point operator+(T v) {
        return Point(x_ + v.x_, y_ + v.y_, z_ + v.z_);
    }

    /**
     * @brief operator +=  Overload of the addition assignment operator with a variable of type T. The new value of each attribue x_, y_, z_ corresponds to the current value of
      that attribute plus the value of the attribute in the variable
     * @param v  variable of type T
     */
    void operator+=(T v) {
        x_ += v.x_;
        y_ += v.y_;
        z_ += v.z_;
    }

    /**
     * @brief operator -  Overload of the subtraction operator with another Point object
     * @param that  Reference to an existing Point object
     * @return  The subtraction of two Point objects corresponds to the subtracton of their corresponding
     * individual attributes x_, y_, z_  .
     */
    Point operator-(const Point &that) {
        return Point(x_ - that.x_, y_ - that.y_, z_ - that.z_);
    }

    /**
     * @brief operator -=  Overload of the subtraction assignment operator with another Point object. The new value of each attribue x_, y_, z_ corresponds to the current value of
      that attribute minus the value of the attribute in the passed Point
     * @param that  Reference to an existing Point object
     */
    void operator-=(const Point &that) {
        x_ -= that.x_;
        y_ -= that.y_;
        z_ -= that.z_;
    }

    /**
     * @brief operator -  Overload of the subtraction operator with a variable of type T
     * @param v  variable of type T
     * @return The subtraction of a Point object and a variable of type T corresponds to the subtraction of their corresponding
     * individual attributes x_, y_, z_
     */
    Point operator-(T v) {
        return Point(x_ - v.x_, y_ - v.y_, z_ - v.z_);
    }

    /**
     * @brief operator -=  Overload of the subtraction assignment operator with a variable of type T. The new value of each attribue x_, y_, z_ corresponds to the current value of
      that attribute minus the value of the attribute in the variable
     * @param v variable of type T
     */
    void operator-=(T v) {
        x_ -= v.x_;
        y_ -= v.y_;
        z_ -= v.z_;
    }

    /**
     * @brief operator *  Overload of the multiplication operator with another Point object
     * @param that  Reference to an existing Point object
     * @return The multiplication of two Point objects corresponds to the multiplication of their corresponding
     * individual attributes x_, y_, z_  .
     */
    Point operator*(const Point &that) {
        return Point(x_*that.x_, y_*that.y_, z_*that.z_);
    }

    /**
     * @brief operator *=   Overload of the multiplication assignment operator with another Point object. The new value of each attribue x_, y_, z_ corresponds to the current value of
      that attribute multiplied by the value of the attribute in the passed Point
     * @param that  Reference to an existing Point object
     */
    void operator*=(const Point &that) {
        x_ *= that.x_;
        y_ *= that.y_;
        z_ *= that.z_;
    }

    /**
     * @brief operator *  Overload of the multiplication operator with variable of type T
     * @param v  variable of type T
     * @return The multiplication of a Point object and a variable of type T corresponds to the multiplication of their corresponding
     * individual attributes x_, y_, z_
     */
    Point operator*(T v) {
        return Point(x_ * v.x_, y_ * v.y_, z_ * v.z_);
    }

    /**
     * @brief operator *=  Overload of the multiplication assignment operator with a variable of type T. The new value of each attribue x_, y_, z_ corresponds to the current value of
      that attribute multiplied by the value of the attribute in the passed variable.
     * @param v  variable of type T
     */
    void operator*=(T v) {
        x_ *= v.x_;
        y_ *= v.y_;
        z_ *= v.z_;
    }

    /**
     * @brief operator /  Overload of the division operator with another Point object
     * @param that  Reference to an existing Point object
     * @return The division of two Point objects corresponds to the division of their corresponding
     * individual attributes x_, y_, z_ .
     */
    Point operator/(const Point &that) {
        if((that.x_==0) || (that.y_==0) || (that.z_==0)) {
            throw division_per_zero();
        }
        return Point(x_/that.x_, y_/that.y_, z_/that.z_);
    }

    /**
     * @brief operator /=  Overload of the division assignment operator with another Point object. The new value of each attribue x_, y_, z_ corresponds to the current value of
      that attribute devided by the value of the attribute in the passed Point.
     * @param that  Reference to an existing Point object
     */
    void operator/=(const Point &that) {
        if((that.x_==0) || (that.y_==0) || (that.z_==0)) {
            throw division_per_zero();
        }
        x_ /= that.x_;
        y_ /= that.y_;
        z_ /= that.z_;

    }

    /**
     * @brief operator /  Overload of the division operator with a variable of type T
     * @param v  variable of type T
     * @return The division of a Point object and a variable of type T corresponds to the division of their corresponding
     * individual attributes x_, y_, z_
     */
    Point operator/(T v) {
        /*!If any attribute of the passed variable is zero an exception is thrown. */
        /*if((v.x_==0) || (v.y_==0) || (v.z_==0)) {
            throw division_per_zero();
        }
        return Point(x_/v.x_, y_/v.y_, z_/v.z_);*/
        if((v==0)) {
            throw division_per_zero();
        }
        return Point(x_/v, y_/v, z_/v);
    }

    /**
     * @brief operator /=  Overload of the division assignment operator with a variable of type T
     * @param v a variable of type T
     */
    void operator/=(T v) {
        /*!If any attribute of the passed variable is zero an exception is thrown. */
        /*if((v.x_==0) || (v.y_==0) || (v.z_==0)) {
            throw division_per_zero();
        }
        x_ /= v.x_;
        y_ /= v.y_;
        z_ /= v.z_;*/
        if((v==0)) {
            throw division_per_zero();
        }
        x_ /= v;
        y_ /= v;
        z_ /= v;
    }

    // TODO: Mudar para ManhattanDistance()
    /**
     * @brief ManhattanLength
     * @return the Manhattam length of the Point
     */
    int ManhattanLength() {
        int ml = std::fabs(x_) + std::fabs(y_) + std::fabs(z_);
        return static_cast<int>(ml);
    }

    /**
     * @brief Norm
     * @return the L^2 norm of the point
     */
    double Norm() {
        return std::sqrt(x_*x_ + y_*y_ + z_*z_) ;
    }

    /**
    * @brief inner  Performs the inner product with another Point object
    * @param p  Reference to an existing point object
    * @return inner product of the two points
    */
    double inner(const Point &p) {
        return x_*p.x_ + y_*p.y_ + z_*p.z_;
    }

    /**
    * @brief outter  Performs the outter product with another Point object
    * @param p  Reference to an existing point object
    * @return outter product of the two points
    */
    Point outter(const Point &p) {
        return Point(y_*p.z_ - z_*p.y_,
                     -1*(x_*p.z_ - z_*p.x_),
                     x_*p.y_ - y_*p.x_ );
    }

     //! Euclidean distance to another Point object
    /**
     * @brief Distance  Computes the euclidean distance to another Point object
     * @param p  Reference to an existing point object
     * @return euclidean distance between the two points
     */
    double Distance(const Point &p) {
        return std::sqrt( (x_-p.x_)*(x_-p.x_) + (y_-p.y_)*(y_-p.y_) + (z_-p.z_)*(z_-p.z_) );
    }

    /**
    * @brief Angle  Angle formed with two other Point objects
    * @param pa  Reference to an existing point object
    * @param pb  Reference to an existing point object
    * @return double representing the Angle formed with the two Points in radians
    */
     double Angle (Point &pa,  Point &pb) {
        double p_pa = Distance(pa);
        double p_pb = Distance(pb);
        double pa_pb = (pa-pb).Norm();
        return std::acos((p_pa*p_pa + p_pb*p_pb - pa_pb*pa_pb)/(2*p_pa*p_pb));
    }

    /**
     * @brief normalize  Normalizes the point dividing it by its norm
     * @return normalized point
     */
    Point normalize() {
        double n = Norm();
        return *this / n;
    }

    /**
    * @brief SelfNormalize  Normalizes the point dividing it by its norm
    */
    void SelfNormalize() {
        double n = Norm();
        *this /= n;
    }
};

/**
 * @brief PointI Point object with attributes of type int
 */
typedef Point<int> PointI;

/**
 * @brief PointD  Point object with attributes of type double
 */
typedef Point<double> PointD;
}
