#include "imagefile.h"

ImageFile::ImageFile(QObject *parent) :
    QObject(parent), imageFormat{QImage::Format_Invalid}
{

}

Image ImageFile::loadImage(QString _fileName)
{
    QImage img = QImage(_fileName);
    imageFormat = img.format();
    Image returnImage(static_cast<size_t>(img.height()), static_cast<size_t>(img.width()));

    int height{ img.height() };
    int width{ img.width() };

    for (int h{0}; h<height; h++) {
        for (int w{0}; w<width; w++) {
            QColor pixelQt{ img.pixel(w,h) };
            QString tmp =  QStringLiteral("%1 ").arg(pixelQt.red());
            //std::cout << pixelQt.red() << " ";
            Pixel pixelIE( pixelQt.red(), pixelQt.green(), pixelQt.blue(), pixelQt.alpha() );
            returnImage.setPixel(h,w,pixelIE);
        }
    }

    return returnImage;
}

void ImageFile::saveImage(QString _filename, const Image &_image)
{
    uli height{ _image.getHeight() };
    uli width{ _image.getWidth() };

    QImage img = QImage(static_cast<int>(width), static_cast<int>(height), imageFormat); //OK

    for (uli h{0}; h<height; ++h) {
        for (uli w{0}; w<width; ++w) {
            Pixel pixelIE = _image.getPixel(h,w);
            QColor pixelQt = QColor(pixelIE.getRed(), pixelIE.getGreen(), pixelIE.getBlue());
            img.setPixelColor(static_cast<int>(w),static_cast<int>(h),pixelQt);
        }
    }

    img.save(_filename);
}

void ImageFile::printImage(const Image &_image)
{
    for (uli h{0}; h<_image.getHeight(); ++h) {
        for (uli w{0}; w<_image.getWidth(); ++w) {
            Pixel p = _image.getPixel(h,w);
            cout << " " << p.getGray();
        }
        cout << endl;
    }
}

