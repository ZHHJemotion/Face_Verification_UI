#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/legacy/compat.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    cv::Mat orgImage1;
    cv::Mat orgImage2;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_LoadingFace1_clicked();

    void on_LoadingFace2_clicked();

    void on_START_clicked();

    void on_originalFaceShow_clicked();

    void on_faceLandmarkDetection_clicked();

    void on_faceAlignment_clicked();

    void on_QUIT_clicked();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
