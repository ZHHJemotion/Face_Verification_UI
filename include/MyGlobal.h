#ifndef MYGLOBAL_H
#define MYGLOBAL_H
#include <QObject>
#include "PathManage.h"

class MyGlobal : public QObject
{
    Q_OBJECT
public:
    explicit MyGlobal(QObject *parent = 0); // constructor
    ~MyGlobal();                           // destructor

public:
    static bool init();                    // initialize programm

public:
    static QString pathOriginalImage;      // the path of the original face images
    static QString pathFaceLandmarkImage;  // the path of the face landmark detection imaegs
    static QString pathFaceAlignmentImage; // the path of the aligned face images

};

#endif // MYGLOBAL_H
