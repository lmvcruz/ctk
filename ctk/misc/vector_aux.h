#pragma once

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
    if (vec1.size() != vec2.size()) throw  incompatible_parameters();
    //
    double dist = 0.0;
    for (auto i = 0; i < vec1.size(); ++i) {
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

template<class T>
bool Contains(std::vector<T> &vec, T val) {
    return std::find(vec.begin(), vec.end(), val) != vec.end();
}

template<class T>
bool Contains(std::vector<T> &vec, const std::vector<T>& vals) {
    for (auto& v: vals) {
        if (not Contains(vec, v)) return false;
    }
    return true;
}

template<class T>
size_t IndexOf(std::vector<T> &vec, T val, size_t init=0) {
    auto it = std::find(vec.begin()+init, vec.end(), val);
    return std::distance(vec.begin(), it);;
}

template<class T>
std::vector<int> ContainsIndices(std::vector<T> &vec, const T val) {
    std::vector<int> indices;
    size_t pos = IndexOf(vec, val, 0);
    while (pos != vec.size()) {
        indices.push_back(pos);
        pos = IndexOf(vec, val, pos + 1);
    }
    return indices;
}

template<class T>
std::vector<int> ContainsIndices(std::vector<T> &vec, 
            const std::vector<T>& vals) {
    std::vector<int> indices;
    for (auto& val: vals) {
        auto newIndices = ContainsIndices(vec, val);
        indices.insert(indices.end(), newIndices.begin(), newIndices.end());
    }
    std::sort(indices.begin(), indices.end());
    return indices;
}
}
