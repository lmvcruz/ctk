TEMPLATE = app
CONFIG += console c++11
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
LIBS += -L/usr/local/lib/ -lgtest -lbenchmark
INCLUDEPATH += "/usr/local/include/"


## CGTools
INCLUDEPATH += $$ROOT_FOLDER/ctk
DEPENDPATH += $$ROOT_FOLDER/ctk

LIBS += -L$$BUILD_FOLDER/libs -lctk
PRE_TARGETDEPS += $$BUILD_FOLDER/libs/libctk.a

