cmake_minimum_required(VERSION 3.0.0)
project(rgbimagebench VERSION 0.1.0)

add_executable(rgbimagebench
    main.cpp
)

# set(OpenCV_LIBS opencv_core opencv_imgproc opencv_calib3d opencv_video opencv_features2d opencv_ml opencv_highgui opencv_objdetect)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

find_package(benchmark REQUIRED)

if(NOT WIN32)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif()

target_link_libraries(${PROJECT_NAME}
    ${OpenCV_LIBS}
    ${GTEST_LIBRARIES}
    ctklib
    benchmark::benchmark
)

if(NOT WIN32)
    target_link_libraries(${PROJECT_NAME} pthread)
endif()
