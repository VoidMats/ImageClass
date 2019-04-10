#ifndef IMAGEPROCESS_H
#define IMAGEPROCESS_H
#include <iostream>
#include <memory>
#include <string>
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

    void setProcess();
    void resetProcess();

    // Public image process functions
    void binarisation(COLOR _color, uint8_t _threshold);
    void linearColorManipulation(COLOR _color, uint8_t _threshold);
    void nonlinearColorManipulation(COLOR _color, std::array<uint8_t,COLORMAX> _table);
    void pointDifferentFilter(COLOR _color, uint8_t _factor=1);
};

#endif // IMAGEPROCESS_H
