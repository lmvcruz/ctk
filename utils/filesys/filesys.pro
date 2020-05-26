QT -= gui

TEMPLATE = lib
CONFIG += staticlib
CONFIG += release
CONFIG += warn_on

CONFIG += c++14

ROOT_FOLDER = $$PWD/../../
BUILD_FOLDER = $$ROOT_FOLDER/../build

## Propgram Setup
TARGET = filesys
OBJECTS_DIR = $$BUILD_FOLDER/$$TARGET
MOC_DIR = $$BUILD_FOLDER/$$TARGET
DESTDIR = $$BUILD_FOLDER/libs


SOURCES += \
    filesystem.cpp

HEADERS += \
    filesystem.h

## Dependecies
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

unix:!macx {
    CONFIG += link_pkgconfig
    PKGCONFIG += opencv
}
macx: {
    QT_CONFIG -= no-pkg-config
    CONFIG += link_pkgconfig
    PKG_CONFIG = /usr/local/bin/pkg-config
    PKGCONFIG += opencv4
    PKGCONFIG += tesseract
    PKGCONFIG += zbar ilmbase
}

