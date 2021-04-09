cmake_minimum_required(VERSION 3.0.0)

project(CTK VERSION 0.1)

add_subdirectory (ctk)
add_subdirectory (ctkunittests)
add_subdirectory (benchmark/image)

target_include_directories(ctklib
    PUBLIC
    ${PROJECT_SOURCE_DIR}
)

target_include_directories(unittests
    PUBLIC
        ${PROJECT_SOURCE_DIR}/ctkunittests
        ${PROJECT_SOURCE_DIR}
)

target_include_directories(imagebench
    PUBLIC
        ${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/ctk
        ${PROJECT_SOURCE_DIR}/ctk/matrix
        ${PROJECT_SOURCE_DIR}/ctk/misc
)