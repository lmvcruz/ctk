#ifndef CGVECTORAUX_H
#define CGVECTORAUX_H

#include <vector>
#include <iostream>
#include <string>
#include <cmath>
#include <random>

namespace ctk {

/**
 * TODO
 */
template<class T>
double Distance(std::vector<T> &vec1, std::vector<T> &vec2)
{
    //TODO: change it to throw an exception
    assert(vec1.size()==vec2.size());
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

//TODO: evaluate the possibility to use generic method (template)
//void Shuffle(std::vector<int> &vec);
//void Shuffle(std::vector<int> &vec, int s);

//void Shuffle(std::vector<unsigned int> &vec);

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
