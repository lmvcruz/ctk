TEMPLATE=subdirs
CONFIG += ordered

#QMAKE_CXXFLAGS = "-std=c++11"

SUBDIRS = \
    ctk \
    utils/filesys \
    ctkunittests \
#    benchmark/matrices \
#    benchmark/image \
#    benchmark/primenumbers \
#    demos/demimg \
#    demos/video_rotations

ctkunittests.depends = ctk
#matrices.depends = ctk
#primenumbers.depends = ctk
