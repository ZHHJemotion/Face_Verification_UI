#-------------------------------------------------
#
# Project created by QtCreator 2017-08-08
#
#-------------------------------------------------

QT       += core gui multimedia multimediawidgets
QT += widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Face_Verification_UI
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    MyOpenCV.cpp \
    PathManage.cpp \
    MyGlobal.cpp \
    MyIO.cpp \
    extractfeature.cpp \
    facelandmarkdetection.cpp \
    facealignment.cpp

HEADERS  += mainwindow.h \
    MyOpenCV.h \
    PathManage.h \
    MyGlobal.h \
    MyIO.h \
    caffememorylayer.h \
    extractfeature.h \
    facelandmarkdetection.h \
    facealignment.h

FORMS    += mainwindow.ui


#------------------------------------------------
#
# the path of dlib and opencv
#
#------------------------------------------------
INCLUDEPATH += /usr/local/Cellar/dlib/19.4/include
LIBS += -L/usr/local/Cellar/dlib/19.4/lib/
LIBS += -L/usr/lib\
     -lblas\
     -lcblas\
     -lclapack\
     -lpthread\
     -L/usr/local/lib\
     -ldlib\
     -lpng\
     -ljpeg\

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

LIBS += -L/usr/local/lib
LIBS += -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_contrib -lopencv_legacy -lopencv_objdetect -lopencv_flann -lopencv_features2d -v

#------------------------------------------------
#
# the path of caffe
#
#------------------------------------------------
DEFINES += CPU_ONLY

INCLUDEPATH += /Users/zhangxingjian/caffe-face/include
INCLUDEPATH += /Users/zhangxingjian/caffe-face/include/caffe/layers
INCLUDEPATH += /Users/zhangxingjian/caffe-face/src/caffe/proto
INCLUDEPATH += /usr/local/include/boost
INCLUDEPATH += /usr/local/include/gflags
INCLUDEPATH += /usr/local/include/glog
INCLUDEPATH += /usr/local/include/leveldb

LIBS += -L/Users/zhangxingjian/caffe-face/build/lib\
     -lcaffe\

LIBS += -L/usr/local/lib\
     -lcblas\
     -lboost_system\
     -lglog\
     -lgflags\
     -lprotobuf\
     -lleveldb\
     -lsnappy\
     -lswscale\
     -llmdb\
     -lhdf5_hl\
     -lhdf5\
     -lm\
     -lstdc++\

INCLUDEPATH +=/usr/include/python2.7/
INCLUDEPATH +=/usr/include/
LIBS += -lboost_python -lpython2.7

DISTFILES += \
    ../../../wallpaper/tim-trad-191574.jpg
