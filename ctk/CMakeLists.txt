cmake_minimum_required(VERSION 3.10)

project(ctklib VERSION 0.1)

add_library(ctklib-static STATIC
ctkabstractmatrix.cpp
ctkauthobject.cpp
ctkcontours.cpp
ctkmath.cpp
ctkpolygon.cpp
ctkauthentication.cpp
ctkbinarymatrix.cpp
ctkimage.cpp
ctknumericmatrix.cpp
ctkvectoraux.cpp
)

