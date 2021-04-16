#pragma once

#include <string>

#include "ctk/matrix/abstract_matrix.h"

namespace ctk {

class NumericMatrix : public AbstractMatrix<double> {
public:
    NumericMatrix();
    NumericMatrix(const NumericMatrix& that);
    NumericMatrix(cv::Mat& d);
    NumericMatrix(int w, int h, std::vector<double>& d);

    NumericMatrix& operator=(const NumericMatrix& that);

    using AbstractMatrix<double>::Create;
    virtual void Create(int w, int h, std::vector<int> &vec);

    void Open(std::string filename);
    void Save(std::string filename);
    void Show();

    NumericMatrix operator+(const NumericMatrix &that);
    void operator+=(const NumericMatrix &that);

    NumericMatrix operator-(const NumericMatrix &that);
    void operator-=(const NumericMatrix &that);

    NumericMatrix operator*(const NumericMatrix &that);
    void operator*=(const NumericMatrix &that);

    NumericMatrix operator/(const NumericMatrix &that);
    void operator/=(const NumericMatrix &that);

    NumericMatrix operator+(const double v);
    void operator+=(const double v);

    NumericMatrix operator-(const double v);
    void operator-=(const double v);

    NumericMatrix operator*(const double v);
    void operator*=(const double v);

    NumericMatrix operator/(const double v);
    void operator/=(const double v);

    double Determinant();

    NumericMatrix Invert();
    void SelfInvert();

    NumericMatrix Transpose();
    void SelfTranspose();
};

}
