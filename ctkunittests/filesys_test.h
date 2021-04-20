#pragma once

#include "gtest/gtest.h"

class CtkFileSystemTest : public ::testing::Test {
public:
    void SetUp() override;

    std::string workspacePath;
    std::string sourcePath;
    static std::string curPath;
};

std::string CtkFileSystemTest::curPath = "";