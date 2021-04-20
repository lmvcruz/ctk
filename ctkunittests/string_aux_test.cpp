#include "string_aux_test.h"

#include <string>

#include "ctk/misc/string_aux.h"

#include "test_setup.h"

#ifdef TEST_STRING_AUX
TEST(CtkStringAuxTest, Test_SplitSpace) {
    std::string str = "Hello World Again";
    std::vector<std::string> splitted = ctk::SplitString(str, " ");
    EXPECT_EQ(splitted.size(), 3);
    EXPECT_EQ(splitted[0], "Hello");
    EXPECT_EQ(splitted[1], "World");
    EXPECT_EQ(splitted[2], "Again");
}

TEST(CtkStringAuxTest, Test_SplitComma) {
    std::string str = "Hello,World,Again";
    std::vector<std::string> splitted = ctk::SplitString(str, ",");
    EXPECT_EQ(splitted.size(), 3);
    EXPECT_EQ(splitted[0], "Hello");
    EXPECT_EQ(splitted[1], "World");
    EXPECT_EQ(splitted[2], "Again");
}

TEST(CtkStringAuxTest, Test_Contains) {
    EXPECT_TRUE(ctk::Contains("Hello", ""));
    EXPECT_FALSE(ctk::Contains("", "Hi"));
    EXPECT_TRUE(ctk::Contains("Hello", "Hell"));
    EXPECT_FALSE(ctk::Contains("Hello", " "));
    EXPECT_TRUE(ctk::Contains("Warning", "War"));
    EXPECT_TRUE(ctk::Contains("Warning", "arn"));
    EXPECT_TRUE(ctk::Contains("Hello World", " "));
    EXPECT_FALSE(ctk::Contains("Hello World", "i"));
}

TEST(CtkStringAuxTest, Test_IndexOf) {
    EXPECT_EQ(ctk::IndexOf("Hello", ""), 0);
    EXPECT_EQ(ctk::IndexOf("", "Hi"), std::string::npos);
    EXPECT_EQ(ctk::IndexOf("Hello", "Hell"), 0);
    EXPECT_EQ(ctk::IndexOf("Hello", " "), std::string::npos);
    EXPECT_EQ(ctk::IndexOf("Warning", "War"), 0);
    EXPECT_EQ(ctk::IndexOf("Warning", "arn"), 1);
    EXPECT_EQ(ctk::IndexOf("Hello World", " "), 5);
    EXPECT_EQ(ctk::IndexOf("Hello World", "i"), std::string::npos);
}

TEST(CtkStringAuxTest, Test_ContainsExps) {
    std::vector<std::string> exps = {"Hell", "World"};
    EXPECT_TRUE(ctk::Contains("Hello", exps));
    EXPECT_FALSE(ctk::Contains("Warning", exps));
    EXPECT_TRUE(ctk::Contains("Hello World", exps));
    EXPECT_TRUE(ctk::Contains("lolo World", exps));
    EXPECT_FALSE(ctk::Contains("hello world", exps));
    EXPECT_FALSE(ctk::Contains("", exps));
    exps.clear();
    EXPECT_FALSE(ctk::Contains("hello world", exps));
    EXPECT_FALSE(ctk::Contains("", exps));
}

TEST(CtkStringAuxTest, Test_ContainsIndices) {
    std::vector<int> indices = ctk::ContainsIndices("Hello Hello", "Hell");
    EXPECT_EQ(indices.size(), 2);
    EXPECT_EQ(indices[0], 0);
    EXPECT_EQ(indices[1], 6);
    indices = ctk::ContainsIndices("Nope Hello World Hello Nope hello", "Hell");
    EXPECT_EQ(indices.size(), 2);
    EXPECT_EQ(indices[0], 5);
    EXPECT_EQ(indices[1], 17);
}

TEST(CtkStringAuxTest, Test_ContainsIndicesExps) {
    std::vector<std::string> exps = {"Hell", "World"};
    std::vector<int> indices = ctk::ContainsIndices("Hello Hello", exps);
    EXPECT_EQ(indices.size(), 2);
    EXPECT_EQ(indices[0], 0);
    EXPECT_EQ(indices[1], 6);
    indices = ctk::ContainsIndices("Nope Hello World Hello Nope hello", exps);
    EXPECT_EQ(indices.size(), 3);
    EXPECT_EQ(indices[0], 5);
    EXPECT_EQ(indices[1], 11);
    EXPECT_EQ(indices[2], 17);
}

#endif
