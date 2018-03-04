#include<QDebug>
#include "MyOpenCV.h"

MyOpenCV::MyOpenCV()
{

}

MyOpenCV::~MyOpenCV()
{

}

QImage MyOpenCV::Mat2QImage(const Mat& mat)
{
    // 8-bits unsigned, NO. OF CHANNELS = 1
    if(mat.type() == CV_8UC1)
    {
        QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
        // Set the color table (used to translate colour indexes to qRgb values)
        image.setColorCount(256);
        for(int i = 0; i < 256; i++)
        {
            image.setColor(i, qRgb(i, i, i));
        }
        // Copy input Mat
        uchar *pSrc = mat.data;
        for(int row = 0; row < mat.rows; row ++)
        {
            uchar *pDest = image.scanLine(row);
            memcpy(pDest, pSrc, mat.cols);
            pSrc += mat.step;
        }
        return image;
    }
    // 8-bits unsigned, NO. OF CHANNELS = 3
    else if(mat.type() == CV_8UC3)
    {
        // Copy input Mat
        const uchar *pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        return image.rgbSwapped();
    }
    else if(mat.type() == CV_8UC4)
    {
        qDebug() << "CV_8UC4";
        // Copy input Mat
        const uchar *pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
        return image.copy();
    }
    else
    {
        qDebug() << "ERROR: Mat could not be converted to QImage.";
        return QImage();
    }
}


void MyOpenCV::Mat2QImageShow(QString& imagePath)
{
    //Mat mat = cv::imread(imagePath, IMREAD_UNCHANGED);
    //qimageShow(Mat2QImage(mat), ui->graphicsView_mat);
}

Mat MyOpenCV::QImage2Mat(QImage image)
{
    Mat mat;
    qDebug() << image.format();
    switch(image.format())
    {
    case QImage::Format_ARGB32:
    case QImage::Format_RGB32:
    case QImage::Format_ARGB32_Premultiplied:
        mat = Mat(image.height(), image.width(), CV_8UC4, (void*)image.constBits(), image.bytesPerLine());
        break;
    case QImage::Format_RGB888:
        mat = Mat(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());
        cv::cvtColor(mat, mat, CV_BGR2RGB);
        break;
    case QImage::Format_Indexed8:
        mat = Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine());
        break;
    }
    return mat;
}

void MyOpenCV::QImage2MatShow(QImage& image)
{
    int imageWidth  = image.width();
    int imageHeight = image.height();

    Mat QImg2Mat = QImage2Mat(image);

#if 1
    if ( QImg2Mat.data )
    {
        imshow("QImage to Mat 1", QImg2Mat);
    }
#endif
}

array2d<rgb_pixel> MyOpenCV::Mat2Array2d(const Mat &mat)
{
    // 8-bits unsigned, NO. OF CHANNELS = 3
    if(mat.type() == CV_8UC3)
    {
        array2d<rgb_pixel> dlibImage;
        assign_image(dlibImage, cv_image<rgb_pixel>(mat)); //cv_image<bgr_pixel>
        return dlibImage;
    }
}

array2d<unsigned char> MyOpenCV::Mat2Array2dGray(const Mat &mat)
{
    // 8-bits unsigned, NO. OF CHANNELS = 1
    if(mat.type() == CV_8UC1)
    {
        array2d<unsigned char> dlibGrayImage;
        assign_image(dlibGrayImage, cv_image<unsigned char>(mat));
        return dlibGrayImage;
    }
}
