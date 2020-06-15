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
        ctkbinaryimagetest.cpp \
        ctkgrayimagetest.cpp \
        ctkmathtest.cpp \
        ctknumericmatrixtest.cpp \
        ctkpolygontest.cpp \
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
    ctkbinaryimagetest.h \
    ctkgrayimagetest.h \
    ctkmathtest.h \
    ctknumericmatrixtest.h \
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
    QT_CONFIG -= no-pkg-configs
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


TESTS_DIR = C:\Users\3334\Documents\git\external\googletest-release-1.10.0\googletest

INCLUDEPATH +="$$TESTS_DIR\include"
DEPENDPATH +="$$TESTS_DIR\include"

LIBS +=  C:/OpenCV/Build/install/x64/mingw/lib/libopencv_core411.dll.a
LIBS +=  C:/OpenCV/Build/install/x64/mingw/lib/libopencv_imgproc411.dll.a
LIBS +=  C:/OpenCV/Build/install/x64/mingw/lib/libopencv_highgui411.dll.a
LIBS +=  C:/OpenCV/Build/install/x64/mingw/lib/libopencv_imgcodecs411.dll.a
LIBS +=  C:/OpenCV/Build/install/x64/mingw/lib/libopencv_features2d411.dll.a
LIBS +=  C:/OpenCV/Build/install/x64/mingw/lib/libopencv_face411.dll.a
LIBS +=  C:/OpenCV/Build/install/x64/mingw/lib/libopencv_objdetect411.dll.a
LIBS +=  C:/OpenCV/Build/install/x64/mingw/lib/libopencv_video411.dll.a
LIBS +=  C:/OpenCV/Build/install/x64/mingw/lib/libopencv_ml411.dll.a
LIBS +=  C:/OpenCV/Build/install/x64/mingw/lib/libopencv_dnn411.dll.a
LIBS +=  C:/OpenCV/Build/install/x64/mingw/lib/libopencv_videoio411.dll.a
LIBS +=  C:/OpenCV/Build/install/x64/mingw/lib/libopencv_calib3d411.dll.a
LIBS +=  C:/Users/3334/Documents/git/external/googletest-release-1.10.0/build/lib/libgmock.dll.a\
LIBS +=  C:/Users/3334/Documents/git/external/googletest-release-1.10.0/build/lib/libgmock_main.dll.a\
LIBS +=  C:/Users/3334/Documents/git/external/googletest-release-1.10.0/build/lib/libgtest.dll.a\
LIBS +=  C:/Users/3334/Documents/git/external/googletest-release-1.10.0/build/lib/libgtest_main.dll.a\

}


