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

add_subdirectory (benchmark/image)
add_subdirectory (benchmark/matrices)
add_subdirectory (benchmark/primenumbers)

add_subdirectory (demos/mosaic)

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
target_include_directories(imagebench
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
