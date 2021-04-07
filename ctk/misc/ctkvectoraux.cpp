#include "ctkvectoraux.h"

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
    if (i < e)
        std::generate(v.begin(), v.end(), [n = i] () mutable { return n++; });
    else
        std::generate(v.begin(), v.end(), [n = i] () mutable { return n--; });
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

std::vector<PointI> getScanOrderVector(unsigned int w, unsigned int h)
{
    std::vector<PointI> indices;
    indices.resize(w*h);
    for (unsigned int y=0; y<h; y++) {
        for (unsigned int x=0; x<w; x++) {
            indices[y*w+x] = PointI(static_cast<int>(x),static_cast<int>(y));
        }
    }
    return indices;
}

std::vector<PointI> getScanOrderVector(PointI &origin,
                                            unsigned int w, unsigned int h)
{
    std::vector<PointI> indices;
    indices.resize(w*h);
    for (unsigned int y=0; y<h; y++) {
        for (unsigned int x=0; x<w; x++) {
            indices[y*w+x] = PointI( origin.getX() + static_cast<int>(x),
                                          origin.getY() + static_cast<int>(y));
        }
    }
    return indices;
}

std::vector<PointI> getSnakeOrderVector(unsigned int w, unsigned int h)
{
    std::vector<PointI> indices;
    indices.resize(w*h);
    for (unsigned int y=0; y<h; y++) {
        for (unsigned int x=0; x<w; x++) {
            indices[y*w+x] = PointI(static_cast<int>(x),static_cast<int>(y));
        }
        y++;
        if (y<h) {
            for (unsigned int x=0; x<w; x++) {
                indices[y*w+x] = PointI( static_cast<int>(w-1-x),
                                              static_cast<int>(y));
            }
        }
    }
    return indices;
}

std::vector<PointI> getSnakeOrderVector(PointI &origin,
                                             unsigned int w, unsigned int h)
{    std::vector<PointI> indices;
     indices.resize(w*h);
      for (unsigned int y=0; y<h; y++) {
          for (unsigned int x=0; x<w; x++) {
              indices[y*w+x] = PointI(static_cast<int>(x),static_cast<int>(y));
          }
          y++;
          if (y<h) {
              for (unsigned int x=0; x<w; x++) {
                  indices[y*w+x] = PointI( origin.getX() + static_cast<int>(w-1-x),
                                                origin.getY() + static_cast<int>(y));
              }
          }
      }
       return indices;
}

std::vector<PointI> getSpiralOrderVector(unsigned int w, unsigned int h)
{
    std::vector<PointI> indices;
    indices.resize(w*h);
    unsigned int ptIndex = 0;
    for (unsigned int i=0; ptIndex<w*h; i++) {
        int layer = static_cast<int>( std::floor(std::sqrt(float(i))) );
        int indexInLayer = static_cast<int>(i) - layer * (layer + 1);
        unsigned int x = static_cast<unsigned int>(layer + std::min(indexInLayer, 0));
        unsigned int y = static_cast<unsigned int>(layer - std::max(indexInLayer, 0));
        if (layer % 2 == 0) {
            unsigned int tmp = y;
            y = x;
            x = tmp;
        }
        if (x>=w || y>=h) {
            continue;
        }
        indices[ptIndex] = PointI(static_cast<int>(x),static_cast<int>(y));
        ptIndex++;
    }
    return indices;
}

std::vector<PointI> getSpiralOrderVector(PointI &origin,
                                              unsigned int w, unsigned int h)
{
    std::vector<PointI> indices;
    indices.resize(w*h);
    unsigned int ptIndex = 0;
    for (unsigned int i=0; ptIndex<w*h; i++) {
        int layer = static_cast<int>( std::floor(std::sqrt(float(i))) );
        int indexInLayer = static_cast<int>(i) - layer * (layer + 1);
        unsigned int x = static_cast<unsigned int>(layer + std::min(indexInLayer, 0));
        unsigned int y = static_cast<unsigned int>(layer - std::max(indexInLayer, 0));
        if (layer % 2 == 0) {
            unsigned int tmp = y;
            y = x;
            x = tmp;
        }
        if (x>=w || y>=h) {
            continue;
        }
        indices[ptIndex] = PointI( origin.getX() + static_cast<int>(x),
                                        origin.getY() + static_cast<int>(y));
        ptIndex++;
    }
    return indices;
}

std::vector<PointI> getSnailOrderVector(unsigned int w, unsigned int h)
{
    std::vector<PointI> indices;
    indices.resize(w*h);
    int r = 0;
    int c = -1;
    unsigned int nextturn = w;
    unsigned int stepsx = w;
    unsigned int stepsy = h-1;
    int inc_c = 1;
    int inc_r = 0;
    int turns = 0;
    for (unsigned int i=0; i<w*h; i++) {
        c += inc_c;
        r += inc_r;
        indices[i] = PointI(c,r);
        if (i == nextturn-1) {
            turns += 1;
            if (turns%2==0) {
                nextturn += stepsx;
                stepsy -= 1;
            }
            else {
                nextturn += stepsy;
                stepsx -= 1;
            }
            int tmp = inc_c;
            inc_c = -inc_r;
            inc_r = tmp;
        }
    }
    return indices;
}
std::vector<PointI> getSnailOrderVector(PointI &origin,
                                             unsigned int w, unsigned int h)
{
    std::vector<PointI> indices;
    indices.resize(w*h);
    int r = 0;
    int c = -1;
    unsigned int nextturn = w;
    unsigned int stepsx = w;
    unsigned int stepsy = h-1;
    int inc_c = 1;
    int inc_r = 0;
    int turns = 0;
    for (unsigned int i=0; i<w*h; i++) {
        c += inc_c;
        r += inc_r;
        indices[i] = PointI(origin.getX() + c, origin.getY() + r);
        if (i == nextturn-1) {
            turns += 1;
            if (turns%2==0) {
                nextturn += stepsx;
                stepsy -= 1;
            }
            else {
                nextturn += stepsy;
                stepsx -= 1;
            }
            int tmp = inc_c;
            inc_c = -inc_r;
            inc_r = tmp;
        }
    }
    return indices;
}


}
