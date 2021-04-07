#include "ctk/math/prime_numbers.h"

namespace ctk {

int countPrimeNumbersBf(int n) {
    return countPrimeNumbersBf<int>(n);
}

unsigned int countPrimeNumbersBf(unsigned int n) {
    return countPrimeNumbersBf<unsigned int>(n);
}

long countPrimeNumbersBf(long n) {
    return countPrimeNumbersBf<long>(n);
}

unsigned long countPrimeNumbersBf(unsigned long n) {
    return countPrimeNumbersBf<unsigned long>(n);
}

long long countPrimeNumbersBf(long long n) {
    return countPrimeNumbersBf<long long>(n);
}

unsigned long long countPrimeNumbersBf(unsigned long long n) {
    return countPrimeNumbersBf<unsigned long long>(n);
}

int countPrimeNumbers(int n) {
    return countPrimeNumbersEs<int>(n);
}

unsigned int countPrimeNumbers(unsigned int n) {
    return countPrimeNumbersEs<unsigned int>(n);
}

long countPrimeNumbers(long n) {
    return countPrimeNumbersEs<long>(n);
}

unsigned long countPrimeNumbers(unsigned long n) {
    return countPrimeNumbersEs<unsigned long>(n);
}

long long countPrimeNumbers(long long n) {
    return countPrimeNumbersEs<long long>(n);
}

unsigned long long countPrimeNumbers(unsigned long long n) {
    return countPrimeNumbersEs<unsigned long long>(n);
}

std::vector<int> generatePrimeNumbersBf(int n) {
    return generatePrimeNumbersBf<int>(n);
}

std::vector<unsigned int> generatePrimeNumbersBf(unsigned int n) {
    return generatePrimeNumbersBf<unsigned int>(n);
}

std::vector<long> generatePrimeNumbersBf(long n) {
    return generatePrimeNumbersBf<long>(n);
}

std::vector<unsigned long> generatePrimeNumbersBf(unsigned long n) {
    return generatePrimeNumbersBf<unsigned long>(n);
}

std::vector<long long> generatePrimeNumbersBf(long long n) {
    return generatePrimeNumbersBf<long long>(n);
}

std::vector<unsigned long long> generatePrimeNumbersBf(unsigned long long n) {
    return generatePrimeNumbersBf<unsigned long long>(n);
}

std::vector<int> generatePrimeNumbers(int n) {
    return generatePrimeNumbersEs<int>(n);
}

std::vector<unsigned int> generatePrimeNumbers(unsigned int n) {
    return generatePrimeNumbersEs<unsigned int>(n);
}

std::vector<long> generatePrimeNumbers(long n) {
    return generatePrimeNumbersEs<long>(n);
}

std::vector<unsigned long> generatePrimeNumbers(unsigned long n) {
    return generatePrimeNumbersEs<unsigned long>(n);
}

std::vector<long long> generatePrimeNumbers(long long n) {
    return generatePrimeNumbersEs<long long>(n);
}

std::vector<unsigned long long> generatePrimeNumbers(unsigned long long n) {
    return generatePrimeNumbersEs<unsigned long long>(n);
}

}
