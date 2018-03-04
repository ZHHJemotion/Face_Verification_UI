# --------------------------------------------------------------
#
#  the face detection on the online video
#
# --------------------------------------------------------------


QT += core
QT -= gui

CONFIG += c++11

TARGET = face_detection
CONFIG += console
CONFIG -= app_bundle

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

SOURCES += main.cpp

INCLUDEPATH += /usr/local/include
INCLUDEPATH += /usr/local/include/opencv/
INCLUDEPATH += /usr/local/include/opencv2/

LIBS += -L/usr/local/lib/
     -lopencv_core
     -lopencv_highgui
     -lopencv_imgproc
     -lopencv_video
     -lopencv_contrib
     -lopencv_legacy
     -lopencv_flann
     -lopencv_features2d
     -lopencv_objdetect

LIBS += -L/usr/local/lib/
LIBS += -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_contrib -lopencv_legacy -lopencv_objdetect -lopencv_flann -lopencv_features2d -v

