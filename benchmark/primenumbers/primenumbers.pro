TEMPLATE = app
CONFIG += c++14
CONFIG -= app_bundle
CONFIG -= qt

TARGET = primenumbers
ROOT_FOLDER = $$PWD/../../
BUILD_FOLDER = $$ROOT_FOLDER/../build

OBJECTS_DIR = $$BUILD_FOLDER/$$TARGET
MOC_DIR = $$BUILD_FOLDER/$$TARGET
DESTDIR = $$BUILD_FOLDER/$$TARGET

SOURCES += \
        main.cpp


HEADERS += \
    cgmathtest.h \
    cgvecauxtest.h

# GTest and GBenchmark
#LIBS += -L/usr/local/lib/ -lgtest -lbenchmark
#INCLUDEPATH += "/usr/local/include/"


## CGTools
INCLUDEPATH += $$ROOT_FOLDER/ctk
DEPENDPATH += $$ROOT_FOLDER/ctk

LIBS += -L$$BUILD_FOLDER/libs -lctk
PRE_TARGETDEPS += $$BUILD_FOLDER/libs/libctk.a

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
