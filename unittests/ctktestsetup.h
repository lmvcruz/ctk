#ifndef CTKTESTSETUP_H
#define CTKTESTSETUP_H

#include <string>

#define TEST_ALL 0

#if ( TEST_ALL || 0 )
#define TEST_BINARY_IMAGE
#endif


#if ( TEST_ALL || 0 )
#define TEST_GRAY_IMAGE
#endif

#if ( TEST_ALL || 0 )
#define TEST_MATH
#endif

#if ( TEST_ALL || 0 )
#define TEST_NUMERIC_MATRICES
#endif

#if ( TEST_ALL || 1 )
#define TEST_RGB_IMAGES
#endif

#if ( TEST_ALL || 0 )
#define TEST_VEC_AUX
#endif

#if ( TEST_ALL || 0 )
#define TEST_POLYGON
#endif

const std::string INPUT_DIR = "../../ctk/data/test/";
const std::string OUTPUT_DIR = "test_out/";
const bool SAVE_IMAGES = true;

#endif // CTKTESTSETUP_H
