TEMPLATE = app
CONFIG += c++14
CONFIG -= app_bundle
CONFIG -= qt

TARGET = matrices
ROOT_FOLDER = $$PWD/../../
BUILD_FOLDER = $$ROOT_FOLDER/../build

OBJECTS_DIR = $$BUILD_FOLDER/$$TARGET
MOC_DIR = $$BUILD_FOLDER/$$TARGET
DESTDIR = $$BUILD_FOLDER/$$TARGET

SOURCES += main.cpp

# GTest and GBenchmark
LIBS += -L/usr/local/lib/ -lgtest -lbenchmark
INCLUDEPATH += "/usr/local/include/"


## CGTools
INCLUDEPATH += $$ROOT_FOLDER/ctk
DEPENDPATH += $$ROOT_FOLDER/ctk

LIBS += -L$$BUILD_FOLDER/libs -lctk
PRE_TARGETDEPS += $$BUILD_FOLDER/libs/libctk.a

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

win32:!macx  {

    EXTLIB_DIR = $$PWD/../../../../../external

    # GOOGLE BENCHMARK
    INCLUDEPATH += $$EXTLIB_DIR/benchmark/include
    INCLUDEPATH += $$EXTLIB_DIR/benchmark/src



    SOURCES +=$$EXTLIB_DIR/benchmark/src/sysinfo.cc

    LIBS           += -L$$EXTLIB_DIR/benchmark/build/src \
                            -lshlwapi \
                            -lkernel32 \
                            -luser32 \
                            -lgdi32 \
                            -lwinspool \
                            -lshell32 \
                            -lole32 \
                            -loleaut32 \
                            -luuid \
                            -lcomdlg32 \
                            -ladvapi32 \
                            -lpthread \
                            -lbenchmark
    PRE_TARGETDEPS +=   $$EXTLIB_DIR/benchmark/build/src/libbenchmark.a


}
