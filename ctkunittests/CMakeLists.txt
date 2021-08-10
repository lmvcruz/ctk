cmake_minimum_required(VERSION 3.0.0)
project(unittests VERSION 0.1.0)

# include(ctkunittests)
# include(CTest)
# enable_testing()

add_executable(unittests
    binary_image_test.cpp
    byte_numbers_test.cpp
    filesys_test.cpp
    image_comparator_test.cpp
    gray_image_test.cpp
    numeric_matrix_test.cpp
    point_test.cpp
    polygon_test.cpp
    prime_numbers_test.cpp
    rgb_image_test.cpp
    string_aux_test.cpp
    vector_aux_test.cpp
    main.cpp
)

# set(OpenCV_LIBS opencv_core opencv_imgproc opencv_calib3d opencv_video opencv_features2d opencv_ml opencv_highgui opencv_objdetect)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} 
${GTEST_LIBRARIES} 
-lpthread)

target_link_libraries(${PROJECT_NAME} ctklib)
