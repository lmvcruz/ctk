cmake_minimum_required(VERSION 3.0.0)

project(CTK VERSION 0.1)

add_subdirectory (ctk)
add_subdirectory (ctkunittests)

target_include_directories(ctklib
    PUBLIC
        ${PROJECT_SOURCE_DIR}/ctk
        ${PROJECT_SOURCE_DIR}/ctk/authentication
        ${PROJECT_SOURCE_DIR}/ctk/core
        ${PROJECT_SOURCE_DIR}/ctk/geometry
        ${PROJECT_SOURCE_DIR}/ctk/image
        ${PROJECT_SOURCE_DIR}/ctk/img_proc
        ${PROJECT_SOURCE_DIR}/ctk/math
        ${PROJECT_SOURCE_DIR}/ctk/matrix
)

target_include_directories(unittests
    PUBLIC
        ${PROJECT_SOURCE_DIR}/ctkunittests
        ${PROJECT_SOURCE_DIR}/ctk
        ${PROJECT_SOURCE_DIR}/ctk/authentication
        ${PROJECT_SOURCE_DIR}/ctk/core
        ${PROJECT_SOURCE_DIR}/ctk/geometry
        ${PROJECT_SOURCE_DIR}/ctk/image
        ${PROJECT_SOURCE_DIR}/ctk/img_proc
        ${PROJECT_SOURCE_DIR}/ctk/math
        ${PROJECT_SOURCE_DIR}/ctk/matrix
)