#include "string_aux_test.h"

#include <string>

#include "ctk/misc/string_aux.h"

#include "test_setup.h"

TEST(CtkStringAuxTest, Test_Show) {
    std::string str = "Hello World";
    std::vector<std::string> splitted = ctk::splitString(str, " ");
    EXPECT_EQ(splitted.size(), 2);
    EXPECT_EQ(splitted[0], "Hello");
    EXPECT_EQ(splitted[1], "World");
}