#include <iostream>
#include <limits>

#include "ctk/matrix/numeric_matrix.h"

void show(const ctk::NumericMatrix& mat) {
    for (auto y = 0; y < mat.GetRows(); ++y) { 
        for (auto x = 0; x < mat.GetCols(); ++ x) {
            std::cout << mat.Get(x, y) << "\t";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void gauss_forward_elimination(ctk::NumericMatrix& mat) {
    // This dimension should be the matrix rank
    int max_dim = std::min(mat.GetRows(), mat.GetCols());
    double epsilon = std::numeric_limits<double>::epsilon() * 100;
    for (int pivot = 0; pivot < mat.GetRows(); ++pivot) {
        auto scale = mat.Get(pivot, pivot);
        if (std::fabs(scale) < epsilon) continue;
        for (int x = pivot; x < mat.GetCols(); ++x) {
                mat.Set(x, pivot, mat.Get(x, pivot) / scale);
            }
        for (int y = pivot+1; y < mat.GetRows(); ++y) {
            if (std::fabs(mat.Get(pivot, y)) < epsilon) {
                continue;
            }
            auto scale = mat.Get(pivot, pivot) / mat.Get(pivot, y);
            for (int x = pivot; x < mat.GetCols(); ++x) {
                mat.Set(x, y, mat.Get(x, y) * scale - mat.Get(x, pivot));
            }
        }
        show(mat);
    }
}

void backward_elimination(ctk::NumericMatrix& mat) {
    assert(mat.GetRows() > 1 and mat.GetRows() + 1 == mat.GetCols());
    int last = mat.GetCols() - 1;
    for (int pivot = mat.GetRows() - 1; pivot >= 0; --pivot) {
        for (int y = pivot-1; y >= 0; --y) {
            double b_at_y = last - (mat.Get(last, pivot) * mat.Get(pivot, y));
            mat.Set(last, y, b_at_y);
            mat.Set(pivot, y, 0);
        }
        show(mat);
    }
}

int main(int argc, char *argv[]) {
    std::vector<double> data = {
        1, 2, 3, 
        4, 5, 6
    };
    ctk::NumericMatrix mat;
    mat.Create(3, 2, data);
    gauss_forward_elimination(mat);
    backward_elimination(mat);
    return 0;
}
