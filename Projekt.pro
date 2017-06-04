#-------------------------------------------------
#
# Project created by QtCreator 2017-03-02T22:03:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Projekt
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    video.cpp

HEADERS  += mainwindow.h \
    video.h

FORMS    += mainwindow.ui

INCLUDEPATH += C:\opencv-build\install\include
LIBS += -LC:\opencv-build\install\x86\mingw\lib \
    -lopencv_core320.dll \
    -lopencv_highgui320.dll \
    -lopencv_imgcodecs320.dll \
    -lopencv_imgproc320.dll \
    -lopencv_features2d320.dll \
    -lopencv_calib3d320.dll  \
    -lopencv_videoio320.dll \
    -lopencv_video320.dll
