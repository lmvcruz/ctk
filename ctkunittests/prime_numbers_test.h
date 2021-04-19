#pragma once

#include "gtest/gtest.h"

#include <vector>

class CtkMathTest : public ::testing::Test {
public:
    const std::vector<int> some_primes_i = {2, 3, 5, 7, 11, 13, 17, 19, 
                        23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 
                        73, 79, 83, 89, 97};
    const std::vector<unsigned int> some_primes_ui = {2, 3, 5, 7, 11, 13, 
                        17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 
                        67, 71, 73, 79, 83, 89, 97};
    const std::vector<long> some_primes_l = {2, 3, 5, 7, 11, 13, 17, 19, 
                        23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 
                        73, 79, 83, 89, 97};
    const std::vector<unsigned long> some_primes_ul = {2, 3, 5, 7, 11, 13, 
                        17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 
                        67, 71, 73, 79, 83, 89, 97};
    const std::vector<long long> some_primes_ll = {2, 3, 5, 7, 11, 13, 17, 
                        19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 
                        71, 73, 79, 83, 89, 97};
    const std::vector<unsigned long long> some_primes_ull = {2, 3, 5, 7, 
                        11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 
                        59, 61, 67, 71, 73, 79, 83, 89, 97};
};
