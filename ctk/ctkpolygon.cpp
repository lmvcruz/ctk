#include "ctkpolygon.h"

#include "opencv2/imgproc.hpp"

namespace ctk {

Polygon::Polygon()
{
}

Polygon::Polygon(const Polygon &that)
{
    data_ = that.data_;
    cvdata_ = that.cvdata_;
}

Polygon::Polygon(std::vector<PointD> &d)
{
    data_ = d;
    cvdata_.resize(d.size());
    for (auto i=0; i<d.size(); i++) {
        cvdata_[i].x = d[i].getX();
        cvdata_[i].y = d[i].getY();
    }
}

Polygon::Polygon(std::vector<cv::Point> &cvd)
{
    cvdata_ = cvd;
    data_.resize(cvd.size());
    for (auto i=0; i<cvd.size(); i++) {
        data_[i].setX(cvd[i].x);
        data_[i].setX(cvd[i].x);
    }
}

Polygon::~Polygon()
{
    data_.clear();
    cvdata_.clear();
}

Polygon &Polygon::operator=(const Polygon &that)
{
    data_ = that.data_;
    cvdata_ = that.cvdata_;
    return *this;
}

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

Polygon &Polygon::operator=(std::vector<cv::Point> &cvd)
{
    cvdata_ = cvd;
    data_.resize(cvd.size());
    for (auto i=0; i<cvd.size(); i++) {
        data_[i].setX(cvd[i].x);
        data_[i].setX(cvd[i].x);
    }
    return *this;
}

void Polygon::add_point(PointD &pt)
{
    data_.push_back(pt);
    cvdata_.push_back(cv::Point(pt.getX(), pt.getY()));
}

void Polygon::add_point(double x, double y)
{
    data_.push_back(PointD(x,y));
    cvdata_.push_back(cv::Point(x, y));
}

void Polygon::set_point(int idx, PointD &pt)
{
    data_[idx] = pt;
    cvdata_[idx] = cv::Point(pt.getX(), pt.getY());
}

void Polygon::set_point(int idx, double x, double y)
{
    data_[idx] = PointD(x,y);
    cvdata_[idx] = cv::Point(x,y);
}

PointD &Polygon::point(int i)
{
    return data_[i];
}

void Polygon::Resize(int s)
{
    data_.resize(s);
    cvdata_.resize(s);
}

int Polygon::size()
{
    return data_.size();
}

double Polygon::Area()
{
    return contourArea(cvdata_);
}

double Polygon::Perimeter()
{
    return arcLength(cvdata_, true);
}

Polygon Polygon::Reduce(int epsilon)
{
    Polygon new_poly;
    approxPolyDP(cv::Mat(cvdata_), new_poly.cvdata_, epsilon, true);
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

Polygon Polygon::Shift(int sh)
{
    Polygon new_poly(*this);
    std::rotate(new_poly.data_.begin(), new_poly.data_.begin()+sh, new_poly.data_.end());
    std::rotate(new_poly.cvdata_.begin(), new_poly.cvdata_.begin()+sh, new_poly.cvdata_.end());
    return new_poly;
}

void Polygon::SelfShift(int sh)
{
    std::rotate(data_.begin(), data_.begin()+sh, data_.end());
    std::rotate(cvdata_.begin(), cvdata_.begin()+sh, cvdata_.end());
}

}
