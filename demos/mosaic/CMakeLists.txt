cmake_minimum_required(VERSION 3.0.0)
project(mosaicdemo VERSION 0.1.0)

add_executable(mosaicdemo
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
