#ifndef IMAGEFILE_H
#define IMAGEFILE_H

// C++ includes
#include <vector>
// Qt includes
#include <QObject>
#include <QString>
#include <QImage>
#include <QDebug>
// My includes
#include "pixel.h"
#include "image.h"

using namespace std;

typedef unsigned long int uli;

class ImageFile : public QObject
{
    Q_OBJECT
public:
    explicit ImageFile(QImage::Format _format = QImage::Format_Invalid, QObject *parent = nullptr);
    Image loadImage(QString _fileName);
    void saveImage(QString _filename, const Image &_image);

    // For testing purposes
    void printImage(const Image &_image);

signals:

public slots:

private:
    QImage::Format imageFormat;
};

#endif // IMAGEFILE_H
