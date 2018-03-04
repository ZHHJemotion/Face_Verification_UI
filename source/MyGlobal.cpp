#include <QDebug>
#include <QLibrary>
#include "MyGlobal.h"

QString MyGlobal::pathOriginalImage = NULL;
QString MyGlobal::pathFaceLandmarkImage = NULL;
QString MyGlobal::pathFaceAlignmentImage = NULL;

MyGlobal::MyGlobal(QObject *parent):QObject(parent)
{

}

MyGlobal::~MyGlobal()
{

}

bool MyGlobal::init()
{
    // 1. define the paths of data
    // -----------------------------------------------
    pathOriginalImage = PathManage::makePathStr("/Users/zhangxingjian/Desktop/Programming/C++/Face_Verification_UI/data/originalFace/");
    pathFaceLandmarkImage = PathManage::makePathStr("/Users/zhangxingjian/Desktop/Programming/C++/Face_Verification_UI/data/faceLandmarkDetection/");
    pathFaceAlignmentImage = PathManage::makePathStr("/Users/zhangxingjian/Desktop/Programming/C++/Face_Verification_UI/data/faceAlignment/");

    // 2. create the paths of data
    // -----------------------------------------------
    PathManage::mkPath(pathOriginalImage);
    PathManage::mkPath(pathFaceLandmarkImage);
    PathManage::mkPath(pathFaceAlignmentImage);

    return true;
}
