######################################################################
# Automatically generated by qmake (3.0) Wed Mar 30 09:25:49 2016
######################################################################

TEMPLATE = app
TARGET = Cube
INCLUDEPATH += .

INCLUDEPATH += /usr/local/include/opencv
LIBS += -L/usr/local/lib -lopencv_shape -lopencv_stitching -lopencv_objdetect -lopencv_superres -lopencv_videostab -lopencv_calib3d -lopencv_features2d -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_video -lopencv_photo -lopencv_ml -lopencv_imgproc -lopencv_flann -lopencv_core -lopencv_hal

CONFIG += c++11
# Input
HEADERS += \
           getsegments.h \
           imadjust.h \
           mark.h \
           segment.h \
           templatematch.h \
    configuration.h
SOURCES += \
           getsegments.cpp \
           imadjust.cpp \
           main.cpp \
           mark.cpp \
           segments.cpp \
           templatematch.cpp
