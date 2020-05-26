#include "gtest/gtest.h"

#include <string>

// This is available in all editors.
std::string INPUT_DIR = "../../ctk/data/test/";
std::string OUTPUT_DIR = "test_out/";
bool SAVE_IMAGES = true;

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
