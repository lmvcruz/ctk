#include "ctkvectoraux.h"

#include <random>

namespace ctk {
/**
 * @brief RangeVector  Creates a vector of sequential ints between two passed ints
 * @param i int representing the start of the range
 * @param e int representing the end of the range
 * @return vector of ints in the range between i and e
 */
std::vector<int> RangeVector(int i, int e) {
    std::vector<int> v;
    long lsize = std::abs(static_cast<long>(e) - static_cast<long>(i))+1;
    v.resize(static_cast<unsigned int>(lsize));
    if (i < e)
        std::generate(v.begin(), v.end(), [n = i] () mutable { return n++; });
    else
        std::generate(v.begin(), v.end(), [n = i] () mutable { return n--; });
    return v;
}

/**
 * @brief RangeVectorUi   Creates a vector of sequential unsigned ints between two passed ints
 * @param i unsigned int representing the start of the range
 * @param e unsigned int representing the end of the range
 * @return vector of unsigned ints in the range between i and e
 */
std::vector<unsigned int> RangeVectorUi(unsigned int i, unsigned int e) {
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
