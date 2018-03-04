#ifndef CAFFEMEMORYLAYER_H
#define CAFFEMEMORYLAYER_H

// include all the header files of layers used in deploy.prototxt
#include "caffe/caffe.hpp"
#include "caffe/layer.hpp"
#include "caffe/layers/input_layer.hpp"
#include "caffe/layers/inner_product_layer.hpp"
#include "caffe/layers/conv_layer.hpp"
#include "caffe/layers/slice_layer.hpp"
#include "caffe/layers/pooling_layer.hpp"
#include "caffe/layers/relu_layer.hpp"
#include "caffe/layers/concat_layer.hpp"
#include "caffe/layers/eltwise_layer.hpp"
#include "caffe/layers/prelu_layer.hpp"
#include "caffe/layers/memory_data_layer.hpp"
#include "caffe/layers/dropout_layer.hpp"
#include "caffe/layers/softmax_layer.hpp"
#include "caffe/layers/softmax_loss_layer.hpp"
#include "caffe/layers/contrastive_loss_layer.hpp"
#include <opencv.hpp>
#include <iostream>

// predeifine
caffe::MemoryDataLayer<float> *memory_layer;
caffe::Net<float>* net;

#endif // CAFFEMEMORYLAYER_H
