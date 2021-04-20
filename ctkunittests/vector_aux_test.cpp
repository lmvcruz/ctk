#include "vector_aux_test.h"

#include <vector>

#include "ctk/misc/vector_aux.h"

#include "test_setup.h"

#ifdef TEST_VEC_AUX
TEST(CtkVecAuxTest, Test_Show) {
    std::vector<int> vec = {1, 2, 3, 5, 6, 7, 8};
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
    std::vector<int> vec1gt = {1, 2, 3, 4, 5, 6, 7, 8};
    std::vector<int> vec1rv = ctk::RangeVector(1, 8);
    EXPECT_EQ(vec1gt, vec1rv);
    //
    std::vector<int> vec2gt = {10, 9, 8};
    std::vector<int> vec2rv = ctk::RangeVector(10, 8);
    EXPECT_EQ(vec2gt, vec2rv);
    //
    std::vector<int> vec3gt = {10};
    std::vector<int> vec3rv = ctk::RangeVector(10, 10);
    EXPECT_EQ(vec3gt, vec3rv);
    //
    std::vector<int> vec4gt = {-3, -2, -1, 0, 1, 2};
    std::vector<int> vec4rv = ctk::RangeVector(-3, 2);
    EXPECT_EQ(vec4gt, vec4rv);
    //
    std::vector<int> vec5gt = {2, 1, 0, -1, -2, -3};
    std::vector<int> vec5rv = ctk::RangeVector(2, -3);
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
    for (int i = 0; i <= maxV; ++i) {
        if (vec1sh[i] != vec1gt[i]) countDiff++;
    }
    int rate = static_cast<int>(static_cast<float>(vec1gt.size()) * 0.8);
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
    for (int i = 0; i <= maxV; ++i) {
        if (vec1sh[i] != vec1gt[i]) countDiff++;
    }
    int rate = static_cast<int>(static_cast<float>(vec1gt.size()) * 0.8);
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
    for (int i = 0; i <= maxV; ++i) {
        if (vec1sh[i] != vec1gt[i]) countDiff++;
    }
    int rate = static_cast<int>(static_cast<float>(vec1gt.size()) * 0.8);
    EXPECT_GE(countDiff, rate);
}

TEST(CtkVecAuxTest, Test_Contains) {
    std::vector<int> veci = {-1, 7, 2, 0, 1, 7, 1, 3, 2};
    EXPECT_TRUE(ctk::Contains(veci, 1));
    EXPECT_FALSE(ctk::Contains(veci, 10)); 
    std::vector<double> vecd = {-1.0, 7.0, 2.0, 0.0, 1.0, 7.0, 1.0, 3.0, 2.0};
    EXPECT_TRUE(ctk::Contains(vecd, 1.0));
    EXPECT_FALSE(ctk::Contains(vecd, 10.0)); 
    std::vector<std::string> vecs = {"-1", "7", "2", "0", "1", "7", "1", "3", "2"};
    // Explicit initialization of string is necessary
    // In ctk::Contains(vecs, "-1"); 
    //   "-1" is const char [3] instead of string
    EXPECT_TRUE(ctk::Contains(vecs, std::string("-1")));
    std::string s = "10";
    EXPECT_FALSE(ctk::Contains(vecs, s));
}

TEST(CtkVecAuxTest, Test_IndexOf) {
    std::vector<int> veci = {-1, 7, 2, 0, 1, 7, 1, 3, 2};
    EXPECT_EQ(ctk::IndexOf(veci, 1), 4);
    EXPECT_EQ(ctk::IndexOf(veci, 1, 5), 6);
    EXPECT_EQ(ctk::IndexOf(veci, 10), veci.size()); 
    std::vector<double> vecd = {-1.0, 7.0, 2.0, 0.0, 1.0, 7.0, 1.0, 3.0, 2.0};
    EXPECT_EQ(ctk::IndexOf(vecd, 1.0), 4);
    EXPECT_EQ(ctk::IndexOf(vecd, 10.0), vecd.size()); 
    std::vector<std::string> vecs = {"-1", "7", "2", "0", "1", "7", "1", "3", "2"};
    // See comment in Test_Contains
    EXPECT_EQ(ctk::IndexOf(vecs, std::string("-1")), 0);
    std::string s = "10";
    EXPECT_EQ(ctk::IndexOf(vecs, s), vecs.size());
}

TEST(CtkVecAuxTest, Test_ContainsQueries) {
    std::vector<int> veci = {-1, 7, 2, 0, 1, 7, 1, 3, 2};
    std::vector<int> queriesTrueI = {7, 0, 2};
    std::vector<int> queriesFalseI = {7, 10, 2};
    EXPECT_TRUE(ctk::Contains(veci, queriesTrueI));
    EXPECT_FALSE(ctk::Contains(veci, queriesFalseI)); 
    std::vector<double> vecd = {-1.0, 7.0, 2.0, 0.0, 1.0, 7.0, 1.0, 3.0, 2.0};
    std::vector<double> queriesTrueD = {7., 0., 2.};
    std::vector<double> queriesFalseD = {7., 10., 2.};
    EXPECT_TRUE(ctk::Contains(vecd, queriesTrueD));
    EXPECT_FALSE(ctk::Contains(vecd, queriesFalseD)); 
    std::vector<std::string> vecs = {"-1", "7", "2", "0", "1", "7", "1", "3", "2"};
    std::vector<std::string> queriesTrueS = {"7", "0", "2"};
    std::vector<std::string> queriesFalseS = {"7", "10", "2"};
    EXPECT_TRUE(ctk::Contains(vecs, queriesTrueS));
    EXPECT_FALSE(ctk::Contains(vecs, queriesFalseS)); 
}

TEST(CtkVecAuxTest, Test_ContainsIndices) {
    std::vector<int> veci = {-1, 7, 2, 0, 1, 7, 1, 3, 2};
    std::vector<int> indices = ctk::ContainsIndices(veci, 1);
    EXPECT_EQ(indices, std::vector<int>({4, 6}));
    std::vector<double> vecd = {-1.0, 7.0, 2.0, 0.0, 1.0, 7.0, 1.0, 3.0, 2.0};
    indices = ctk::ContainsIndices(vecd, 1.0);
    EXPECT_EQ(indices, std::vector<int>({4, 6}));
    indices = ctk::ContainsIndices(vecd, 10.0);
    EXPECT_EQ(indices.size(), 0);
    std::vector<std::string> vecs = {"-1", "7", "2", "0", "1", "7", "1", "3", "2"};
    // See comment in Test_Contains
    indices = ctk::ContainsIndices(vecs, std::string("1"));
    EXPECT_EQ(indices, std::vector<int>({4, 6}));
}

TEST(CtkVecAuxTest, Test_ContainsIndicesQueries) {
    std::vector<int> veci = {-1, 7, 2, 0, 1, 7, 1, 3, 2};
    std::vector<int> queriesTrueI = {7, 0, 2};
    std::vector<int> indices = ctk::ContainsIndices(veci, queriesTrueI);
    EXPECT_EQ(indices, std::vector<int>({1, 2, 3, 5, 8}));
    std::vector<int> queriesFalseI = {7, 10, 2};
    indices = ctk::ContainsIndices(veci, queriesFalseI);
    EXPECT_EQ(indices, std::vector<int>({1, 2, 5, 8}));
}

#endif
