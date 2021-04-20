#pragma once

#include <string>

#define TEST_ALL 0

#if ( TEST_ALL || 0 )
#define TEST_BINARY_IMAGE
#endif


#if ( TEST_ALL || 0 )
#define TEST_GRAY_IMAGE
#endif

#if ( TEST_ALL || 0 )
#define TEST_PRIME_NUMBERS
#endif

#if ( TEST_ALL || 0 )
#define TEST_NUMERIC_MATRICES
#endif

#if ( TEST_ALL || 0 )
#define TEST_RGB_IMAGES
#endif

#if ( TEST_ALL || 1 )
#define TEST_VEC_AUX
#endif

#if ( TEST_ALL || 0 )
#define TEST_POLYGON
#endif

#if ( TEST_ALL || 0 )
#define TEST_POINT
#endif

#if ( TEST_ALL || 0 )
#define TEST_FILESYS
#endif

#if ( TEST_ALL || 0 )
#define TEST_STRING_AUX
#endif

const std::string INPUT_DIR = "../../data/test/";
const std::string OUTPUT_DIR = "test_out/";
const bool SAVE_IMAGES = true;
