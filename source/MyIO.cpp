#include <QDebug>
#include "MyIO.h"

MyIO::MyIO()
{

}

MyIO::~MyIO()
{

}

QFileInfoList MyIO::getFileList(const QString &path)
{
    QFileInfoList fileList;
    if(path.isNull() || path.isEmpty())
    {
        qDebug() << "## The path is null or empty!!!";
        return fileList;
    }
    else
    {
        QDir dir(path);
        if(!dir.exists()) //判断路径是否存在
        {
            qDebug() << "## The path is not exists!!!";
            return fileList;
        }
        else
        {
            QFileInfoList folderList = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);

            fileList = dir.entryInfoList(QDir::Files | QDir::NoSymLinks);
            QStringList filters;
            filters << QString("*.jpeg") << QString("*.jpg") << QString("*.png")
                    << QString("*.tiff") << QString("*.gif") << QString("*.bmp");
            dir.setNameFilters(filters);  //设置文件名称过滤器: 后缀为.jpeg等图片格式

            for(int i=0; i<folderList.size(); i++)
            {
                 QString folderName = folderList.at(i).absoluteFilePath();
                 qDebug() << "## Folder Name: " + folderName;

                 QFileInfoList childFileList = getFileList(folderName);
                 fileList.append(childFileList);
            }

            return fileList;
        }
    }
}

QStringList MyIO::getFileList(const QString &path, bool fileTypeFilter)
{
    QStringList fileList;
    if(path.isNull() || path.isEmpty())
    {
        qDebug() << "## The path is null or empty!!!";
        return fileList;
    }
    else
    {
        QDir dir(path);
        if(!dir.exists()) //判断路径是否存在
        {
            qDebug() << "## The path is not exists!!!";
            return fileList;
        }
        else
        {
            QDirIterator *dirIterator = NULL; //定义迭代器
            QStringList filters;              //获取所选文件类型过滤器
            if(fileTypeFilter)
            {
                filters << QString("*.jpeg") << QString("*.jpg") << QString("*.png")
                        << QString("*.tiff") << QString("*.gif") << QString("*.bmp");
                dirIterator = new QDirIterator(path,filters,
                                               QDir::Files | QDir::NoSymLinks,
                                               QDirIterator::Subdirectories);
            }
            else
            {
                dirIterator = new QDirIterator(path,QDir::Files | QDir::NoSymLinks,
                                                    QDirIterator::Subdirectories);
            }

            while(dirIterator->hasNext())
            {
                dirIterator->next();
                QFileInfo fileInfo = dirIterator->fileInfo();
                QString filePath = fileInfo.absoluteFilePath();
                fileList.append(filePath);
            }

            delete dirIterator;
            dirIterator = NULL;

            return fileList;
        }
    }
}
