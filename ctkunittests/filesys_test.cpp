#include "filesys_test.h"

#include <iostream>

#include "ctk/misc/filesys.h"
#include "ctk/misc/string_aux.h"

#include "test_setup.h"

#ifdef TEST_FILESYS
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
    splitted = ctk::SplitString(workspacePath, "/");
    EXPECT_EQ(splitted.back(), "ctk");
    // Change the path (and then CurrentPath())
    ctk::ChangeCurrentPath(sourcePath);
    splitted = ctk::SplitString(ctk::CurrentPath(), "/");
    EXPECT_EQ(splitted.back(), "ctkunittests");
}

// This test only works if the test is run from 
// $CTK_WORKSPACE/build/ctkunittest (or any folder at the same level)
// TODO: figure out a generic way to test 
// TEST_F(CtkFileSystemTest, Test_AbsolutePath) {
//     auto home = ctk::GetEnvironmentVariable("CTK_WORKSPACE");
//     auto absPath = ctk::AbsolutePath("../../ctkunittests");
//     EXPECT_EQ(absPath, sourcePath);
//     absPath = ctk::AbsolutePath(sourcePath + "/filesys_test.cpp");
//     EXPECT_EQ(absPath, sourcePath + "/filesys_test.cpp");
// }

TEST_F(CtkFileSystemTest, Test_ContainsFile) {
    EXPECT_TRUE(ctk::ContainsFileOrDir(workspacePath, "ctkunittests"));
    EXPECT_TRUE(ctk::ContainsFileOrDir(sourcePath, "filesys_test.cpp"));
    EXPECT_FALSE(ctk::ContainsFileOrDir(sourcePath, "filesys.cpp"));
}

TEST_F(CtkFileSystemTest, Test_ListDirAbsolutePath) {
    auto files = ctk::ListDir(sourcePath);
    EXPECT_EQ(files.size(), 29);
    bool containsFyleSys = false;
    for (auto &fn : files) {
        if (fn == sourcePath + "/filesys_test.cpp")
            containsFyleSys = true;
    }
    EXPECT_TRUE(containsFyleSys);
}

// See coment before test CtkFileSystemTest::Test_AbsolutePath
// TODO: figure out a generic way to test 
// TEST_F(CtkFileSystemTest, Test_ListDirRelativePath) {
//     auto files = ctk::ListDir("../../ctkunittests");
//     EXPECT_EQ(files.size(), 29);
//     bool containsFyleSys = false;
//     for (auto &fn : files) {
//         if (fn == "../../ctkunittests/filesys_test.cpp")
//             containsFyleSys = true;
//     }
//     EXPECT_TRUE(containsFyleSys);
// }

TEST_F(CtkFileSystemTest, Test_FileNamesWithAllFilters) {
    const std::vector<std::string> filters = {"cpp", "_test"};
    auto files = ctk::ListFilesContainingAllExpressions(sourcePath, 
                                                     filters);
    EXPECT_EQ(files.size(), 12);
    bool containsFyleSys = false;
    for (auto &fn : files) {
        if (fn == sourcePath + "/filesys_test.cpp")
            containsFyleSys = true;
    }
    EXPECT_TRUE(containsFyleSys);
}

TEST_F(CtkFileSystemTest, Test_FileNamesWithAnyFilter) {
    const std::vector<std::string> filters = {"cpp", "_test"};
    auto files = ctk::ListFilesContainingAnyExpressions(sourcePath, 
                                                     filters);
    EXPECT_EQ(files.size(), 25);
    bool containsFyleSys = false;
    for (auto &fn : files) {
        if (fn == sourcePath + "/filesys_test.cpp")
            containsFyleSys = true;
    }
    EXPECT_TRUE(containsFyleSys);
}

TEST_F(CtkFileSystemTest, Test_FileNamesWithoutAllFilters) {
    const std::vector<std::string> filters = {".pri", ".h"};
    auto files = ctk::ListFilesWithoutAllExpressions(sourcePath, 
                                                     filters);
    EXPECT_EQ(files.size(), 15);    
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
#endif
