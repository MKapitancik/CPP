#-------------------------------------------------
#
# Project created by QtCreator 2016-02-21T09:44:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CamDriver
TEMPLATE = app

INCLUDEPATH += /usr/local/include/opencv
LIBS += -L/usr/local/lib -lopencv_shape -lopencv_stitching -lopencv_objdetect -lopencv_superres -lopencv_videostab -lopencv_calib3d -lopencv_features2d -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_video -lopencv_photo -lopencv_ml -lopencv_imgproc -lopencv_flann -lopencv_core -lopencv_hal


SOURCES += main.cpp\
        mainwindow.cpp \
    picam.cpp \
    im2label.cpp

HEADERS  += mainwindow.h \
    picam.h \
    im2label.h

FORMS    += mainwindow.ui
