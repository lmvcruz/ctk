#pragma once

#include <cmath>

#include "ctk/core/exceptions.h"

namespace ctk {

template<class T>
class Point {
private:
    T x, y, z;

public:

    /**
     * @brief Point  Default constructor.
     * @param x  x coordinate, set to 0
     * @param y  y coordinate, set to 0
     * @param z  z coordinate, set to 0
     */
    Point(T x_=0, T y_=0, T z_=0) {
        x = x_;
        y = y_;
        z = z_;
    }

    /**
     * @brief Point Copy constructor.
     * @param that  Reference to an existing Point object
     */
    Point(const Point &that) {
        x = that.x;
        y = that.y;
        z = that.z;
    }

    /**
     * @brief ~Point  Destructor
     */
    virtual ~Point() = default;

    /**
     * @brief operator =  Overload of copy operator given another Point object
     * @param that  Reference to an existing Point object
     * @return Updated Point objecy
     */
    Point& operator=(const Point &that) {
        x = that.x;
        y = that.y;
        z = that.z;
        return *this;
    }

    /**
    * @brief operator ==  Overload of is equal operator given another Point object
    * @param that  Reference to an existing Point object
    * @return boolean indicating the result of the == comparison between the two Points
    */
    bool operator==(Point const &that ) const  {
        if ((that.x != x) || (that.y != y) || (that.z != z)) {
            return false;
        }
        return true;
    }

    /**
    * @brief operator !=  Overload of is different operator given another Point object
    * @param that  Reference to an existing Point object
    * @return boolean indicating the result of the != comparison between the two Points
    */
    bool operator!=(Point const  &that) const {
        return !(*this == that);
    }

    /**
     * @brief set  Function to set the values of the attributes x,y and z
     * @param x  desired value of x
     * @param y  desired value of y
     * @param z  desired value of z
     */
    void Set(T x_, T y_, T z_=0) {
        x = x_;
        y = y_;
        z = z_;
    }

    /**
     * @brief SetX  Function to set the value of the attribute x
     * @param x  desired value of x
     */
    void SetX(T x_) {
        x = x_;
    }

    /**
     * @brief GetX  Function to access the value of the attribute x
     * @return Attribute x
     */
    T GetX() const{
        return x;
    }

    /**
     * @brief SetY  Function to set the valus of the attribute y
     * @param y  desired value of y
     */
    void SetY(T y_) {
        y = y_;
    }

    /**
     * @brief GetY  Function to access the value of the attribute y
     * @return Attribute y
     */
    T GetY() const {
        return y;
    }

    /**
     * @brief SetZ  Function to set the value of the attribute z
     * @param z  desired value of z
     */
    void SetZ(T z_) {
        z = z_;
    }

    /**
     * @brief GetZ  Function to access the value of the attribute z
     * @return Attribute z
     */
    T GetZ() const {
        return z;
    }

    /**
     * @brief operator +  Overload of the addition operator with another Point object
     * @param that  Reference to an existing Point object
     * @return The sum of two Point objects corresponds to the sum of their corresponding
     * individual attributes x, y, z
     */
    Point operator+(const Point &that) const {
        return Point(x + that.x, y + that.y, z + that.z);
    }

    /**
     * @brief operator +=  Overload of the addition assignment operator with another Point object. The new value of each attribue x, y, z corresponds to the current value of
      that attribute plus the value of the attribute in the passed Point
     * @param that  Reference to an existing Point object
     */
    void operator+=(const Point &that) {
        x += that.x;
        y += that.y;
        z += that.z;
    }

    /**
     * @brief operator +  Overload of the addition operator with a variable of type T
     * @param v  variable of type T
     * @return  The sum of a Point object and a variable of type T corresponds to the sum of their corresponding
     * individual attributes x, y, z
     */
    Point operator+(T v) const {
        return Point(x + v.x, y + v.y, z + v.z);
    }

    /**
     * @brief operator +=  Overload of the addition assignment operator with a variable of type T. The new value of each attribue x, y, z corresponds to the current value of
      that attribute plus the value of the attribute in the variable
     * @param v  variable of type T
     */
    void operator+=(T v) {
        x += v.x;
        y += v.y;
        z += v.z;
    }

    /**
     * @brief operator -  Overload of the subtraction operator with another Point object
     * @param that  Reference to an existing Point object
     * @return  The subtraction of two Point objects corresponds to the subtracton of their corresponding
     * individual attributes x, y, z  .
     */
    Point operator-(const Point &that) const {
        return Point(x - that.x, y - that.y, z - that.z);
    }

    /**
     * @brief operator -=  Overload of the subtraction assignment operator with another Point object. The new value of each attribue x, y, z corresponds to the current value of
      that attribute minus the value of the attribute in the passed Point
     * @param that  Reference to an existing Point object
     */
    void operator-=(const Point &that) {
        x -= that.x;
        y -= that.y;
        z -= that.z;
    }

    /**
     * @brief operator -  Overload of the subtraction operator with a variable of type T
     * @param v  variable of type T
     * @return The subtraction of a Point object and a variable of type T corresponds to the subtraction of their corresponding
     * individual attributes x, y, z
     */
    Point operator-(T v) const {
        return Point(x - v.x, y - v.y, z - v.z);
    }

    /**
     * @brief operator -=  Overload of the subtraction assignment operator with a variable of type T. The new value of each attribue x, y, z corresponds to the current value of
      that attribute minus the value of the attribute in the variable
     * @param v variable of type T
     */
    void operator-=(T v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
    }

    /**
     * @brief operator *  Overload of the multiplication operator with another Point object
     * @param that  Reference to an existing Point object
     * @return The multiplication of two Point objects corresponds to the multiplication of their corresponding
     * individual attributes x, y, z  .
     */
    Point operator*(const Point &that) const {
        return Point(x * that.x, y * that.y, z * that.z);
    }

    /**
     * @brief operator *=   Overload of the multiplication assignment operator with another Point object. The new value of each attribue x, y, z corresponds to the current value of
      that attribute multiplied by the value of the attribute in the passed Point
     * @param that  Reference to an existing Point object
     */
    void operator*=(const Point &that) {
        x *= that.x;
        y *= that.y;
        z *= that.z;
    }

    /**
     * @brief operator *  Overload of the multiplication operator with variable of type T
     * @param v  variable of type T
     * @return The multiplication of a Point object and a variable of type T corresponds to the multiplication of their corresponding
     * individual attributes x, y, z
     */
    Point operator*(T v) const {
        return Point(x * v.x, y * v.y, z * v.z);
    }

    /**
     * @brief operator *=  Overload of the multiplication assignment operator with a variable of type T. The new value of each attribue x, y, z corresponds to the current value of
      that attribute multiplied by the value of the attribute in the passed variable.
     * @param v  variable of type T
     */
    void operator*=(T v) {
        x *= v.x;
        y *= v.y;
        z *= v.z;
    }

    /**
     * @brief operator /  Overload of the division operator with another Point object
     * @param that  Reference to an existing Point object
     * @return The division of two Point objects corresponds to the division of their corresponding
     * individual attributes x, y, z .
     */
    Point operator/(const Point &that) const {
        if (that.x == 0 || that.y == 0 || that.z == 0) {
            throw division_per_zero();
        }
        return Point(x / that.x, y / that.y, z / that.z);
    }

    /**
     * @brief operator /=  Overload of the division assignment operator with another Point object. The new value of each attribue x, y, z corresponds to the current value of
      that attribute devided by the value of the attribute in the passed Point.
     * @param that  Reference to an existing Point object
     */
    void operator/=(const Point &that) {
        if (that.x == 0 || that.y == 0 || that.z ==0 ) {
            throw division_per_zero();
        }
        x /= that.x;
        y /= that.y;
        z /= that.z;

    }

    /**
     * @brief operator /  Overload of the division operator with a variable of type T
     * @param v  variable of type T
     * @return The division of a Point object and a variable of type T corresponds to the division of their corresponding
     * individual attributes x, y, z
     */
    Point operator/(T v) const {
        if (v == 0) {
            throw division_per_zero();
        }
        return Point(x / v, y / v, z / v);
    }

    /**
     * @brief operator /=  Overload of the division assignment operator with a variable of type T
     * @param v a variable of type T
     */
    void operator/=(T v) {
        if (v == 0) {
            throw division_per_zero();
        }
        x /= v;
        y /= v;
        z /= v;
    }

    /**
     * @brief ManhattanLength
     * @return the Manhattam length of the Point
     */
    int ManhattanLength() const {
        int ml = std::fabs(x) + std::fabs(y) + std::fabs(z);
        return static_cast<int>(ml);
    }

    /**
     * @brief Norm
     * @return the L^2 norm of the point
     */
    double Norm() const {
        return std::sqrt(x*x + y*y + z*z) ;
    }

    /**
    * @brief Inner  Performs the inner product with another Point object
    * @param p  Reference to an existing point object
    * @return inner product of the two points
    */
    double Inner(const Point &p) const {
        return x*p.x + y*p.y + z*p.z;
    }

    /**
    * @brief Outter  Performs the outter product with another Point object
    * @param p  Reference to an existing point object
    * @return outter product of the two points
    */
    Point Outter(const Point &p) const {
        return Point(y*p.z - z*p.y,
                     -1 * (x*p.z - z*p.x),
                     x*p.y - y*p.x );
    }

    /**
     * @brief Distance  Computes the euclidean distance to another Point object
     * @param p  Reference to an existing point object
     * @return euclidean distance between the two points
     */
    double Distance(const Point &p) const {
        return std::sqrt((x - p.x) * (x - p.x) + 
                         (y - p.y) * (y - p.y) + 
                         (z - p.z) * (z - p.z) );
    }

    /**
    * @brief Angle  Angle formed with two other Point objects
    * @param pa  Reference to an existing point object
    * @param pb  Reference to an existing point object
    * @return double representing the Angle formed with the two Points in radians
    */
     double Angle (Point &pa,  Point &pb) const {
        double p_pa = Distance(pa);
        double p_pb = Distance(pb);
        double pa_pb = (pa-pb).Norm();
        return std::acos((p_pa*p_pa + p_pb*p_pb - pa_pb*pa_pb) / 
                         (2*p_pa*p_pb));
    }

    /**
     * @brief Normalize  Normalizes the point dividing it by its norm
     * @return normalized point
     */
    Point Normalize() const {
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
