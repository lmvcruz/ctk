cmake_minimum_required(VERSION 3.0.0)

project(ctklib VERSION 0.1)

add_library(ctklib STATIC
authentication/ctkauth_object.cpp
authentication/ctkauthentication.cpp
geometry/ctkpolygon.cpp
image/ctkimage.cpp
img_proc/ctkcontours.cpp
matrix/ctkabstractmatrix.cpp
matrix/ctknumericmatrix.cpp
ctkmath.cpp
ctkvectoraux.cpp
)

# set(OpenCV_LIBS opencv_core opencv_imgproc opencv_calib3d opencv_video opencv_features2d opencv_ml opencv_highgui opencv_objdetect opencv_contrib opencv_legacy opencv_gpu)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${OpenCV_LIBS} )