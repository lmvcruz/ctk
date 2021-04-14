#include "filesys_test.h"

#include <iostream>

#include "ctk/misc/filesys.h"
#include "ctk/misc/string_aux.h"

#include "test_setup.h"

TEST_F(CtkFileSystemTest, Test_Show) {
    std::vector<std::string> splitted;
    // Query current path and does not change it
    splitted = ctk::splitString(ctk::currentPath(), "/");
    EXPECT_EQ(splitted.back(), "ctkunittests");
    // Query different path but does not change it 
    // So, currentPath() is still ctkunittests
    splitted = ctk::splitString(ctk::currentPath(".."), "/");
    EXPECT_EQ(splitted.back(), "build");
    splitted = ctk::splitString(ctk::currentPath(), "/");
    EXPECT_EQ(splitted.back(), "ctkunittests");
    // Change the path (and then currentPath())
    ctk::changeCurrentPath("..");
    splitted = ctk::splitString(ctk::currentPath(), "/");
    EXPECT_EQ(splitted.back(), "build");
}