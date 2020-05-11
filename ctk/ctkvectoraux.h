#ifndef CGVECTORAUX_H
#define CGVECTORAUX_H

#include <vector>
#include <iostream>
#include <string>

/**
 * TODO
 */
template<class T>
void show(std::vector<T> &vec, std::string sep=" ") {
    for (auto &v: vec) std::cout << v << sep;
    std::cout << std::endl;
}

std::vector<int> RangeVector(int i, int e);

//TODO: evaluate the possibility to use generic method (template)
void Shuffle(std::vector<int> &vec);
void Shuffle(std::vector<int> &vec, int s);

#endif // CGVECTORAUX_H
