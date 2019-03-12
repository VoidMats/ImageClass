#include "imagefile.h"

ImageFile::ImageFile(QObject *parent) : QObject(parent)
{

}

Image ImageFile::loadImage(QString _fileName) const
{
    QImage img = QImage(_fileName);
    Image returnImage(static_cast<size_t>(img.height()), static_cast<size_t>(img.width()));

    for (int w{0}; w<img.height(); ++w) {
        for (int h{0}; h<img.width(); ++h) {
            QRgb pixelQt{img.pixel(h,w)};
            Pixel pixelIE(qRed(pixelQt),qGreen(pixelQt),qBlue(pixelQt));
            returnImage.setPixel(h,w,pixelIE);
        }
    }
    return returnImage;
}

void ImageFile::saveImage(QString _filename, const Image &_image)
{
    uli height = _image.getHeight();
    uli width = _image.getWidth();

    QImage img = QImage(static_cast<int>(height), static_cast<int>(width), QImage::Format_RGB32);
    for (uli h{0}; h<height; ++h) {
        for (uli w{0}; w<width; ++w) {
            Pixel pixelIE = _image.getPixel(h,w);
            QColor pixelQt = QColor(pixelIE.getRed(),pixelIE.getGreen(),pixelIE.getBlue());
            img.setPixelColor(static_cast<int>(h),static_cast<int>(w),pixelQt);
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

