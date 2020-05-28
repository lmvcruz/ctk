TEMPLATE = app
CONFIG += c++14
CONFIG -= app_bundle
CONFIG -= qt

TARGET = unittests
ROOT_FOLDER = $$PWD/..
BUILD_FOLDER = $$ROOT_FOLDER/../build

OBJECTS_DIR = $$BUILD_FOLDER/$$TARGET
MOC_DIR = $$BUILD_FOLDER/$$TARGET
DESTDIR = $$BUILD_FOLDER/$$TARGET

SOURCES += \
        ctkbinarymatrixtest.cpp \
        ctkgrayimagetest.cpp \
        ctkmathtest.cpp \
        ctknumericmatrixtest.cpp \
        ctkrgbimagetest.cpp \
        ctkvecauxtest.cpp \
        main.cpp

LIBS += -L/usr/local/lib/ -lgtest
INCLUDEPATH += "/usr/local/include/"


## UniQode Library
INCLUDEPATH += $$ROOT_FOLDER/ctk
DEPENDPATH += $$ROOT_FOLDER/ctk

LIBS += -L$$BUILD_FOLDER/libs -lctk
PRE_TARGETDEPS += $$BUILD_FOLDER/libs/libctk.a

HEADERS += \
    ctkbinarymatrixtest.h \
    ctkgrayimagetest.h \
    ctkmathtest.h \
    ctknumericmatrixtest.h \
    ctkrgbimagetest.h \
    ctkvecauxtest.h


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
