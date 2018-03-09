import pandas as pd
from matplotlib import *
from matplotlib.pyplot import *

train_log = pd.read_csv("/Users/Desktop/draw_loss_curve/face_DeepID_GoogleNet_train_add_2.log.train")
test_log = pd.read_csv("/Users/Desktop/draw_loss_curve/face_DeepID_GoogleNet_train_add_2.log.test")

_, ax1 = subplots(figsize=(8, 6))
#ax2 = ax1.twinx()
train_contrastive_loss = train_log["Contrastive_Loss"]
train_softmax_loss1 = train_log["softmax_loss1"]
train_softmax_loss2 = train_log["softmax_loss2"]
train_loss = train_contrastive_loss + 0.3*train_softmax_loss1 + train_softmax_loss2
#train_center_loss = train_log["center_loss"]
#train_softmax_loss = train_log["softmax_loss"]
#train_loss = 0.008*train_center_loss + train_softmax_loss
trainLoss, = ax1.plot(train_log["NumIters"], train_loss, 'r')

test_contrastive_loss = test_log["Contrastive_Loss"]
test_softmax_loss1 = test_log["softmax_loss1"]
test_softmax_loss2 = test_log["softmax_loss2"]
test_loss = test_contrastive_loss + 0.3*test_softmax_loss1 + test_softmax_loss2
#test_center_loss = test_log["center_loss"]
#test_softmax_loss = test_log["softmax_loss"]
#test_loss = 0.008*test_center_loss + test_softmax_loss
testLoss, = ax1.plot(test_log["NumIters"], test_loss, 'g', marker = 'x')
#ax2.plot(test_log["Iters"], test_log["TestAccuracy"], 'r')

title('Train loss & Test loss vs. Iters')
ax1.set_xlabel('Iters')
ax1.set_ylabel('Loss')
legend(handles = [trainLoss, testLoss,], labels = ['train loss of face_DeepID_GoogleNet_train_add_2', 'test loss of face_DeepID_GoogleNet_train_add_2'], loc = 'best')

#ax2.set_ylabel('test accuracy')
savefig("/Users/Desktop/draw_loss_curve/face_DeepID_GoogleNet_train_add_2.png") #save image as png
