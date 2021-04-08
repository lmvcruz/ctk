#pragma once

#include <vector>

#include "ctk/geometry/point.h"

namespace ctk {

std::vector<PointI> getScanOrderVector(unsigned int w, unsigned int h);
std::vector<PointI> getScanOrderVector(PointI &origin, unsigned int w, unsigned int h);
std::vector<PointI> getSnakeOrderVector(unsigned int w, unsigned int h);
std::vector<PointI> getSnakeOrderVector(PointI &origin, unsigned int w, unsigned int h);
std::vector<PointI> getSpiralOrderVector(unsigned int w, unsigned int h);
std::vector<PointI> getSpiralOrderVector(PointI &origin, unsigned int w, unsigned int h);
std::vector<PointI> getSnailOrderVector(unsigned int w, unsigned int h);
std::vector<PointI> getSnailOrderVector(PointI &origin, unsigned int w, unsigned int h);

}
