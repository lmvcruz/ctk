#include "prime_numbers_test.h"

#include "ctk/math/prime_numbers.h"
#include "ctk/misc/vector_aux.h"

#include "test_setup.h"

#ifdef TEST_PRIME_NUMBERS
TEST_F(CtkMathTest, Test_Setup) {
    EXPECT_EQ(CtkMathTest::some_primes_i.size(), 25);
    EXPECT_EQ(CtkMathTest::some_primes_ui.size(), 25);
    EXPECT_EQ(CtkMathTest::some_primes_l.size(), 25);
    EXPECT_EQ(CtkMathTest::some_primes_ul.size(), 25);
    EXPECT_EQ(CtkMathTest::some_primes_ll.size(), 25);
    EXPECT_EQ(CtkMathTest::some_primes_ull.size(), 25);
}

TEST_F(CtkMathTest, Test_CoutingPrimes) {
    int i = 100;
    unsigned int ui = 100;
    long l = 100;
    unsigned long ul = 100;
    long long ll = 100;
    unsigned long long ull = 100;
    EXPECT_EQ(ctk::CountPrimeNumbersBf(i), 25);
    EXPECT_EQ(ctk::CountPrimeNumbersBf(ui), 25);
    EXPECT_EQ(ctk::CountPrimeNumbersBf(l), 25);
    EXPECT_EQ(ctk::CountPrimeNumbersBf(ul), 25);
    EXPECT_EQ(ctk::CountPrimeNumbersBf(ll), 25);
    EXPECT_EQ(ctk::CountPrimeNumbersBf(ull), 25);
    //
    EXPECT_EQ(ctk::CountPrimeNumbers(i), 25);
    EXPECT_EQ(ctk::CountPrimeNumbers(ui), 25);
    EXPECT_EQ(ctk::CountPrimeNumbers(l), 25);
    EXPECT_EQ(ctk::CountPrimeNumbers(ul), 25);
    EXPECT_EQ(ctk::CountPrimeNumbers(ll), 25);
    EXPECT_EQ(ctk::CountPrimeNumbers(ull), 25);
}

TEST_F(CtkMathTest, Test_ListingPrimes) {
    int i = 100;
    unsigned int ui = 100;
    long l = 100;
    unsigned long ul = 100;
    long long ll = 100;
    unsigned long long ull = 100;
    EXPECT_EQ(ctk::GeneratePrimeNumbersBf(i), some_primes_i);
    EXPECT_EQ(ctk::GeneratePrimeNumbersBf(ui), some_primes_ui);
    EXPECT_EQ(ctk::GeneratePrimeNumbersBf(l), some_primes_l);
    EXPECT_EQ(ctk::GeneratePrimeNumbersBf(ul), some_primes_ul);
    EXPECT_EQ(ctk::GeneratePrimeNumbersBf(ll), some_primes_ll);
    EXPECT_EQ(ctk::GeneratePrimeNumbersBf(ull), some_primes_ull);
    //
    EXPECT_EQ(ctk::GeneratePrimeNumbers(i), some_primes_i);
    EXPECT_EQ(ctk::GeneratePrimeNumbers(ui), some_primes_ui);
    EXPECT_EQ(ctk::GeneratePrimeNumbers(l), some_primes_l);
    EXPECT_EQ(ctk::GeneratePrimeNumbers(ul), some_primes_ul);
    EXPECT_EQ(ctk::GeneratePrimeNumbers(ll), some_primes_ll);
    EXPECT_EQ(ctk::GeneratePrimeNumbers(ull), some_primes_ull);
}
#endif
