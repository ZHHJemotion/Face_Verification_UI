#include "facealignment.h"

Mat FaceAlignment(Mat org)
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

        shapes.push_back(shape);
    }

    // align and crop face depend on the landmark
    dlib::array<array2d<rgb_pixel> > face_chips;
    extract_image_chips(img, get_face_chip_details(shapes), face_chips);

    // resize the aligned and cropped face
    array2d<rgb_pixel> face_save(128,128);
    resize_image(tile_images(face_chips), face_save);
    Mat temp = dlib::toMat(face_save);

    return temp;
}
