QT -= gui

TEMPLATE = lib
CONFIG += staticlib
CONFIG += release
CONFIG += warn_on

CONFIG += c++11

BUILD_FOLDER = $$PWD/../../build

## Propgram Setup
TARGET = ctk
OBJECTS_DIR = $$BUILD_FOLDER/$$TARGET
MOC_DIR = $$BUILD_FOLDER/$$TARGET
DESTDIR = $$BUILD_FOLDER/$$TARGET


#SOURCES +=

HEADERS += \
    ctkmath.h \
    ctkvectoraux.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    requirements.txt

SOURCES += \
    ctkmath.cpp
