import pandas as pd
from matplotlib import *
from matplotlib.pyplot import *

train_log = pd.read_csv("/Users/Desktop/draw_loss_curve/siamese_train_euclidean_1.log.train")
test_log = pd.read_csv("/Users/Desktop/draw_loss_curve/siamese_train_euclidean_1.log.test")
_, ax1 = subplots(figsize=(8, 6))

trainLoss, = ax1.plot(train_log["NumIters"], train_log["loss"], 'r')
testLoss, = ax1.plot(test_log["NumIters"], test_log["loss"], 'g')

title('Train loss & Test loss vs. Iters')
ax1.set_xlabel('Iters')
ax1.set_ylabel('Loss')

legend(handles = [trainLoss, testLoss,], labels = ['train loss of siamese_train_euclidean_1', 'test loss of siamese_train_euclidean_1'], loc = 'best')

savefig("/Users/Desktop/draw_loss_curve/siamese_train_euclidean_1.png") #save image as png