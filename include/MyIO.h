#ifndef MYIO_H
#define MYIO_H

#include <QDir>
#include <QFile>
#include <QObject>
#include <QString>
#include <QIODevice>
#include <QDirIterator>
#include "PathManage.h"

class MyIO:public QObject
{
    Q_OBJECT
public:
    explicit MyIO();
    ~MyIO();

public:
    QFileInfoList getFileList(const QString &path);
    QStringList getFileList(const QString &path, bool fileTypeFilter);

};

#endif // MYIO_H
