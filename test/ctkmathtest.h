#ifndef CGMATHTEST_H
#define CGMATHTEST_H

#include "gtest/gtest.h"

#include <vector>

class CgMathTest : public ::testing::Test {
public:
    void SetUp() override;

    std::vector<int> some_primes_i;
    std::vector<unsigned int> some_primes_ui;
    std::vector<long> some_primes_l;
    std::vector<unsigned long> some_primes_ul;
    std::vector<long long> some_primes_ll;
    std::vector<unsigned long long> some_primes_ull;
};

#endif // CGMATHTEST_H
