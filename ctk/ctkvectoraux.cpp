#include "ctkvectoraux.h"

#include <random>

namespace ctk {

std::vector<int> RangeVector(int i, int e)
{
    std::vector<int> v;
    v.resize(std::abs(e-i)+1);
    if (i<e)
        std::generate(v.begin(), v.end(), [n = i] () mutable { return n++; });
    else
        std::generate(v.begin(), v.end(), [n = i] () mutable { return n--; });
    return v;
}

void Shuffle(std::vector<int> &vec)
{
    std::random_device rng;
    std::mt19937 urng(rng());
    std::shuffle(vec.begin(), vec.end(), urng);
}

void Shuffle(std::vector<int> &vec, int s)
{
    std::mt19937 urng(s);
    std::shuffle(vec.begin(), vec.end(), urng);
}

}
