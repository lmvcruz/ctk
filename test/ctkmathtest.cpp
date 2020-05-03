#include "ctkmathtest.h"

#include "ctkmath.h"
#include "ctkvectoraux.h"

void CgMathTest::SetUp()
{
    some_primes_i = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43,
                     47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
    some_primes_ui = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43,
                      47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
    some_primes_l = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43,
                     47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
    some_primes_ul = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43,
                      47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
    some_primes_ll = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43,
                      47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
    some_primes_ull = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43,
                       47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
}

TEST_F(CgMathTest, CgMathTestSetup) {
    EXPECT_EQ(CgMathTest::some_primes_i.size(), 25);
    EXPECT_EQ(CgMathTest::some_primes_ui.size(), 25);
    EXPECT_EQ(CgMathTest::some_primes_l.size(), 25);
    EXPECT_EQ(CgMathTest::some_primes_ul.size(), 25);
    EXPECT_EQ(CgMathTest::some_primes_ll.size(), 25);
    EXPECT_EQ(CgMathTest::some_primes_ull.size(), 25);
}

TEST_F(CgMathTest, CgMathTestCoutingPrimes) {
    int i = 100;
    unsigned int ui = 100;
    long l = 100;
    unsigned long ul = 100;
    long long ll = 100;
    unsigned long long ull = 100;
    EXPECT_EQ(ctk::countPrimeNumbersBf(i), 25);
    EXPECT_EQ(ctk::countPrimeNumbersBf(ui), 25);
    EXPECT_EQ(ctk::countPrimeNumbersBf(l), 25);
    EXPECT_EQ(ctk::countPrimeNumbersBf(ul), 25);
    EXPECT_EQ(ctk::countPrimeNumbersBf(ll), 25);
    EXPECT_EQ(ctk::countPrimeNumbersBf(ull), 25);
    //
    EXPECT_EQ(ctk::countPrimeNumbers(i), 25);
    EXPECT_EQ(ctk::countPrimeNumbers(ui), 25);
    EXPECT_EQ(ctk::countPrimeNumbers(l), 25);
    EXPECT_EQ(ctk::countPrimeNumbers(ul), 25);
    EXPECT_EQ(ctk::countPrimeNumbers(ll), 25);
    EXPECT_EQ(ctk::countPrimeNumbers(ull), 25);
}

TEST_F(CgMathTest, CgMathTestListingPrimes) {
    int i = 100;
    unsigned int ui = 100;
    long l = 100;
    unsigned long ul = 100;
    long long ll = 100;
    unsigned long long ull = 100;
    EXPECT_EQ(ctk::generatePrimeNumbersBf(i), some_primes_i);
    EXPECT_EQ(ctk::generatePrimeNumbersBf(ui), some_primes_ui);
    EXPECT_EQ(ctk::generatePrimeNumbersBf(l), some_primes_l);
    EXPECT_EQ(ctk::generatePrimeNumbersBf(ul), some_primes_ul);
    EXPECT_EQ(ctk::generatePrimeNumbersBf(ll), some_primes_ll);
    EXPECT_EQ(ctk::generatePrimeNumbersBf(ull), some_primes_ull);
    //
    EXPECT_EQ(ctk::generatePrimeNumbers(i), some_primes_i);
    EXPECT_EQ(ctk::generatePrimeNumbers(ui), some_primes_ui);
    EXPECT_EQ(ctk::generatePrimeNumbers(l), some_primes_l);
    EXPECT_EQ(ctk::generatePrimeNumbers(ul), some_primes_ul);
    EXPECT_EQ(ctk::generatePrimeNumbers(ll), some_primes_ll);
    EXPECT_EQ(ctk::generatePrimeNumbers(ull), some_primes_ull);
}
