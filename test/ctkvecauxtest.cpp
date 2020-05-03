#include "ctkvecauxtest.h"

#include <vector>

#include "ctkvectoraux.h"

TEST(CgVecAuxTest, CgMathTestCoutingPrimes) {
    std::vector<int> vec = {1,2,3,5,6,7,8};
    //
    testing::internal::CaptureStdout();
    show(vec);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "1 2 3 5 6 7 8 \n");
    //
    testing::internal::CaptureStdout();
    show(vec, ", ");
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "1, 2, 3, 5, 6, 7, 8, \n");
}
