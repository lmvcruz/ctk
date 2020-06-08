#ifndef BINARYMATRIX_H
#define BINARYMATRIX_H

#include <string>

#include "opencv2/imgproc.hpp"

#include "ctkabstractmatrix.h"

namespace ctk {

class BinaryMatrix : public AbstractMatrix<bool>
{
public:
    BinaryMatrix();
    BinaryMatrix(const BinaryMatrix& that);
    BinaryMatrix(const AbstractMatrix<bool>& that);
    BinaryMatrix(cv::Mat& d);
    BinaryMatrix(int w, int h, std::vector<bool>& d);

    BinaryMatrix &operator=(const BinaryMatrix& that);

    void set(int x, int y, bool v);
    bool get(int x, int y);

    BinaryMatrix Not();
    BinaryMatrix And(BinaryMatrix& that);
    BinaryMatrix Or(BinaryMatrix& that);
    BinaryMatrix Xor(BinaryMatrix& that);

    //TODO: Implement Self methods

    int countTrues();
    int countFalses();

    //TODO: test and benchmark these methods;
    //TODO: replace type by an internal enum
    BinaryMatrix Erode(int size, int etype=cv::MORPH_RECT);
    void SelfErode(int size, int etype=cv::MORPH_RECT);
    BinaryMatrix Dilate(int size, int etype=cv::MORPH_RECT);
    void SelfDilate(int size, int etype=cv::MORPH_RECT);

    void Open(std::string filename);
    void Save(std::string filename);
    void Show();

};

};

#endif // BINARYMATRIX_H
