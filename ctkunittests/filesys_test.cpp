#include "filesys_test.h"

#include <iostream>

#include "ctk/misc/filesys.h"
#include "ctk/misc/string_aux.h"

#include "test_setup.h"

void CtkFileSystemTest::SetUp() {
    if (curPath == "") {
        curPath = ctk::CurrentPath();
    }
    ctk::ChangeCurrentPath(curPath);
}

TEST_F(CtkFileSystemTest, Test_Exists) {
    EXPECT_TRUE(ctk::Exists("../../ctkunittests"));
    EXPECT_FALSE(ctk::Exists("../../ctkunitte"));
    EXPECT_TRUE(ctk::Exists("../../ctkunittests/filesys_test.cpp"));
    EXPECT_FALSE(ctk::Exists("../../ctkunittests/filesys_t.cp"));
}

TEST_F(CtkFileSystemTest, Test_IsFileOrIsDir) {
    EXPECT_FALSE(ctk::IsFile("../../ctkunittests"));
    EXPECT_TRUE(ctk::IsDir("../../ctkunittests"));
    EXPECT_FALSE(ctk::IsEmpty("../../ctkunittests"));
    EXPECT_TRUE(ctk::IsFile("../../ctkunittests/filesys_test.cpp"));
    EXPECT_FALSE(ctk::IsDir("../../ctkunittests/filesys_test.cpp"));
    EXPECT_FALSE(ctk::IsEmpty("../../ctkunittests/filesys_test.cpp"));
}

TEST_F(CtkFileSystemTest, Test_CurrentPath) {
    std::vector<std::string> splitted;
    // Query current path and does not change it
    splitted = ctk::splitString(ctk::CurrentPath(), "/");
    EXPECT_EQ(splitted.back(), "ctkunittests");
    // Query different path but does not change it 
    // So, CurrentPath() is still ctkunittests
    splitted = ctk::splitString(ctk::CurrentPath(".."), "/");
    EXPECT_EQ(splitted.back(), "build");
    splitted = ctk::splitString(ctk::CurrentPath(), "/");
    EXPECT_EQ(splitted.back(), "ctkunittests");
    // Change the path (and then CurrentPath())
    ctk::ChangeCurrentPath("..");
    splitted = ctk::splitString(ctk::CurrentPath(), "/");
    EXPECT_EQ(splitted.back(), "build");
}

// TODO: This test has to be changed
// We can define an environment variable with the $WORKSPACE 
// and concate the expect value from it
TEST_F(CtkFileSystemTest, Test_AbsolutePath) {
    auto absPath = ctk::AbsolutePath("../../ctkunittests");
    EXPECT_EQ(absPath, "/home/leandroc_local/Workspace/github/ctk/ctkunittests");
    absPath = ctk::AbsolutePath("../../ctkunittests/filesys_test.cpp");
    EXPECT_EQ(absPath, "/home/leandroc_local/Workspace/github/ctk/ctkunittests/filesys_test.cpp");
}

TEST_F(CtkFileSystemTest, Test_ContainsFile) {
    EXPECT_TRUE(ctk::ContainsFileOrDir("../..", "ctkunittests"));
    EXPECT_TRUE(ctk::ContainsFileOrDir("../../ctkunittests", "filesys_test.cpp"));
    EXPECT_FALSE(ctk::ContainsFileOrDir("../../ctkunittests", "filesys.cpp"));
}

TEST_F(CtkFileSystemTest, Test_ListDir) {
    auto files = ctk::ListDir("../../ctkunittests");
    EXPECT_EQ(files.size(), 25);
    bool containsFyleSys = false;
    for (auto &fn : files) {
        if (fn == "../../ctkunittests/filesys_test.cpp")
            containsFyleSys = true;
    }
    EXPECT_TRUE(containsFyleSys);
}

TEST_F(CtkFileSystemTest, Test_FileNamesAllFiltered) {
    const std::vector<std::string> filters = {"cpp", "_test"};
    auto files = ctk::ListFilesContainingAllExpressions("../../ctkunittests", 
                                                     filters);
    EXPECT_EQ(files.size(), 10);
    bool containsFyleSys = false;
    for (auto &fn : files) {
        if (fn == "../../ctkunittests/filesys_test.cpp")
            containsFyleSys = true;
    }
    EXPECT_TRUE(containsFyleSys);
}

TEST_F(CtkFileSystemTest, Test_FileNamesAnyFiltered) {
    const std::vector<std::string> filters = {"cpp", "_test"};
    auto files = ctk::ListFilesContainingAnyExpressions("../../ctkunittests", 
                                                     filters);
    EXPECT_EQ(files.size(), 21);
    bool containsFyleSys = false;
    for (auto &fn : files) {
        if (fn == "../../ctkunittests/filesys_test.cpp")
            containsFyleSys = true;
    }
    EXPECT_TRUE(containsFyleSys);
}