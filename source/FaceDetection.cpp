#include <QDebug>
#include "FaceDetection.h"

FaceDetection::FaceDetection()
{

}

FaceDetection::~FaceDetection()
{

}

array2d<rgb_pixel> FaceDetection::LandmarkDetection(array2d<rgb_pixel> &image)
{
    // define a face detector
    frontal_face_detector detector = get_frontal_face_detector();

    // define a shape predictor, used to predict the face landmark of a given image
    // using shape_predictor_68_face_landmarks.dat to load model
    shape_predictor sp;
    deserialize("/Users/dlib/examples/build/shape_predictor_68_face_landmarks.dat") >> sp;

    image_window win, win_face;

    //array2d<rgb_pixel> image;

    //load_image(image, "//");

    // amplify the image to detect some smalller face so easily
    pyramid_up(image);

    // detect the face to get the shape
    std::vector<dlib::rectangle> dets = detector(image);

    // using the shape_predictor to show the pose of each detected face
    std::vector<full_object_detection> shapes;
    for (unsigned long j = 0; j < dets.size(); ++j)
    {
        // predictor the pose
        full_object_detection shape = sp(image, dets[j]);

        shapes.push_back(shape);
    }

    // show the result of detection !!!!!!!!!!
    win.clear_overlay();
    win.set_image(image);
    win.add_overlay(dets, rgb_pixel(255, 0, 0));
    win.add_overlay(render_face_detections(shapes));

    // align and crop a face depend on the landmark !!!!!!!!!!
    dlib::array<array2d<rgb_pixel> > face_chips;
    extract_image_chips(image, get_face_chip_details(shapes), face_chips);
    win_faces.set_image(tile_images(face_chips));

    //save_png(tile_images(face_chips), "/Users/Desktop/Programming/Python/Conver_Data/detected.png");

    return shapes;
}

array2d<rgb_pixel> FaceDetection::FaceAlignment(array2d<rgb_pixel> &image)
{
    shapes = array2d<rgb_pixel> FaceDetection::LandmarkDetection(array2d<rgb_pixel> image);

    image_window win_faces;

    // align and crop a face depend on the landmark
    dlib::array<array2d<rgb_pixel> > face_chips;
    extract_image_chips(image, get_face_chip_details(shapes), face_chips);
    win_faces.set_image(tile_images(face_chips));

    return face_chips;
}
