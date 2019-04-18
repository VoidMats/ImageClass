#include <QCoreApplication>
#include "image.h"
#include "imagefile.h"
#include "pixel.h"
#include "test.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    /* **** Test program ****/
    qDebug("Test pixels");
    Pixel redPixel{255,0,0,255};
    Pixel greenPixel{0,255,0,255};
    Pixel bluePixel{0,0,255,255};
    Pixel mixPixel{66,134,244};
    std::cout << "rgb(66,134,244) = " << mixPixel.getHex() << std::endl;

    std::cout << "Create a new image and write pixels" << std::endl;
    ImageFile file(QImage::Format_RGB32);
    Image emptyImage = Image(20,20);
    //Pixel ip = Pixel(0,0,0);
    //emptyImage.setPixel(2,2,ip);

    for (unsigned int h{0}; h<emptyImage.getHeight(); h++) {
        Pixel ip = Pixel(0,0,0);
        emptyImage.setPixel(5,h,ip);
    }
    file.printImage(emptyImage);
    std::cout << "Save image to file" << endl;
    file.saveImage("./test1.jpg", emptyImage);

    Image normalImage = file.loadImage("./bild2.jpg");
    file.saveImage("./test2.jpg", normalImage);
    Image testImage = file.loadImage("./sample20Big.png");
    file.saveImage("./test3.jpg", testImage);


    //Image ie(50,50);
    //for( size_t i=0; i<ie.getHeight(); i++) {
    //    Pixel pixelToSet{0,0,0};
    //    ie.setPixel(i,i,pixelToSet);
    //}
    //file.saveImage("./test4.png", ie);

    //Pixel test = ie.getPixel(2,2);
    //test.setBlue(120);
    //ie.setPixel(2,2,test);
    //Pixel test2 = ie.getPixel(1,1);


    //Image test20 = file.loadImage("./sample201.jpg");
    //file.printImage(myTest);

    return a.exec();
}
