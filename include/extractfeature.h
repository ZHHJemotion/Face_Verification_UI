#ifndef EXTRACTFEATURE_H
#define EXTRACTFEATURE_H

#include <opencv.hpp>

using namespace cv;
using namespace std;

// give a face, return a container "vector<float>"
std::vector<float> ExtractFeature(Mat FaceROI_1, Mat FaceROI_2);
void CaffePredefine();

#endif // EXTRACTFEATURE_H
