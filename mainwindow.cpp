#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QImage>
#include <QDir>
#include <QUrl>
#include <QMessageBox>
#include <QDesktopServices>
#include <QFileDialog>
#include "MyGlobal.h"
#include "MyOpenCV.h"
#include "PathManage.h"
#include "extractfeature.h"
#include "facelandmarkdetection.h"
#include "facealignment.h"

#include <dlib/opencv.h>
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
#include <time.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unistd.h> // for sleep()

using namespace dlib;
using namespace cv;
using namespace std;

#define faceFile string("/Users/Desktop/master thesis paper/Face_Verification_UI/data/originalFace/")
#define orgFile string("/Users/Desktop/Programming/C++/Face_Verification_UI/data/originalFace/")
#define landmarkFile string("/Users/Desktop/Programming/C++/Face_Verification_UI/data/faceLandmarkDetection/")
#define alignFile string("/Users/Desktop/Programming/C++/Face_Verification_UI/data/faceAlignment/")

//#define image_1 string("075A05.png")
//#define image_2 string("079A04.png")

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Mat orgImage1;
    Mat orgImage2;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_LoadingFace1_clicked()
{
    QString path = QString::fromStdString(faceFile);

    //Open file and return the file path
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), path, "Images (*.png)");
    //qDebug() << imagePath;

    if (fileName.isNull())
    {
       // if user didn't choose image
       QMessageBox::information(this, "Document", "No image", QMessageBox::Ok | QMessageBox::Cancel);
    }

    std::string imagePath1(fileName.toStdString());  // Qstring to string

    MyOpenCV face;

    orgImage1 = imread(imagePath1);
    if(!orgImage1.data)
    {
        qDebug() << "ERROR: Can not load the original image.";
    }

    // convert Mat to QImage
    QImage srcImg1 = face.Mat2QImage(orgImage1);

    // show the original face
    srcImg1.scaled(QSize(),Qt::KeepAspectRatio);
    ui->original_face1->setPixmap(QPixmap::fromImage(srcImg1));
    ui->original_face1->setScaledContents(true);
}

void MainWindow::on_LoadingFace2_clicked()
{
    QString path = QString::fromStdString(faceFile);

    //Open file and return the file path
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), path, "Images (*.png)");
    //qDebug() << imagePath;

    if (fileName.isNull())
    {
       // if user didn't choose image
       QMessageBox::information(this, "Document", "No image", QMessageBox::Ok | QMessageBox::Cancel);
    }

    std::string imagePath2(fileName.toStdString()); // Qstring to string

    MyOpenCV face;

    orgImage2 = imread(imagePath2);
    if(!orgImage2.data)
    {
        qDebug() << "ERROR: Can not load the original image.";
    }

    // convert Mat to QImage
    QImage srcImg2 = face.Mat2QImage(orgImage2);

    // show the original face
    srcImg2.scaled(QSize(),Qt::KeepAspectRatio);
    ui->original_face2->setPixmap(QPixmap::fromImage(srcImg2));
    ui->original_face2->setScaledContents(true);

}


void MainWindow::on_START_clicked()
{
    MyGlobal path;
    path.init();

    // ========================================================
    // define a global class object of MyOpenCV
    // ========================================================
    MyOpenCV face;

    // ========================================================
    // 1. show the original face image
    // ========================================================
    //Mat orgImage1 = imread(orgFile + image_1, 1);
    //Mat orgImage2 = imread(orgFile + image_2, 1);

    if(!orgImage1.data || !orgImage2.data)
    {
        qDebug() << "ERROR: Can not load the original image.";
    }

    // convert Mat to QImage
    //QImage srcImg1 = face.Mat2QImage(orgImage1);
    //QImage srcImg2 = face.Mat2QImage(orgImage2);

    // show the original face
    //srcImg1.scaled(QSize(),Qt::KeepAspectRatio);
    //ui->original_face1->setPixmap(QPixmap::fromImage(srcImg1));
    //ui->original_face1->setScaledContents(true);

    //srcImg2.scaled(QSize(),Qt::KeepAspectRatio);
    //ui->original_face2->setPixmap(QPixmap::fromImage(srcImg2));
    //ui->original_face2->setScaledContents(true);


    // ========================================================
    // 2. face landmark detection
    // ========================================================

    // detect the 1st face
    // ------------------------------------------------------
    // define a face detector
    frontal_face_detector detector = get_frontal_face_detector();

    // define a shape predictor, used to predict the face landmark of a given image
    // using shape_predictor_68_face_landmarks.dat to load model
    shape_predictor sp;
    deserialize("/Users/zhangxingjian/dlib/examples/build/shape_predictor_68_face_landmarks.dat") >> sp;

    // convet Mat to array2d<rgb_pixel> using with dlib
    array2d<rgb_pixel> img1, img2;
    assign_image(img1, cv_image<rgb_pixel>(orgImage1));
    assign_image(img2, cv_image<rgb_pixel>(orgImage2));

    // amplify the image to detect some smalller face so easily
    pyramid_up(img1);
    pyramid_up(img2);

    // detect 1st face to get the shape
    // ------------------------------------------------------
    std::vector<dlib::rectangle> dets1 = detector(img1);
    cout << "Number of faces detected: " << dets1.size() << endl;
    if(dets1.size() == 0)
    {
        qDebug() << "ERROR: can not detect face.";
    }

    // using the shape_predictor to show the pose of each detected face
    std::vector<full_object_detection> shapes;
    for (unsigned long j = 0; j < dets1.size(); ++j)
    {
        // predictor the pose
        full_object_detection shape1 = sp(img1, dets1[j]);

        for(int i = 0; i < 68; i++)
        {
            // draw the 68 facial landmark points onto face
            draw_solid_circle(img1, shape1.part(i), 5, rgb_pixel(0,255,0));
        }

        shapes.push_back(shape1);
    }

    Mat landmarkTemp1 = dlib::toMat(img1);

    //Mat landmarkTemp1 = FaceLandmarkDetection(orgImage1);
    //imwrite(landmarkFile + image_1, landmarkTemp1);

    QImage faceLandmark1 = face.Mat2QImage(landmarkTemp1);
    faceLandmark1.scaled(QSize(),Qt::KeepAspectRatio);  // scale the face into the window
    ui->landmark1->setPixmap(QPixmap::fromImage(faceLandmark1));
    ui->landmark1->setScaledContents(true);


    // detect the 2nd face
    // ------------------------------------------------------
    // detect 2nd face to get the shape
    // ------------------------------------------------------
    std::vector<dlib::rectangle> dets2 = detector(img2);
    cout << "Number of faces detected: " << dets2.size() << endl;
    if(dets2.size() == 0)
    {
        qDebug() << "ERROR: can not detect face.";
    }

    // using the shape_predictor to show the pose of each detected face
    //std::vector<full_object_detection> shapes2;
    for (unsigned long j = 0; j < dets2.size(); ++j)
    {
        // predictor the pose
        full_object_detection shape2 = sp(img2, dets2[j]);

        for(int i = 0; i < 68; i++)
        {
            // draw the 68 facial landmark points onto face
            draw_solid_circle(img2, shape2.part(i), 5, rgb_pixel(0,255,0));
        }

        shapes.push_back(shape2);
    }

    Mat landmarkTemp2 = dlib::toMat(img2);
    //Mat landmarkTemp2 = FaceLandmarkDetection(orgImage2);
    //imwrite(landmarkFile + image_2, landmarkTemp2);

    QImage faceLandmark2 = face.Mat2QImage(landmarkTemp2);
    faceLandmark2.scaled(QSize(),Qt::KeepAspectRatio);
    ui->landmark2->setPixmap(QPixmap::fromImage(faceLandmark2));
    ui->landmark2->setScaledContents(true);


    // ========================================================
    // 3. face alignment
    // ========================================================

    // the 1st face alignment
    // ------------------------------------------------------
    Mat chipTemp1 = FaceAlignment(orgImage1);
    //imwrite(alignFile + image_1, chipTemp1);

    QImage chipImg1 = face.Mat2QImage(chipTemp1);
    chipImg1.scaled(QSize(),Qt::KeepAspectRatio);
    ui->aligned_face1->setPixmap(QPixmap::fromImage(chipImg1));
    ui->aligned_face1->setScaledContents(true);

    // the 2nd face alignment
    // ------------------------------------------------------
    Mat chipTemp2 = FaceAlignment(orgImage2);
    //imwrite(alignFile + image_2, chipTemp2);

    QImage chipImg2 = face.Mat2QImage(chipTemp2);
    chipImg2.scaled(QSize(),Qt::KeepAspectRatio);
    ui->aligned_face2->setPixmap(QPixmap::fromImage(chipImg2));
    ui->aligned_face2->setScaledContents(true);


    // ==========================================================
    // 4.CNN caffe deploy
    // ==========================================================
    CaffePredefine();
    std::vector<float> result; // define a vector to save the result
    if (!chipTemp1.empty() || !chipTemp2.empty())
    {
        ui->prob_value->clear();

        unsigned long i;
        result = ExtractFeature(chipTemp1, chipTemp2);
        for(i = 0; i < result.size(); i++)
        {
            cout << result[i] <<endl;
            QLocale chinese(QLocale::Chinese, QLocale::China);
            QString prob = chinese.toString(result[i], 'f');
            ui->prob_value->append(prob);
        }
    }


    // ==========================================================
    // 5. show the result of verification
    // ==========================================================
    if(result.size() == 2)
    {
        // result[0] > result[1] -> different
        // result[1] < result[1] -> same
        if(result[0] > result[1])
        {
            ui->Verification_Result->setText("They are two different children!");
        }
        else if(result[0] < result[1])
        {
            ui->Verification_Result->setText("It's a same kid!");
        }
        else
        {
            qDebug() << "ERROR: cannot verify these two faces to belong the same person or not.";
        }
    }
    else
    {
        qDebug() << "ERROR: the number of category must be 2.";
    }
}



void MainWindow::on_originalFaceShow_clicked()
{
    // define a global class object of MyOpenCV
    // ------------------------------------------------------
    MyOpenCV face;

    //Mat orgImage1 = imread(orgFile + image_1, 1);
    //Mat orgImage2 = imread(orgFile + image_2, 1);

    if(!orgImage1.data || !orgImage2.data)
    {
        qDebug() << "ERROR: Can not load the original image.";
    }

    // convert Mat to QImage
    QImage srcImg1 = face.Mat2QImage(orgImage1);
    QImage srcImg2 = face.Mat2QImage(orgImage2);

    // show the original face
    srcImg1.scaled(QSize(),Qt::KeepAspectRatio);
    ui->original_face1->setPixmap(QPixmap::fromImage(srcImg1));
    ui->original_face1->setScaledContents(true);

    srcImg2.scaled(QSize(),Qt::KeepAspectRatio);
    ui->original_face2->setPixmap(QPixmap::fromImage(srcImg2));
    ui->original_face2->setScaledContents(true);
}

void MainWindow::on_faceLandmarkDetection_clicked()
{
    // define a global class object of MyOpenCV
    // ------------------------------------------------------
    MyOpenCV face;

    //Mat orgImage1 = imread(orgFile + image_1, 1);
    //Mat orgImage2 = imread(orgFile + image_2, 1);

    if(!orgImage1.data || !orgImage2.data)
    {
        qDebug() << "ERROR: Can not load the original image.";
    }

    // detect the 1st face
    // ------------------------------------------------------
    Mat landmarkTemp1 = FaceLandmarkDetection(orgImage1);

    QImage faceLandmark1 = face.Mat2QImage(landmarkTemp1);
    faceLandmark1.scaled(QSize(),Qt::KeepAspectRatio);
    ui->landmark1->setPixmap(QPixmap::fromImage(faceLandmark1));
    ui->landmark1->setScaledContents(true);

    // detect the 2nd face
    // ------------------------------------------------------
    Mat landmarkTemp2 = FaceLandmarkDetection(orgImage2);

    QImage faceLandmark2 = face.Mat2QImage(landmarkTemp2);
    faceLandmark2.scaled(QSize(),Qt::KeepAspectRatio);
    ui->landmark2->setPixmap(QPixmap::fromImage(faceLandmark2));
    ui->landmark2->setScaledContents(true);
}

void MainWindow::on_faceAlignment_clicked()
{
    // define a global class object of MyOpenCV
    // ------------------------------------------------------
    MyOpenCV face;

    //Mat orgImage1 = imread(orgFile + image_1, 1);
    //Mat orgImage2 = imread(orgFile + image_2, 1);

    if(!orgImage1.data || !orgImage2.data)
    {
        qDebug() << "ERROR: Can not load the original image.";
    }

    // the 1st face alignment
    // ------------------------------------------------------
    Mat chipTemp1 = FaceAlignment(orgImage1);
    //imwrite(alignFile + string("073A06Gf_aligned.png"), chipTemp1);

    QImage chipImg1 = face.Mat2QImage(chipTemp1);
    chipImg1.scaled(QSize(),Qt::KeepAspectRatio);
    ui->aligned_face1->setPixmap(QPixmap::fromImage(chipImg1));
    ui->aligned_face1->setScaledContents(true);

    // the 2nd face alignment
    // ------------------------------------------------------
    Mat chipTemp2 = FaceAlignment(orgImage2);
    //imwrite(alignFile + string("075A06_aligned.png"), chipTemp2);

    QImage chipImg2 = face.Mat2QImage(chipTemp2);
    chipImg2.scaled(QSize(),Qt::KeepAspectRatio);
    ui->aligned_face2->setPixmap(QPixmap::fromImage(chipImg2));
    ui->aligned_face2->setScaledContents(true);

}

void MainWindow::on_QUIT_clicked()
{
    close();
}

