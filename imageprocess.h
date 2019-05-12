#ifndef IMAGEPROCESS_H
#define IMAGEPROCESS_H
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>
// Classes
#include "pixel.h"
#include "image.h"
// Library includes

class ImageProcess
{
private:
    Image org;
    Image mod;

public:
    ImageProcess(const Image &_image);  // TODO rule of five
    ~ImageProcess();

    // Public image manipulation functions
    void setProcess();
    void resetProcess();
    Image getOriginalImage();
    Image getProcessImage();

    // Public image process functions
    void convToGray();
    void binarisation(COLOR _color, uint8_t _threshold, uint8_t _min=0, uint8_t _max=COLORMAX);
    void linearColorManipulation(COLOR _color, uint8_t _threshold);
    void nonlinearColorManipulation(COLOR _color, std::array<uint8_t,COLORMAX+1> _table);
    void pointDifferentFilter(COLOR _color, uint8_t _factor=1);
    void meanFilter(COLOR _color);
    void medianFilter(COLOR _color);
    void laplaceFilter(COLOR _color);
    void contrastEnhancementFilter(COLOR _color);
     // TODO from here and downwords
    void dilatation(uint8_t nr);
    void erosion(uint8_t nr);

    // Public tables functions
    std::array<uint8_t,COLORMAX+1> createTablePolynom(int _degree, int _factor);

    // Public image feature extraction
    void graylevelSegmentation();
    void connectedComponentAnalysis();
};

#endif // IMAGEPROCESS_H
