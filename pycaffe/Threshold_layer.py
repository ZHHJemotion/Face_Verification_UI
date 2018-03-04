import caffe
import numpy as np
import json

class ThresholdLayer(caffe.Layer):
    """Rewrite the threshold layer of caffe to be applied in the metric learning.
    
     Accepts JSON-encoded parameters through param_str

    Use like this:

    layer {
        name: "threshold"
        type: "Python"
        bottom: "distance"
        top: "prediction"
        python_param {
            module: "Threshold_layer"
            layer: "ThresholdLayer"
            param_str: "{\"threshold\": 1}"
        }
    }
    """

    def setup(self, bottom, top):
        assert len(bottom) == 1, 'requires two layer.bottoms'
        assert len(top) == 1, 'requires a single layer.top'

        if hasattr(self, 'param_str') and self.param_str:
            params = json.loads(self.param_str)
        else:
            params = {}

        self.threshold = params.get('threshold', 1)


    def reshape(self, bottom, top):
        top[0].reshape(bottom[0].num, 1)


    def forward(self, bottom, top):
        n = bottom[0].shape[0]
        temp = []
        #prediction_array = np.array([])
        for i in range(0, n):
            prediction = 0 if bottom[0].data[i] > self.threshold else prediction = 1
            temp.append(prediction)

        prediction_array = np.asarray(temp)
        top[0].data[...] = prediction_array[:, np.newaxis]


    def backward(self, top, propagate_down, bottom):
        pass