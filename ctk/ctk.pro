QT -= gui

TEMPLATE = lib
CONFIG += staticlib
CONFIG += release
CONFIG += warn_on

CONFIG += c++14

BUILD_FOLDER = $$PWD/../../build

## Propgram Setup
TARGET = ctk
OBJECTS_DIR = $$BUILD_FOLDER/$$TARGET
MOC_DIR = $$BUILD_FOLDER/$$TARGET
DESTDIR = $$BUILD_FOLDER/$$TARGET


DISTFILES += \
    requirements.txt

SOURCES += \
    ctkabstractmatrix.cpp \
    ctkbinarymatrix.cpp \
    ctkimage.cpp \
    ctkmath.cpp \
    ctknumericmatrix.cpp \
    ctkvectoraux.cpp

HEADERS += \
    ctkabstractmatrix.h \
    ctkbinarymatrix.h \
    ctkimage.h \
    ctkmath.h \
    ctknumericmatrix.h \
    ctkvectoraux.h

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

