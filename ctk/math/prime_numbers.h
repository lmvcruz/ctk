#pragma once

#include <vector>
#include <cmath>

namespace ctk {

template<class T>
/**
 * @brief CountPrimeNumbersBf Count the prime numbers before a passed limit
 * @param n count limit
 * @return number of primes befor n
 */
T CountPrimeNumbersBf(T n) {
    T count = 0;
    for (T i=2; i<n; i++) {
        bool isPrime = true;
        for (int j=2; j<i; j++) {
            if (i%j==0) {
                isPrime = false;
                break;
            }
        }
        if (isPrime) count++;
    }
    return count;
}

template<class T>
/**
 * @brief CountPrimeNumbersEs
 * @param n
 * @return
 */
T CountPrimeNumbersEs(T n) {
    std::vector<bool> sieve;
    sieve.resize(n+1, true);
    sieve[0] = sieve[1] = false;
    T p = 2;
    T count = 0;
    T bk = static_cast<T>(sqrt(n))+1;
    do {
        count++;
        sieve[p] = true;
        for (auto i=p; i<n; i+=p) sieve[i] = false;
        T init = p+1;
        p = n+1;
        for (auto i=init; i<sieve.size(); i++) {
            if (sieve[i]) {
                p = i;
                break;
            }
        }
    } while(p<bk);
    //
    for (auto i=p; i<n; i++) {
        if (sieve[i]) count++;
    }
    return count;
}

int CountPrimeNumbersBf(int n);
unsigned int CountPrimeNumbersBf(unsigned int n);
long CountPrimeNumbersBf(long n);
unsigned long CountPrimeNumbersBf(unsigned long n);
long long CountPrimeNumbersBf(long long n);
unsigned long long CountPrimeNumbersBf(unsigned long long n);

int CountPrimeNumbers(int n);
unsigned int CountPrimeNumbers(unsigned int n);
long CountPrimeNumbers(long n);
unsigned long CountPrimeNumbers(unsigned long n);
long long CountPrimeNumbers(long long n);
unsigned long long CountPrimeNumbers(unsigned long long n);

template<class T>
/**
 * @brief GeneratePrimeNumbersBf Get the prime numbers before a passed limit
 * @param n  limit
 * @return vector with all prime numbers before n
 */
std::vector<T> GeneratePrimeNumbersBf(T n) {
    std::vector<T> primes;
    for (int i=2; i<n; i++) {
        bool isPrime = true;
        for (int j=2; j<i; j++) {
            if (i%j==0) {
                isPrime = false;
                break;
            }
        }
        if (isPrime) {
            primes.push_back(i);
        }
    }
    return primes;
}

template<class T>
std::vector<T> GeneratePrimeNumbersEs(T n) {
    std::vector<bool> sieve;
    sieve.resize(n+1, true);
    sieve[0] = sieve[1] = false;
    T p = 2;
    T count = 0;
    T bk = static_cast<T>(sqrt(n))+1;
    std::vector<T> primes;
    do {
        count++;
        sieve[p] = true;
        primes.push_back(p);
        for (auto i=p; i<n; i+=p) sieve[i] = false;
        T init = p+1;
        p = n+1;
        for (auto i=init; i<sieve.size(); i++) {
            if (sieve[i]) {
                p = i;
                break;
            }
        }
    } while(p<bk);
    //
    for (auto i=p; i<n; i++) {
        if (sieve[i]) primes.push_back(i);
    }
    return primes;
}

/**
 * @brief GeneratePrimeNumbersBf
 * @param n
 * @return
 */
std::vector<int> GeneratePrimeNumbersBf(int n);

/**
 * @brief GeneratePrimeNumbersBf
 * @param n
 * @return
 */
std::vector<unsigned int> GeneratePrimeNumbersBf(unsigned int n);

/**
 * @brief GeneratePrimeNumbersBf
 * @param n
 * @return
 */
std::vector<long> GeneratePrimeNumbersBf(long n);

/**
 * @brief GeneratePrimeNumbersBf
 * @param n
 * @return
 */
std::vector<unsigned long> GeneratePrimeNumbersBf(unsigned long n);

/**
 * @brief GeneratePrimeNumbersBf
 * @param n
 * @return
 */
std::vector<long long> GeneratePrimeNumbersBf(long long n);

/**
 * @brief GeneratePrimeNumbersBf
 * @param n
 * @return
 */
std::vector<unsigned long long> GeneratePrimeNumbersBf(unsigned long long n);


/**
 * @brief GeneratePrimeNumbers
 * @param n
 * @return
 */
std::vector<int> GeneratePrimeNumbers(int n);

/**
 * @brief GeneratePrimeNumbers
 * @param n
 * @return
 */
std::vector<unsigned int> GeneratePrimeNumbers(unsigned int n);

/**
 * @brief GeneratePrimeNumbers
 * @param n
 * @return
 */
std::vector<long> GeneratePrimeNumbers(long n);

/**
 * @brief GeneratePrimeNumbers
 * @param n
 * @return
 */
std::vector<unsigned long> GeneratePrimeNumbers(unsigned long n);

/**
 * @brief GeneratePrimeNumbers
 * @param n
 * @return
 */
std::vector<long long> GeneratePrimeNumbers(long long n);

/**
 * @brief GeneratePrimeNumbers
 * @param n
 * @return
 */
std::vector<unsigned long long> GeneratePrimeNumbers(unsigned long long n);

};
