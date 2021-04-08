#include "ctk/misc/spatial_ordering.h"

namespace ctk {
    
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
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            indices[y*w+x] = PointI(static_cast<int>(x),static_cast<int>(y));
        }
        y++;
        if (y < h) {
            for (int x = 0; x < w; x++) {
                indices[y*w+x] = PointI(static_cast<int>(w-1-x),
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