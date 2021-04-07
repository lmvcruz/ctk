cmake_minimum_required(VERSION 3.0.0)
project(unittests VERSION 0.1.0)

# include(ctkunittests)
# include(CTest)
# enable_testing()

add_executable(unittests
ctkbinaryimagetest.cpp
ctkgrayimagetest.cpp
ctkprime_numbers_test.cpp
ctknumericmatrixtest.cpp
ctkrgbimagetest.cpp
ctkvecauxtest.cpp
point_test.cpp
polygon_test.cpp
main.cpp
)


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
