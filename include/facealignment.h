#ifndef FACEALIGNMENT_H
#define FACEALIGNMENT_H

#include <dlib/opencv.h>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/image_transforms.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <dlib/graph_utils.h>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/legacy/compat.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>

#include <string>
#include <unistd.h> // for sleep()
#include <QDebug>

using namespace dlib;
using namespace cv;
using namespace std;

// predefine
Mat FaceAlignment(Mat org);

#endif // FACEALIGNMENT_H
