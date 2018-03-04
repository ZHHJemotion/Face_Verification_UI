import caffe
import numpy as np

class EuclideanLayer(caffe.Layer):
    """EuclideanDistance layer use for calculating Euclidean Distance."""

    def setup(self, bottom, top):
        # check input pair
        if len(bottom) != 2:
            raise Exception("Need two inputs to compute the distance.")

    def reshape(self, bottom, top):
        # check input dimensions match
        if bottom[0].count != bottom[1].count:
            raise Exception("Inputs must have the same dimensions!")
        # difference is shape of inputs
        self.diff = np.zeros_like(bottom[0].data, dtype=np.float32)
        # loss output is scalar
        top[0].reshape(bottom[0].num, 1)

    def forward(self, bottom, top):
        self.diff[...] = bottom[0].data - bottom[1].data
        top[0].data[...] = np.sqrt(np.sum(self.diff ** 2, axis=1)[:, np.newaxis])

    def backward(self, top, propagate_down, bottom):
        pass


