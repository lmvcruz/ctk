cmake_minimum_required(VERSION 3.0.0)

project(CTK VERSION 0.1)

if (CMAKE_VERSION VERSION_LESS "3.1")
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++17")
    endif ()
else ()
    set (CMAKE_CXX_STANDARD 17)
endif ()


add_subdirectory (ctk)
add_subdirectory (ctkunittests)

add_subdirectory (benchmark/image/binimage)
add_subdirectory (benchmark/image/rgbimage)
add_subdirectory (benchmark/matrices)
add_subdirectory (benchmark/primenumbers)

add_subdirectory (demos/mosaic)
add_subdirectory (demos/gauss_elimination)

# CTK Lib
target_include_directories(ctklib
    PUBLIC
    ${PROJECT_SOURCE_DIR}
)

# Lib Unit tests
target_include_directories(unittests
    PUBLIC
        ${PROJECT_SOURCE_DIR}/ctkunittests
        ${PROJECT_SOURCE_DIR}
)

# Lib Benchmark
target_include_directories(binimagebench
    PUBLIC
        ${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/ctk
)

target_include_directories(rgbimagebench
    PUBLIC
        ${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/ctk
)

target_include_directories(matrixbench
    PUBLIC
        ${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/ctk
)

target_include_directories(primenumbench
    PUBLIC
        ${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/ctk
)

# Demos
target_include_directories(mosaicdemo
    PUBLIC
        ${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/ctk
        ${PROJECT_SOURCE_DIR}/../ext/rapidjson/include
)

target_include_directories(gauss_elimination
    PUBLIC
        ${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/ctk
)

add_custom_target(ctkunittests
    COMMAND ${PROJECT_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}/ctkunittests/unittests
)