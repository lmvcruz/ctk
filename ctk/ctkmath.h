#pragma once

#include <vector>
#include <cmath>

namespace ctk {

template<class T>
/**
 * @brief countPrimeNumbersBf Count the prime numbers before a passed limit
 * @param n count limit
 * @return number of primes befor n
 */
T countPrimeNumbersBf(T n) {
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
 * @brief countPrimeNumbersEs
 * @param n
 * @return
 */
T countPrimeNumbersEs(T n) {
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

int countPrimeNumbersBf(int n);
unsigned int countPrimeNumbersBf(unsigned int n);
long countPrimeNumbersBf(long n);
unsigned long countPrimeNumbersBf(unsigned long n);
long long countPrimeNumbersBf(long long n);
unsigned long long countPrimeNumbersBf(unsigned long long n);

int countPrimeNumbers(int n);
unsigned int countPrimeNumbers(unsigned int n);
long countPrimeNumbers(long n);
unsigned long countPrimeNumbers(unsigned long n);
long long countPrimeNumbers(long long n);
unsigned long long countPrimeNumbers(unsigned long long n);

template<class T>
/**
 * @brief generatePrimeNumbersBf Get the prime numbers before a passed limit
 * @param n  limit
 * @return vector with all prime numbers before n
 */
std::vector<T> generatePrimeNumbersBf(T n) {
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
std::vector<T> generatePrimeNumbersEs(T n) {
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
 * @brief generatePrimeNumbersBf
 * @param n
 * @return
 */
std::vector<int> generatePrimeNumbersBf(int n);

/**
 * @brief generatePrimeNumbersBf
 * @param n
 * @return
 */
std::vector<unsigned int> generatePrimeNumbersBf(unsigned int n);

/**
 * @brief generatePrimeNumbersBf
 * @param n
 * @return
 */
std::vector<long> generatePrimeNumbersBf(long n);

/**
 * @brief generatePrimeNumbersBf
 * @param n
 * @return
 */
std::vector<unsigned long> generatePrimeNumbersBf(unsigned long n);

/**
 * @brief generatePrimeNumbersBf
 * @param n
 * @return
 */
std::vector<long long> generatePrimeNumbersBf(long long n);

/**
 * @brief generatePrimeNumbersBf
 * @param n
 * @return
 */
std::vector<unsigned long long> generatePrimeNumbersBf(unsigned long long n);


/**
 * @brief generatePrimeNumbers
 * @param n
 * @return
 */
std::vector<int> generatePrimeNumbers(int n);

/**
 * @brief generatePrimeNumbers
 * @param n
 * @return
 */
std::vector<unsigned int> generatePrimeNumbers(unsigned int n);

/**
 * @brief generatePrimeNumbers
 * @param n
 * @return
 */
std::vector<long> generatePrimeNumbers(long n);

/**
 * @brief generatePrimeNumbers
 * @param n
 * @return
 */
std::vector<unsigned long> generatePrimeNumbers(unsigned long n);

/**
 * @brief generatePrimeNumbers
 * @param n
 * @return
 */
std::vector<long long> generatePrimeNumbers(long long n);

/**
 * @brief generatePrimeNumbers
 * @param n
 * @return
 */
std::vector<unsigned long long> generatePrimeNumbers(unsigned long long n);

};
