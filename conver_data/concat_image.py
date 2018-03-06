# coding=utf-8
import cv2
import numpy as np
import caffe

def concat_image():

    img1 = cv2.imread("/Users/Desktop/Programming/C++/Face_Verification_UI/data/faceAlignment/073A04Gf_aligned.png")
    img2 = cv2.imread("/Users/Desktop/Programming/C++/Face_Verification_UI/data/faceAlignment/075A06_aligned.png")

    img1 = np.float64(img1)
    img1 = img1[:, :, (2, 1, 0)]
    img1 = img1.transpose((2, 0, 1))

    img2 = np.float64(img2)
    img2 = img2[:, :, (2, 1, 0)]
    img2 = img2.transpose((2, 0, 1))

    img = np.concatenate(img1, img2)

    datum = caffe.io.array_to_datum(img, label=None)

    # cv2.imwrite("/Users/Desktop/Programming/C++/Face_Verification_UI/data/faceAlignment/concat_face.png",
    #            img, [int(cv2.IMWRITE_PNG_COMPRESSION), 0])

    return datum

concat_image()