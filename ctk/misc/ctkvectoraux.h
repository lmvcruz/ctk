#ifndef CGVECTORAUX_H
#define CGVECTORAUX_H

#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "ctk/core/exceptions.h"
#include "ctk/geometry/point.h"

namespace ctk {

/**
 * TODO
 */
template<class T>
/**
 * @brief Distance  Distance between two vectors
 * @param vec1 vector 1
 * @param vec2 vector 2
 * @return double representing the distance between vectors 1 and 2
 */
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
/**
 * @brief show  print vector content
 * @param vec  vector to print
 * @param sep  delimiter to print between elements
 */
void show(std::vector<T> &vec, std::string sep=" ") {
    for (auto &v: vec) std::cout << v << sep;
    std::cout << std::endl;
}

std::vector<int> RangeVector(int i, int e);
std::vector<int> RangeVector(int e);
std::vector<unsigned int> RangeVectorUi(unsigned int i, unsigned int e);
std::vector<unsigned int> RangeVectorUi(unsigned int e);
std::vector<int> generateUniqueRandomNumbs(int n, int s, int e);
std::vector<PointI> getScanOrderVector(unsigned int w, unsigned int h);
std::vector<PointI> getScanOrderVector(PointI &origin, unsigned int w, unsigned int h);
std::vector<PointI> getSnakeOrderVector(unsigned int w, unsigned int h);
std::vector<PointI> getSnakeOrderVector(PointI &origin, unsigned int w, unsigned int h);
std::vector<PointI> getSpiralOrderVector(unsigned int w, unsigned int h);
std::vector<PointI> getSpiralOrderVector(PointI &origin, unsigned int w, unsigned int h);
std::vector<PointI> getSnailOrderVector(unsigned int w, unsigned int h);
std::vector<PointI> getSnailOrderVector(PointI &origin, unsigned int w, unsigned int h);



template<class T>
/**
 * @brief Shuffle  Randomize the order of the elements in a vector
 * @param vec vector
 */
void Shuffle(std::vector<T> &vec)
{
    std::random_device rng;
    std::mt19937 urng(rng());
    std::shuffle(vec.begin(), vec.end(), urng);
}

template<class T>
/**
 * @brief Shuffle?
 * @param vec
 * @param s
 */
void Shuffle(std::vector<T> &vec, unsigned int s)
{
    std::mt19937 urng(s);
    std::shuffle(vec.begin(), vec.end(), urng);
}

}

#endif // CGVECTORAUX_H
