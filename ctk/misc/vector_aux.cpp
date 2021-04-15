#include "ctk/misc/vector_aux.h"

#include <algorithm>
#include <random>
#include <vector>

#include "ctk/geometry/point.h"

namespace ctk {
/**
 * @brief RangeVector  Creates a vector of sequential ints between two passed ints
 * @param i int representing the start of the range vector
 * @param e int representing the end of the range vector
 * @return vector of ints between i and e
 */
std::vector<int> RangeVector(int i, int e) {
    std::vector<int> v;
    long lsize = std::abs(static_cast<long>(e) - static_cast<long>(i))+1;
    v.resize(static_cast<unsigned int>(lsize));
    if (i < e) {
        std::generate(v.begin(), v.end(), [n = i] () mutable { return n++; });
    }
    else {
        std::generate(v.begin(), v.end(), [n = i] () mutable { return n--; });
    }
    return v;
}

/**
 * @brief RangeVector  Creates a vector of sequential ints between zero and the passed int
 * @param e  int representing the end of the range vector
 * @return vector of ints between 0 and e
 */
std::vector<int> RangeVector(int e) {
    std::vector<int> v = RangeVector(0, e);
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

/**
 * @brief RangeVectorUi  Creates a vector of sequential unsigned ints between zero and the passed int
 * @param e  unsigned int representing the end of the range vector
 * @return vector of unsigned ints between 0 and e
 */
std::vector<unsigned int> RangeVectorUi(unsigned int e) {
    std::vector<unsigned int> v = RangeVectorUi(0, e);
    return v;
}

/**
 * @brief generateUniqueRandomNumbs  Generates n unique random numbers between s and e
 * @param n  int representing the number of random numbers to be generated
 * @param s  int representing the start of the range
 * @param e  int representing the end of the range
 * @return vector of ints with size n containing unique random numbers between s and e
 */
std::vector<int> generateUniqueRandomNumbs(int n, int s, int e) {
    std::vector<int> numbers;
    for (int i =s; i<e; i++) {
        numbers.push_back(i);
    }
    std::random_shuffle(numbers.begin(), numbers.end());
    std::vector<int> random_numbers;
    for (int i = 0; i < n; i++) {
        random_numbers.push_back(numbers[i]);
    }
    return random_numbers;
}

}
