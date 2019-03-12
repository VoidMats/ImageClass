#include <QCoreApplication>
#include "image.h"
#include "imagefile.h"
#include "pixel.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Image ie(3,3);
    Pixel test = ie.getPixel(2,2);
    test.setBlue(120);
    ie.setPixel(2,2,test);
    Pixel test2 = ie.getPixel(1,1);
    ImageFile file;
    Image myTest = file.loadImage("./bild2.jpg");
    Image test20 = file.loadImage("./sample201.jpg");
    myTest.binarisation(COLOR::red,150);
    //file.printImage(myTest);
    file.saveImage("./test3.jpg", myTest);
    return a.exec();
}
