TEMPLATE=subdirs
CONFIG += ordered

#QMAKE_CXXFLAGS = "-std=c++11"

SUBDIRS = \
    ctk \
    utils/filesys
#    unittests \
#    benchmark/matrices \
#    benchmark/primenumbers \
#    demos/demimg \
#    demos/video_rotations

unittests.depends = ctk
matrices.depends = ctk
primenumbers.depends = ctk
