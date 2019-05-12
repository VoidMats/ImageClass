#include <QCoreApplication>
#include "image.h"
#include "imageprocess.h"
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

    // *** Load image and convert to grayscale
    Image normalImage = file.loadImage("./bild2.jpg");
    normalImage.convGray();
    file.saveImage("./test2.jpg", normalImage);
    ImageProcess normalProcess{normalImage};

    // *** Testing linearColorManipulation ***
    //normalProcess.linearColorManipulation(gray, 120);
    //Image linearImage = normalProcess.getProcessImage();
    //file.saveImage("./test3.jpg", linearImage);

    // *** Testing binarisation ***
    //normalProcess.binarisation(gray, 120);
    //Image binar1Image = normalProcess.getProcessImage();
    //file.saveImage("./test3.jpg", binar1Image);
    //normalProcess.binarisation(gray, 120, 30, 180);
    //Image binar2Image = normalProcess.getProcessImage();
    //file.saveImage("./test4.jpg", binar2Image);

    // *** Testing nonlinearColorManipulation ***
    /*std::array<uint8_t,COLORMAX+1> table;
    for (uint8_t i=0; i<COLORMAX; i++) {
        size_t value = static_cast<size_t>(i*i); // f(x)=x^2
        if( value>COLORMAX )
            value = COLORMAX;
        table[i] = static_cast<uint8_t>(value);
    }
    normalProcess.nonlinearColorManipulation(gray, table);
    Image nonlinearImage = normalProcess.getProcessImage();
    file.saveImage("./test5.jpg", nonlinearImage); */

    // *** Testing point different filter ***
    //normalProcess.pointDifferentFilter(gray,3);
    //Image filterImage = normalProcess.getProcessImage();
    //file.saveImage("./test4.jpg", filterImage);

    // *** Testing mean filter ***
    //normalProcess.meanFilter(gray);
    //Image meanImage = normalProcess.getProcessImage();
    //file.saveImage("./test5_mean.jpg", meanImage);

    // *** Testing median filter ***
    //normalProcess.medianFilter(gray);
    //Image medianImage = normalProcess.getProcessImage();
    //file.saveImage("./test6_median.jpg", medianImage);

    // *** Testing laplace filter ***
    normalProcess.laplaceFilter(gray);
    Image laplaceImage = normalProcess.getProcessImage();
    file.saveImage("./test7_laplace.jpg", laplaceImage);

    // *** Testing laplace filter ***
    normalProcess.contrastEnhancementFilter(gray);
    Image contrastImage = normalProcess.getProcessImage();
    file.saveImage("./test8_contrast.jpg", laplaceImage);

    //Image testImage = file.loadImage("./sample20Big.png");
    //file.saveImage("./test5.jpg", testImage);

    //Image ie(50,50);
    //for( size_t i=0; i<ie.getHeight(); i++) {
    //    Pixel pixelToSet{0,0,0};
    //    ie.setPixel(i,i,pixelToSet);
    //}
    //file.saveImage("./test5.png", ie);

    //Pixel test = ie.getPixel(2,2);
    //test.setBlue(120);
    //ie.setPixel(2,2,test);
    //Pixel test2 = ie.getPixel(1,1);


    //Image test20 = file.loadImage("./sample201.jpg");
    //file.printImage(myTest);

    return a.exec();
}
