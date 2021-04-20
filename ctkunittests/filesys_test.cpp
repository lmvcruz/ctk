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
    workspacePath = ctk::GetEnvironmentVariable("CTK_WORKSPACE");
    sourcePath = workspacePath + "/ctkunittests";
}

TEST_F(CtkFileSystemTest, Test_EnvVar) {
    EXPECT_EQ(ctk::GetEnvironmentVariable("CTK_ENV_VAR_TEST"), "Test");
}

TEST_F(CtkFileSystemTest, Test_Exists) {
    EXPECT_TRUE(ctk::Exists(sourcePath));
    EXPECT_FALSE(ctk::Exists(workspacePath + "/ctkunitte"));
    EXPECT_TRUE(ctk::Exists(sourcePath + "/filesys_test.cpp"));
    EXPECT_FALSE(ctk::Exists(sourcePath + "/filesys_t.cp"));
}

TEST_F(CtkFileSystemTest, Test_IsFileOrIsDir) {
    EXPECT_FALSE(ctk::IsFile(sourcePath));
    EXPECT_TRUE(ctk::IsDir(sourcePath));
    EXPECT_FALSE(ctk::IsEmpty(sourcePath));
    EXPECT_TRUE(ctk::IsFile(sourcePath + "/filesys_test.cpp"));
    EXPECT_FALSE(ctk::IsDir(sourcePath + "/filesys_test.cpp"));
    EXPECT_FALSE(ctk::IsEmpty(sourcePath + "/filesys_test.cpp"));
}

TEST_F(CtkFileSystemTest, Test_CurrentPath) {
    std::vector<std::string> splitted;
    // Query current path and does not change it
    splitted = ctk::SplitString(ctk::CurrentPath(), "/");
    EXPECT_EQ(splitted.back(), "ctkunittests");
    // Query different path but does not change it 
    // So, CurrentPath() is still ctkunittests
    splitted = ctk::SplitString(ctk::CurrentPath(".."), "/");
    EXPECT_EQ(splitted.back(), "build");
    splitted = ctk::SplitString(ctk::CurrentPath(), "/");
    EXPECT_EQ(splitted.back(), "ctkunittests");
    // Change the path (and then CurrentPath())
    ctk::ChangeCurrentPath("..");
    splitted = ctk::SplitString(ctk::CurrentPath(), "/");
    EXPECT_EQ(splitted.back(), "build");
}

// This test only works if the test is run from 
// $CTK_WORKSPACE/build/ctkunittest (or any folder at the same level)
// We are exactly testing the conversion from relative to absolute 
// path, so an assumption like that is necessary
TEST_F(CtkFileSystemTest, Test_AbsolutePath) {
    auto home = ctk::GetEnvironmentVariable("CTK_WORKSPACE");
    auto absPath = ctk::AbsolutePath("../../ctkunittests");
    EXPECT_EQ(absPath, sourcePath);
    absPath = ctk::AbsolutePath(sourcePath + "/filesys_test.cpp");
    EXPECT_EQ(absPath, sourcePath + "/filesys_test.cpp");
}

TEST_F(CtkFileSystemTest, Test_ContainsFile) {
    EXPECT_TRUE(ctk::ContainsFileOrDir(workspacePath, "ctkunittests"));
    EXPECT_TRUE(ctk::ContainsFileOrDir(sourcePath, "filesys_test.cpp"));
    EXPECT_FALSE(ctk::ContainsFileOrDir(sourcePath, "filesys.cpp"));
}

TEST_F(CtkFileSystemTest, Test_ListDirAbsolutePath) {
    auto files = ctk::ListDir(sourcePath);
    EXPECT_EQ(files.size(), 25);
    bool containsFyleSys = false;
    for (auto &fn : files) {
        if (fn == sourcePath + "/filesys_test.cpp")
            containsFyleSys = true;
    }
    EXPECT_TRUE(containsFyleSys);
}

// See coment before test CtkFileSystemTest::Test_AbsolutePath
TEST_F(CtkFileSystemTest, Test_ListDirRelativePath) {
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
    auto files = ctk::ListFilesContainingAllExpressions(sourcePath, 
                                                     filters);
    EXPECT_EQ(files.size(), 10);
    bool containsFyleSys = false;
    for (auto &fn : files) {
        if (fn == sourcePath + "/filesys_test.cpp")
            containsFyleSys = true;
    }
    EXPECT_TRUE(containsFyleSys);
}

TEST_F(CtkFileSystemTest, Test_FileNamesAnyFiltered) {
    const std::vector<std::string> filters = {"cpp", "_test"};
    auto files = ctk::ListFilesContainingAnyExpressions(sourcePath, 
                                                     filters);
    EXPECT_EQ(files.size(), 21);
    bool containsFyleSys = false;
    for (auto &fn : files) {
        if (fn == sourcePath + "/filesys_test.cpp")
            containsFyleSys = true;
    }
    EXPECT_TRUE(containsFyleSys);
}

TEST_F(CtkFileSystemTest, Test_CreateDir) {
    std::string dirname = "tcharam";
    EXPECT_FALSE(ctk::Exists(dirname));
    ctk::CreateDir(dirname);
    EXPECT_TRUE(ctk::Exists(dirname));
    ctk::RemoveDir(dirname);
    EXPECT_FALSE(ctk::Exists(dirname));
}
