#include <QCoreApplication>
#include "image.h"
#include "imagefile.h"
#include "pixel.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    /* **** Test program ****
     * Start with pixel data */
    Pixel redPixel{255,0,0,255};
    Pixel greenPixel{0,255,0,255};
    Pixel bluePixel{0,0,255,255};
    Pixel mixPixel{66,134,244};
    std::cout << "rgb(66,134,244) = " << mixPixel.getHex() << std::endl;
    Image ie(3,3);
    Pixel test = ie.getPixel(2,2);
    test.setBlue(120);
    ie.setPixel(2,2,test);
    Pixel test2 = ie.getPixel(1,1);
    ImageFile file;
    Image myTest = file.loadImage("./bild2.jpg");
    Image test20 = file.loadImage("./sample201.jpg");
    //file.printImage(myTest);
    file.saveImage("./test3.jpg", myTest);
    return a.exec();
}
