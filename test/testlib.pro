TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

TARGET = test_lib
ROOT_FOLDER = $$PWD/..
BUILD_FOLDER = $$ROOT_FOLDER/../build

OBJECTS_DIR = $$BUILD_FOLDER/$$TARGET
MOC_DIR = $$BUILD_FOLDER/$$TARGET
DESTDIR = $$BUILD_FOLDER/$$TARGET

SOURCES += \
        ctkmathtest.cpp \
        ctkvecauxtest.cpp \
        main.cpp

LIBS += -L/usr/local/lib/ -lgtest
INCLUDEPATH += "/usr/local/include/"


## UniQode Library
INCLUDEPATH += $$ROOT_FOLDER/ctk
DEPENDPATH += $$ROOT_FOLDER/ctk

LIBS += -L$$BUILD_FOLDER/ctk -lctk
PRE_TARGETDEPS += $$BUILD_FOLDER/ctk/libctk.a

HEADERS += \
    ctkmathtest.h \
    ctkvecauxtest.h
