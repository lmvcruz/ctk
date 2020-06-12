#include "ctkvectoraux.h"

#include <random>

namespace ctk {

std::vector<int> RangeVector(int i, int e)
{
    std::vector<int> v;
    long lsize = std::abs(static_cast<long>(e)-static_cast<long>(i))+1;
    v.resize(static_cast<unsigned int>(lsize));
    if (i<e)
        std::generate(v.begin(), v.end(), [n = i] () mutable { return n++; });
    else
        std::generate(v.begin(), v.end(), [n = i] () mutable { return n--; });
    return v;
}

std::vector<unsigned int> RangeVectorUi(unsigned int i, unsigned int e)
{
    std::vector<unsigned int> v;
    long lsize = std::abs(static_cast<long>(e)-static_cast<long>(i))+1;
    v.resize(static_cast<unsigned int>(lsize));
    if (i<e)
        std::generate(v.begin(), v.end(), [n = i] () mutable { return n++; });
    else
        std::generate(v.begin(), v.end(), [n = i] () mutable { return n--; });
    return v;
}

}
