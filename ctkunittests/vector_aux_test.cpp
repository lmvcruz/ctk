#include "vector_aux_test.h"

#include <vector>

#include "ctk/misc/vector_aux.h"

#include "test_setup.h"

#ifdef TEST_VEC_AUX
TEST(CtkVecAuxTest, Test_Show) {
    std::vector<int> vec = {1,2,3,5,6,7,8};
    //
    testing::internal::CaptureStdout();
    ctk::show(vec);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "1 2 3 5 6 7 8 \n");
    //
    testing::internal::CaptureStdout();
    ctk::show(vec, ", ");
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "1, 2, 3, 5, 6, 7, 8, \n");
}

TEST(CtkVecAuxTest, Test_RangeVector) {
    std::vector<int> vec1gt = {1,2,3,4,5,6,7,8};
    std::vector<int> vec1rv = ctk::RangeVector(1,8);
    EXPECT_EQ(vec1gt, vec1rv);
    //
    std::vector<int> vec2gt = {10,9,8};
    std::vector<int> vec2rv = ctk::RangeVector(10,8);
    EXPECT_EQ(vec2gt, vec2rv);
    //
    std::vector<int> vec3gt = {10};
    std::vector<int> vec3rv = ctk::RangeVector(10,10);
    EXPECT_EQ(vec3gt, vec3rv);
    //
    std::vector<int> vec4gt = {-3,-2,-1,0,1,2};
    std::vector<int> vec4rv = ctk::RangeVector(-3,2);
    EXPECT_EQ(vec4gt, vec4rv);
    //
    std::vector<int> vec5gt = {2,1,0,-1,-2,-3};
    std::vector<int> vec5rv = ctk::RangeVector(2,-3);
    EXPECT_EQ(vec5gt, vec5rv);
}

TEST(CtkVecAuxTest, Test_Shuffle1) {
    int maxV = 9;
    std::vector<int> vec1gt = ctk::RangeVector(0,maxV);
    std::vector<int> vec1sh = vec1gt;
    ctk::Shuffle(vec1sh);
    EXPECT_EQ(vec1gt.size(), vec1sh.size());
    EXPECT_NE(vec1gt, vec1sh);
    //
    int countDiff = 0;
    for (int i=0; i<=maxV; i++) {
        if (vec1sh[i]!=vec1gt[i]) countDiff++;
    }
    int rate = static_cast<int>(static_cast<float>(vec1gt.size())*0.8);
    EXPECT_GE(countDiff, rate);
}

TEST(CtkVecAuxTest, Test_Shuffle2) {
    int maxV = 900;
    std::vector<int> vec1gt = ctk::RangeVector(0,maxV);
    std::vector<int> vec1sh = vec1gt;
    ctk::Shuffle(vec1sh, 1000);
    EXPECT_EQ(vec1gt.size(), vec1sh.size());
    EXPECT_NE(vec1gt, vec1sh);
    //
    int countDiff = 0;
    for (int i=0; i<=maxV; i++) {
        if (vec1sh[i]!=vec1gt[i]) countDiff++;
    }
    int rate = static_cast<int>(static_cast<float>(vec1gt.size())*0.8);
    EXPECT_GE(countDiff, rate);
}

TEST(CtkVecAuxTest, Test_Shuffle3) {
    int maxV = 10000;
    std::vector<int> vec1gt = ctk::RangeVector(0,maxV);
    std::vector<int> vec1sh = vec1gt;
    ctk::Shuffle(vec1sh, -1000);
    EXPECT_EQ(vec1gt.size(), vec1sh.size());
    EXPECT_NE(vec1gt, vec1sh);
    //
    int countDiff = 0;
    for (int i=0; i<=maxV; i++) {
        if (vec1sh[i]!=vec1gt[i]) countDiff++;
    }
    int rate = static_cast<int>(static_cast<float>(vec1gt.size())*0.8);
    EXPECT_GE(countDiff, rate);
}
#endif
