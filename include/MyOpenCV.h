#ifndef MYOPENCV_H
#define MYOPENCV_H

#include <QObject>
#include <QImage>
#include <QCoreApplication>

#include <dlib/opencv.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/legacy/compat.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>

using namespace dlib;
using namespace cv;

class MyOpenCV: public QObject
{
    Q_OBJECT
public:
    explicit MyOpenCV();
    ~MyOpenCV();

public:
    //void QImageShow(QImage& qImage);
    void Mat2QImageShow(QString& imagePath);
    QImage Mat2QImage(const Mat& mat);
    void QImage2MatShow(QImage& image);
    Mat QImage2Mat(QImage image);
    array2d<rgb_pixel> Mat2Array2d(const Mat& mat);
    array2d<unsigned char> Mat2Array2dGray(const Mat& mat);
};

#endif // MYOPENCV_H
