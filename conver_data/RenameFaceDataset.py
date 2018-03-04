# -*- coding: UTF-8 -*-
import os

def rename():
    count = 1
    path = '/Users/zhangxingjian/Desktop/Programming/Python/Conver_Data/Database_aligned_balanced/Adam'

    filelist = os.listdir(path)   #该文件夹下所有的文件（包括文件夹）
    for files in filelist:  #遍历所有文件
        Olddir = os.path.join(path, files)  #原来的文件路径
        if os.path.isdir(Olddir):  #如果是文件夹则跳过
            continue

        filename = 'Adam - '
        #filename = os.path.splitext(files)[0] #文件名
        #filetype = os.path.splitext(files)[1] #文件扩展名
        Newdir = os.path.join(path, filename + str(count) + '.png')   #新的文件路径
        os.rename(Olddir, Newdir)  #重命名
        print files
        count += 1

rename()
