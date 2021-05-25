cmake_minimum_required(VERSION 3.0.0)
project(gauss_elimination VERSION 0.1.0)

add_executable(gauss_elimination
    main.cpp
)

find_package(OpenCV REQUIRED)

include_directories(
    ${OpenCV_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME} 
    ${OpenCV_LIBS}
    ctklib
)
