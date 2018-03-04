import caffe
import json

class AccuracyLayer(caffe.Layer):
    """
    Rewrite Accuracy layer as a Python layer
    For metric learning such as Euclidean Distance and Mahalanobis Distance

    Accepts JSON-encoded parameters through param_str

    Use like this:

    layer {
        name: "accuracy"
        type: "Python"
        bottom: "pred"
        bottom: "label"
        top: "accuracy"
        include {
            phase: TEST
        }
        python_param {
            module: "accuracy_layer"
            layer: "AccuracyLayer"
            param_str: "{\"top_k\": 2}"
        }
    }
    """
    
    def setup(self, bottom, top):
        assert len(bottom) == 2,    'requires two layer.bottoms'
        assert len(top) == 1,       'requires a single layer.top'

        #if hasattr(self, 'param_str') and self.param_str:
        #    params = json.loads(self.param_str)
        #else:
        #    params = {}

        #self.top_k = params.get('top_k', 1)
    
    def reshape(self, bottom, top):
        top[0].reshape(1)
    
    def forward(self, bottom, top):
        # Renaming for clarity
        predictions = bottom[0].data
        ground_truth = bottom[1].data
    
        num_correct = 0.0

        n = bottom[0].shape[0]
        for i in range(0, n):
            if predictions[i] == ground_truth[i]:
                num_correct += 1

        # Accuracy is averaged over the batch
        top[0].data[0] = num_correct / len(ground_truth)
    
    def backward(self, top, propagate_down, bottom):
        pass