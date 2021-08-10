#pragma once

#include <vector>

namespace ctk {

int CountBits(int num);
std::vector<int> int2bits(int num);
int bits2int(std::vector<int> bits);

};