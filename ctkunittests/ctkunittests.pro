TEMPLATE = app
CONFIG += c++14
CONFIG -= app_bundle
CONFIG -= qt

TARGET = ctkunittests
ROOT_FOLDER = $$PWD/..
BUILD_FOLDER = $$ROOT_FOLDER/../build

OBJECTS_DIR = $$BUILD_FOLDER/$$TARGET
MOC_DIR = $$BUILD_FOLDER/$$TARGET
DESTDIR = $$BUILD_FOLDER/$$TARGET

SOURCES += \
        ctkbinaryimagetest.cpp \
        ctkgrayimagetest.cpp \
        ctkmathtest.cpp \
        ctknumericmatrixtest.cpp \
        ctkpointtest.cpp \
        ctkpolygontest.cpp \
        ctkrgbimagetest.cpp \
        ctkvecauxtest.cpp \
        main.cpp


## UniQode Library
INCLUDEPATH += $$ROOT_FOLDER/ctk
DEPENDPATH += $$ROOT_FOLDER/ctk

LIBS += -L$$BUILD_FOLDER/libs -lctk
PRE_TARGETDEPS += $$BUILD_FOLDER/libs/libctk.a

HEADERS += \
    ctkbinaryimagetest.h \
    ctkgrayimagetest.h \
    ctkmathtest.h \
    ctknumericmatrixtest.h \
    ctkpointtest.h \
    ctkpolygontest.h \
    ctkrgbimagetest.h \
    ctktestsetup.h \
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
    LIBS += -L/usr/local/lib/ -lgtest
    INCLUDEPATH += "/usr/local/include/"

    QT_CONFIG -= no-pkg-configs
    CONFIG += link_pkgconfig
    PKG_CONFIG = /usr/local/bin/pkg-config
    PKGCONFIG += opencv4
    PKGCONFIG += tesseract
    PKGCONFIG += zbar ilmbase
}
win32:!macx  {
    EXTLIB_DIR=$$PWD/../../../../external
    include(gtest_dependency.pri)

    OPENCV_DIR = C:\OpenCV\Build\install

    INCLUDEPATH +="$$OPENCV_DIR\include"
    DEPENDPATH +="$$OPENCV_DIR\include"

    LIBS += -L"$$OPENCV_DIR/x64/mingw/lib/"\
    -lopencv_core411\
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
