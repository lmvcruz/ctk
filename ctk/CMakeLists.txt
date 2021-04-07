cmake_minimum_required(VERSION 3.0.0)

project(ctklib VERSION 0.1)

add_library(ctklib STATIC
authentication/auth_object.cpp
authentication/authentication.cpp
geometry/polygon.cpp
image/image.cpp
img_proc/contours.cpp
math/prime_numbers.cpp
matrix/ctkabstractmatrix.cpp
matrix/ctknumericmatrix.cpp
misc/ctkvectoraux.cpp
)

# set(OpenCV_LIBS opencv_core opencv_imgproc opencv_calib3d opencv_video opencv_features2d opencv_ml opencv_highgui opencv_objdetect opencv_contrib opencv_legacy opencv_gpu)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${OpenCV_LIBS} )