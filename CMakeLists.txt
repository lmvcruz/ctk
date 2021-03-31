cmake_minimum_required(VERSION 3.10)

project(CTK VERSION 0.1)

add_subdirectory (ctk)

target_include_directories(ctklib-static
    PUBLIC
        ${PROJECT_SOURCE_DIR}/ctk
)