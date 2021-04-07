cmake_minimum_required(VERSION 3.0.0)

project(ctklib VERSION 0.1)

add_library(ctklib STATIC
authentication/auth_object.cpp
authentication/authentication.cpp
geometry/polygon.cpp
image/image.cpp
img_proc/contours.cpp
math/prime_numbers.cpp
matrix/abstract_matrix.cpp
matrix/numeric_matrix.cpp
misc/ctkvectoraux.cpp
)

# set(OpenCV_LIBS opencv_core opencv_imgproc opencv_calib3d opencv_video opencv_features2d opencv_ml opencv_highgui opencv_objdetect)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${OpenCV_LIBS} )