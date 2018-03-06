#include <QCoreApplication>
#include <QDebug>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/legacy/compat.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>

using namespace cv;
using namespace std;


// declaring the global functions
Mat getVideoFrame(VideoCapture cap, bool isShowImage);
void faceDetection(Mat frame, int currentFrame);
Mat faceRotation(Mat srcImage, Mat dstImage);


// the global variables
// Copy this file from opencv/data/haarscascades to target folder (it is very important!!!)
string face_cascade_name = "/Users/Desktop/Programming/C++/face_detection/haarcascade_frontalface/haarcascade_frontalface_alt.xml";
//string face_cascade_name = "/Users/Desktop/Programming/C++/face_detection/haarcascade_frontalface/haarcascade_frontalface_alt2.xml";
CascadeClassifier faceCascade;


/************************************************************************************
 * name: getVideoFrame
 * input: VideoCapture cap -- the video to be read
 *        bool isShowImage -- if show the image to the window
 * output: frame -- return a frame of the video
 * function: get the single frame from the given video link
 *
 ************************************************************************************/
Mat getVideoFrame(VideoCapture cap, bool isShowImage)
{
    // ---------------------------------------------------
    //  load a frame of video into the output vector
    // ---------------------------------------------------
    Mat frame;
    cap >> frame;

    bool success = cap.read(frame);
    // exception handling
    if(!success)
    {
        printf("Cannot read frame!!!");
        exit(EXIT_FAILURE);
    }

    // ----------------------------------------------------------------------
    //  get the current frame and the index,
    //  then show the current frame in a window
    // ----------------------------------------------------------------------
    if(isShowImage)
    {
        double posFrame = cap.get(CV_CAP_PROP_POS_FRAMES);
        auto temp = std::to_string(posFrame); // changing into string form
        std::cout << temp + " frame" << endl;
        string windowName = temp + " frame";

        namedWindow(windowName, WINDOW_AUTOSIZE);
        imshow(windowName, frame);
    }

    /*
    if(waitKey(0) == 27) // 27 means "esc"
    {
        exit(EXIT_SUCCESS);
    }
    */

    return frame;

    /*
    // -------------------------------------------------------
    // TEST CODE
    // read the single frame by type the number of the frame
    // -------------------------------------------------------
    double frameNumber = cap.get(CV_CAP_PROP_FRAME_COUNT); // get the number of the frames
    std::cout << "frame count = " << frameNumber << endl;

    for(;;)
    {
        Mat frame;
        double frameIndex;

        std::cout << "frame index ?";
        std::cin >> frameIndex;
        if(frameIndex < 0 || frameIndex >= frameNumber) //check if inside the video's frame
        {
            break;
        }

        cap.set(CV_CAP_PROP_POS_FRAMES, frameIndex);
        bool success = cap.read(frame);
        if(!success)
        {
            printf("Cannot read frame!!!");
            break;
        }

        namedWindow("the frame", WINDOW_AUTOSIZE);
        imshow("the frame", frame);
    }
    */

}



/************************************************************************************
 * function name:  faceRotation
 * input: Mat srcImage        -- the image to be processed
 * output: dstImage
 * function: face rotating 90° of each captured picture before face detection
 *
 ************************************************************************************/
Mat faceRotation(Mat srcImage, Mat dstImage)
{
    // exception handling
    if (!srcImage.data)
    {
        printf("Error in reading image!!!\n");
        exit(EXIT_FAILURE);
    }

    // the image of the transpose
    Mat transposeImage;

    // =====================================
    // 1. transpose
    // =====================================
    transpose(srcImage, transposeImage);

    // =====================================
    // 2. flip to get the rotated 90° picture
    // =====================================
    flip(transposeImage, dstImage, 1);

    if (!dstImage.data)
    {
        printf("The error in the image after transformation!!!\n");
        exit(EXIT_FAILURE);
    }

}




/************************************************************************************
 * function name:  faceDetection
 * input: Mat frame        -- the image to be processed
 *        int currentFrame -- the index of current image
 * output: void
 * function: face detecting at each frame of video and saving the captured faces
 *
 ************************************************************************************/
void faceDetection(Mat frame, int currentFrame)
{
    //Q_UNUSED (currentFrame); // unused the parameter currentFrame
    // decalreing the local variables
    std::vector<Rect> faces;
    Mat grayFrame;
    Mat crop;
    Mat res;
    Mat gray;
    string text;
    stringstream sstm;

    cvtColor(frame, grayFrame, COLOR_BGR2GRAY);
    //equalizeHist(grayFrame, grayFrame); // equalization operation to the grayscale

    // ==================================================
    // 1. detect faces
    // ==================================================
    faceCascade.detectMultiScale(grayFrame, faces, 1.2, 2, 0 | CASCADE_SCALE_IMAGE, Size(30,30));

    // ==================================================
    // 2. set region of interest(ROI) to draw the rectangle to get the detected faces
    // ==================================================
    cv::Rect roi_b;
    cv::Rect roi_c;

    size_t ic = 0; // ic is the index of current element
    int ac = 0; // ac is the area of current element

    size_t ib = 0; // ib is the index of the biggest element
    int ab = 0; // ab is the area of the biggest element

    // ==================================================
    // 3. iterate through all current elements(detecte faces)
    // ==================================================
    for(ic = 0; ic < faces.size(); ic++)
    {
        // 3.1 get the area of current and biggest element
        // -------------------------------------------
        roi_c.x = faces[ic].x;
        roi_c.y = faces[ic].y;
        roi_c.width = (faces[ic].width);
        roi_c.height = (faces[ic].height);
        // get the area of current element(detect faces)
        ac = roi_c.width * roi_c.height;

        roi_b.x = faces[ib].x;
        roi_b.y = faces[ib].y;
        roi_b.width = (faces[ib].width);
        roi_b.height = (faces[ib].height);
        // get the area of the biggest element
        // at beginning it is same as "current" element
        ab = roi_b.width * roi_b.height;

        // doing the substitution
        // if the area of the current element is bigger than the area of the biggest element
        if(ac > ab)
        {
            ib = ic;
            roi_b.x = faces[ib].x;
            roi_b.y = faces[ib].y;
            roi_b.width = (faces[ib].width);
            roi_b.height = (faces[ib].height);
        }

//        // form a filename
//        filename = "";
//        stringstream ssfn;
//        ssfn << filename << ".png";
//        filename = ssfn.str();
//        filenumber++;

//        imwrite(filename, gray);

        // 3.2 doing the cropping operation and resizing
        // ---------------------------------------------------
        crop = frame(roi_b);
        resize(crop, res, Size(512,512), 0, 0, INTER_LINEAR); // will be used while saving images to size 512x512
        cvtColor(crop, gray, CV_BGR2GRAY); // convert cropped image to grayscale

        // 3.3 display the detected faces
        // ---------------------------------------------------
        Point pt1(faces[ic].x, faces[ic].y);
        Point pt2((faces[ic].x + faces[ic].height), (faces[ic].y + faces[ic].width));
        rectangle(frame, pt1, pt2, Scalar(0, 255, 0), 2, 8, 0);
    }

    // ==================================================
    // 4. show the image
    //    can use the parameter currentFrame to name the window
    // ==================================================
    sstm << "Crop area size: " << roi_b.width << "x" << roi_b.height ; // get the cropped area size
    text = sstm.str();

    // the type of the text on the image
    putText(frame, text, cvPoint(30,30), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0, 0, 255), 1, CV_AA);
    //namedWindow("original", WINDOW_AUTOSIZE);
    //imshow("original", frame);

    string currentFrameNumber = to_string(currentFrame);
    string filename = currentFrameNumber + ".png";
    string filePath = "/Users/zhangxingjian/Desktop/Programming/C++/face_detection/saveImage/boy/Parker1/Parker - ";
    string savePath = filePath + filename;

    if(!crop.empty())
    {
        namedWindow("detected", WINDOW_AUTOSIZE);
        imshow("detected", crop);
        // write the image
        imwrite(savePath, res);
    }
    else
    {
        destroyWindow("detected");
    }
}



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    string videoPath = "/Users/zhangxingjian/Downloads/Daily Photo Time Lapse of Parker 1 month - 2 years.mp4";
    //string videoPath = "/Users/zhangxingjian/Desktop/Programming/C++/face_detection/0 to 10 in 60 Seconds.mp4";

    // =======================================
    // 1. load video
    // =======================================
    VideoCapture cap(videoPath);
    //exception handling to check if read the video successfully
    if(!cap.isOpened())
    {
        printf("Cannot open the video file!");
    }

    double frameCount = cap.get(CV_CAP_PROP_FRAME_COUNT);
    printf("the frame count of this video is %f \n", frameCount);

    int currentFrame = 0;

    while(1)
    {
        // =======================================
        // 2. read frame from this video
        // =======================================
        Mat frame = getVideoFrame(cap, false);

        // rotate the each frame 90°
        //Mat frameRotation;
        //faceRotation(frame, frameRotation);

        currentFrame ++;
        std::cout << "current processed frame is " << currentFrame << endl;


        if(waitKey(10) == 27) // 27 means "esc"
        {
            exit(EXIT_SUCCESS);
        }

        // =======================================
        // 3. face detection in this frame
        // =======================================

        // 3.1. load the cascade
        // ---------------------------------------
        // exception handling
        if(!faceCascade.load(face_cascade_name))
        {
            printf("Error loading!");
            return false;
        }


        // exception handling
        if(!frame.empty())
        {
            // rotate the each frame 90°
            //transpose(frame, frame);
            //flip(frame, frame, 1);

            faceDetection(frame, currentFrame);
        }
        else
        {
            printf("Error! No captured frame!");
            return false;
        }

        if(cap.get(CV_CAP_PROP_POS_FRAMES) == cap.get(CV_CAP_PROP_FRAME_COUNT))
        {
            // if the number of captured frames is equal to the total number of frames
            // we stop
            break;
        }
    }

    /*
    VideoCapture cap(0);
    if(!cap.isOpened()){
            return -1;
    }
    Mat frame;

    while(true){
        cap>>frame;
        imshow("the video", frame);
        //qDebug("the third step has a error!");
        if(waitKey(30) >= 0) break;
    */

    waitKey(0);

    return a.exec();
}
