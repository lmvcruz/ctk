QT -= gui

TEMPLATE = lib
CONFIG += staticlib
CONFIG += debug
CONFIG += warn_on

CONFIG += c++14

ROOT_FOLDER = $$PWD/../
BUILD_FOLDER = $$ROOT_FOLDER/../build

## Propgram Setup
TARGET = ctk
OBJECTS_DIR = $$BUILD_FOLDER/$$TARGET
MOC_DIR = $$BUILD_FOLDER/$$TARGET
DESTDIR = $$BUILD_FOLDER/libs


DISTFILES += \
    requirements.txt

SOURCES += \
    ctkabstractmatrix.cpp \
    ctkauthentication.cpp \
    ctkauthobject.cpp \
    ctkcontours.cpp \
    ctkimage.cpp \
    ctkmath.cpp \
    ctknumericmatrix.cpp \
    ctkpolygon.cpp \
    ctkvectoraux.cpp

HEADERS += \
    ctkabstractmatrix.h \
    ctkauthentication.h \
    ctkauthobject.h \
    ctkcontours.h \
    ctkexceptions.h \
    ctkimage.h \
    ctkmath.h \
    ctknumericmatrix.h \
    ctkpoint.h \
    ctkpolygon.h \
    ctktypes.h \
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

win32: {
 OPENCV_DIR = C:\OpenCV\Build\install

 INCLUDEPATH +="$$OPENCV_DIR\include"
 DEPENDPATH +="$$OPENCV_DIR\include"

 LIBS += -L"$$OPENCV_DIR/x64/mingw/lib/"\
-libopencv_core411\
-lopencv_imgproc411\
-lopencv_highgui411\
-lopencv_imgcodecs411\
-lopencv_features2d411\
-lopencv_face411\
-lopencv_objdetect411\
-lopencv_video411\
-lopencv_ml411\
-lopencv_dnn411\
-lopencv_videoio411\
-lopencv_calib3d411
}
