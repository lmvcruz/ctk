#include "ctk/math/byte_numbers.h"

#include <algorithm>

namespace ctk {

int CountBits(int num) {
    int numberOfBits = 0;
    while (num>0) {
        numberOfBits += num & 1;
        num >>= 1;
    }
    return numberOfBits;
}

std::vector<int> int2bits(int num) {
    std::vector<int> bits;
    while (num>0) {
        bits.push_back(num & 1);
        num >>= 1;
    }
    std::reverse(bits.begin(), bits.end());
    return bits;
}

int bits2int(std::vector<int> bits) {
    int num = 0;
    int base = 1;
    for (auto i=bits.size()-1; i>=0; --i) {
        num += bits[i] * base;
        base <<= 1;
    }
    return num;
}

};