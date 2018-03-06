#include "facelandmarkdetection.h"

Mat FaceLandmarkDetection(Mat org)
{
    // define a face detector
    frontal_face_detector detector = get_frontal_face_detector();

    // define a shape predictor, used to predict the face landmark of a given image
    // using shape_predictor_68_face_landmarks.dat to load model
    shape_predictor sp;
    deserialize("/Users/dlib/examples/build/shape_predictor_68_face_landmarks.dat") >> sp;

    // convet Mat to array2d<rgb_pixel> using with dlib
    array2d<rgb_pixel> img;
    assign_image(img, cv_image<rgb_pixel>(org));

    // amplify the image to detect some smalller face so easily
    pyramid_up(img);

    // detect face to get the shape
    // ------------------------------------------------------
    std::vector<dlib::rectangle> dets = detector(img);
    cout << "Number of faces detected: " << dets.size() << endl;
    if(dets.size() == 0)
    {
        qDebug() << "ERROR: can not detect face.";
    }

    // using the shape_predictor to show the pose of each detected face
    std::vector<full_object_detection> shapes;
    for (unsigned long j = 0; j < dets.size(); ++j)
    {
        // predictor the pose
        full_object_detection shape = sp(img, dets[j]);

        for(int i = 0; i < 68; i++)
        {
            // draw the 68 facial landmark points onto face
            draw_solid_circle(img, shape.part(i), 5, rgb_pixel(0,255,0));
        }

        shapes.push_back(shape);
    }

    // show the result of detection
    /**********************************
    image_window win;
    win.clear_overlay();
    win.set_image(img);
    win.add_overlay(dets, rgb_pixel(255, 0, 0));  // overlay the detected facial region
    win.add_overlay(render_face_detections(shapes)); // overlay the facial shape contains 68 landmark points
    dlib::sleep(5000);
    **********************************/

    Mat temp = dlib::toMat(img);

    return temp;

}
