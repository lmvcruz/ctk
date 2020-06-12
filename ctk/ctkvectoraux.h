#ifndef CGVECTORAUX_H
#define CGVECTORAUX_H

#include <vector>
#include <iostream>
#include <string>
#include <cmath>
#include <random>

#include "ctkexceptions.h"

namespace ctk {

/**
 * TODO
 */
template<class T>
double Distance(std::vector<T> &vec1, std::vector<T> &vec2)
{
    if(vec1.size()!=vec2.size()) throw  incompatible_parameters();
    //
    double dist = 0.0;
    for (auto i=0; i<vec1.size(); i++) {
        double d = vec1[i] - vec2[d];
        dist += d*d;
    }
    return std::sqrt(dist);
}

template<class T>
void show(std::vector<T> &vec, std::string sep=" ") {
    for (auto &v: vec) std::cout << v << sep;
    std::cout << std::endl;
}

std::vector<int> RangeVector(int i, int e);
std::vector<unsigned int> RangeVectorUi(unsigned int i, unsigned int e);

template<class T>
void Shuffle(std::vector<T> &vec)
{
    std::random_device rng;
    std::mt19937 urng(rng());
    std::shuffle(vec.begin(), vec.end(), urng);
}

template<class T>
void Shuffle(std::vector<T> &vec, unsigned int s)
{
    std::mt19937 urng(s);
    std::shuffle(vec.begin(), vec.end(), urng);
}

}

#endif // CGVECTORAUX_H
