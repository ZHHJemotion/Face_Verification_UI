#ifndef FACEDETECTION_H
#define FACEDETECTION_H

#include <QObject>
#include <QImage>
#include <QCoreApplication>
#include "MyOpenCV.h"

#include <dlib/opencv.h>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/legacy/compat.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>

#include <string.h>
#include <string>
#include <time.h>
#include <fstream>
#include <iostream>

using namespace dlib;
using namespace cv;
using namespace std;


class FaceDetection: public QObject
{
    Q_OBJECT
public:
    explicit FaceDetection();
    ~FaceDetection();

public:
    array2d<rgb_pixel> LandmarkDetection(array2d<rgb_pixel>& image);
    array2d<rgb_pixel> FaceAlignment(array2d<rgb_pixel>& image);

};

#endif // FACEDETECTION_H
