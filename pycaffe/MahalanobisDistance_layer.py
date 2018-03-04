import caffe
import numpy as np

class MahalanobisDistanceLayer(caffe.Layer):
    """MahalanonisDistance layer use for calculating Mahalanobis Distance."""

    def setup(self, bottom, top):
        # check input pair
        if len(bottom) != 2:
            raise Exception("Need two inputs to compute the distance.")

    def reshape(self, bottom, top):
        # check input dimensions match
        if bottom[0].count != bottom[1].count:
            raise Exception("Inputs must have the same dimensions!")
        # difference is an array of bottom.num
        # self.diff = np.zeros(shape=(bottom[0].shape[0], 1))
        # output is scalar
        top[0].reshape(bottom[0].num, 1)

    def forward(self, bottom, top):
        # calculate the covariance of two matrix
        temp = np.vstack((bottom[0].data, bottom[1].data))
        tempT = temp.T
        D = np.cov(tempT)
        invD = np.linalg.inv(D)  # the inverse of covariance

        n = bottom[0].shape[0]
        # diff = np.zeros(shape=(n,1))
        dis = []
        diss = np.array([])
        for i in range(0, n):
            delta = temp[i] - temp[i + n]
            # delta = bottom[0].data[i] - bottom[1].data[i]
            diff = np.sqrt(np.dot(np.dot(delta, invD), delta.T))
            dis.append(diff)

        diss = np.asarray(dis)
        top[0].data[...] = diss[:, np.newaxis]


    def backward(self, top, propagate_down, bottom):
        pass