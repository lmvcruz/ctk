cmake_minimum_required(VERSION 3.0.0)
project(primenumbench VERSION 0.1.0)

add_executable(primenumbench
    main.cpp
)

# set(OpenCV_LIBS opencv_core opencv_imgproc opencv_calib3d opencv_video opencv_features2d opencv_ml opencv_highgui opencv_objdetect)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

find_package(benchmark REQUIRED)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

target_link_libraries(${PROJECT_NAME} 
    ${OpenCV_LIBS}
    ${GTEST_LIBRARIES} 
    -lpthread
    ctklib
    benchmark::benchmark
)
