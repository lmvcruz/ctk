#ifndef CGVECTORAUX_H
#define CGVECTORAUX_H

#include <vector>
#include <iostream>
#include <string>

template<class T>
void show(std::vector<T> &vec, std::string sep=" ") {
    for (auto &v: vec) std::cout << v << sep;
    std::cout << std::endl;
}

#endif // CGVECTORAUX_H
