#include "byte_numbers_test.h"

#include "test_setup.h"

#include "ctk/math/byte_numbers.h"

#ifdef TEST_BYTE_NUMBERS

TEST_F(CtkByteNumberTest, Test_CountBits) {
    EXPECT_EQ(ctk::CountBits(2), 1);
    EXPECT_EQ(ctk::CountBits(3), 2);
    EXPECT_EQ(ctk::CountBits(4), 1);
    EXPECT_EQ(ctk::CountBits(5), 2);
    EXPECT_EQ(ctk::CountBits(6), 2);
    EXPECT_EQ(ctk::CountBits(7), 3);
    EXPECT_EQ(ctk::CountBits(8), 1);
}

TEST_F(CtkByteNumberTest, Test_Int2Bits) {
    std::vector<int> vec2 = {1, 0};
    std::vector<int> vec4 = {1, 0, 0};
    std::vector<int> vec5 = {1, 0, 1};
    std::vector<int> vec6 = {1, 1, 0};
    std::vector<int> vec10 = {1, 0, 1, 0};
    EXPECT_EQ(ctk::int2bits(2), vec2);
    EXPECT_EQ(ctk::int2bits(4), vec4);
    EXPECT_EQ(ctk::int2bits(5), vec5);
    EXPECT_EQ(ctk::int2bits(6), vec6);
    EXPECT_EQ(ctk::int2bits(10), vec10);
}

TEST_F(CtkByteNumberTest, Test_Bits2Int) {
    std::vector<int> vec2 = {1, 0};
    std::vector<int> vec4 = {1, 0, 0};
    std::vector<int> vec5 = {1, 0, 1};
    EXPECT_EQ(ctk::bits2int(vec2), 2);
    EXPECT_EQ(ctk::bits2int(vec4), 4);
    EXPECT_EQ(ctk::bits2int(vec5), 5);
}
#endif