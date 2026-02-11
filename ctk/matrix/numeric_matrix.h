#pragma once

#include <span>
#include <string>
#include <string_view>

#include "ctk/matrix/abstract_matrix.h"

namespace ctk {

class NumericMatrix : public AbstractMatrix<double> {
public:
    using AbstractMatrix<double>::Create;

    NumericMatrix();
    NumericMatrix(const NumericMatrix& that);
    NumericMatrix(const cv::Mat& d);
    NumericMatrix(int w, int h, const std::vector<double>& d);

    NumericMatrix& operator=(const NumericMatrix& that);

    void Create(int w, int h, std::span<const double> values) override;

    void Open(std::string_view filename) override;
    void Save(std::string_view filename) const override;
    void Show() const;

    NumericMatrix operator+(const NumericMatrix& that) const;
    void operator+=(const NumericMatrix& that);

    NumericMatrix operator-(const NumericMatrix& that) const;
    void operator-=(const NumericMatrix& that);

    NumericMatrix operator*(const NumericMatrix& that) const;
    void operator*=(const NumericMatrix& that);

    NumericMatrix operator/(const NumericMatrix& that) const;
    void operator/=(const NumericMatrix& that);

    NumericMatrix operator+(const double v) const;
    void operator+=(const double v);

    NumericMatrix operator-(const double v) const;
    void operator-=(const double v);

    NumericMatrix operator*(const double v) const;
    void operator*=(const double v);

    NumericMatrix operator/(const double v) const;
    void operator/=(const double v);

    double Determinant() const;

    NumericMatrix Invert() const;
    void SelfInvert();

    NumericMatrix Transpose() const;
    void SelfTranspose();
};

}  // namespace ctk
