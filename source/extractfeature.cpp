#define USE_OPENCV
#include "extractfeature.h"
#include "caffememorylayer.h"

namespace caffe
{
    extern INSTANTIATE_CLASS(InputLayer);
    extern INSTANTIATE_CLASS(InnerProductLayer);
    extern INSTANTIATE_CLASS(DropoutLayer);
    extern INSTANTIATE_CLASS(SliceLayer);
    extern INSTANTIATE_CLASS(ConvolutionLayer);
    extern INSTANTIATE_CLASS(ReLULayer);
    extern INSTANTIATE_CLASS(PoolingLayer);
    extern INSTANTIATE_CLASS(SoftmaxLayer);
    extern INSTANTIATE_CLASS(MemoryDataLayer);
    extern INSTANTIATE_CLASS(EltwiseLayer);
    extern INSTANTIATE_CLASS(ConcatLayer);
    extern INSTANTIATE_CLASS(PReLULayer);
    extern INSTANTIATE_CLASS(SoftmaxWithLossLayer);
    extern INSTANTIATE_CLASS(ContrastiveLossLayer);
}

#define deployFile string("/Users/zhangxingjian/Desktop/Programming/C++/Face_Verification_UI/prototxt/face_deploy_noBN.prototxt")
#define caffemodelFile string("/Users/zhangxingjian/Desktop/Programming/C++/Face_Verification_UI/caffemodel/face_train_test_iter_20000.caffemodel")

template <typename Dtype>

caffe::Net<Dtype>* NetInitLoad(std::string paramFile, std::string pretrainedParamFile, caffe::Phase phase)
{
    caffe::Net<Dtype>* net(new caffe::Net<Dtype>(deployFile, caffe::TEST)); // .prototxt 的路径需要重新写！！！
    net->CopyTrainedLayersFrom(caffemodelFile);
    return net;
}


void CaffePredefine()
{
    caffe::Caffe::set_mode(caffe::Caffe::CPU); // if your PC has GPU, set GPU!
    net = NetInitLoad<float>(deployFile, caffemodelFile, caffe::TEST);
    memory_layer = (caffe::MemoryDataLayer<float> *)net->layers()[0].get();
}

std::vector<float> ExtractFeature(Mat FaceROI_1, Mat FaceROI_2)
{
    caffe::Caffe::set_mode(caffe::Caffe::CPU); // if your PC has GPU, set GPU!
    Mat concateTemp;
    std::vector<Mat> test, temp;
    std::vector<int> testLabel;

    // merge two 3-channels images to a 6-channels image
    temp.push_back(FaceROI_1);
    temp.push_back(FaceROI_2);
    cv::merge(temp, concateTemp);
    test.push_back(concateTemp);
    testLabel.push_back(0);
    memory_layer->AddMatVector(test, testLabel);
    temp.clear();
    test.clear();
    testLabel.clear();

    // Forward Propagation
    std::vector<caffe::Blob<float>*> input_vec;
    net->Forward(input_vec);

    // get the output of Softmax layer --> prob
    auto prob = net->blob_by_name("prob");
    float* begin = prob->mutable_cpu_data();
    vector<float> test_vector{ begin, begin + prob->channels() }; // used to save the extracted feature

    return test_vector;
}
