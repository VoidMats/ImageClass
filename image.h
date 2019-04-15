#ifndef IMAGE_H
#define IMAGE_H
// C++ includes
#include <stdint.h>
#include <vector>
#include <array>
#include <iostream>
#include <string>
#include <cstring>
#include <memory>
// Classes
#include "pixel.h"
#include "smartpointers.h"
// Library includes

const size_t COLORMAX{255};

class Image
{
private:
    size_t height = 0;
    size_t width = 0;
    Pixel *data = nullptr;
    //std::shared_ptr<Pixel[]> data;  //In C++11 unique_ptr is not complete does not exist
    size_t sizeByte;

    // Pixel assignment operator
    const Pixel &operator = (const size_t  &_i) const;
    Pixel &operator = (const size_t &_i);

    // Private functions
    template<typename HistoSize>
    HistoSize calcHistogramSize();

public:
    //Image() : height{0}, width{0}, data{nullptr} {} //Maybe this should be removed
    Image(const size_t &_height,
          const size_t &_width,
          const Pixel &_pixel = Pixel());
    ~Image();
    // Copy constructor
    Image(Image const &_copy);
    Image &operator = (const Image &_copy);
    // Move constructor
    Image(Image &&_move);
    Image &operator = (Image &&_move);

    // Public attribute functions
    Pixel getPixel(size_t _height, size_t _width) const;
    //Pixel getPixel(size_t _memIterator) const { return data[_memIterator]; } Not sure about this yet
    void setPixel(size_t _height, size_t _width, const Pixel &_pixel=Pixel());
    void setPixel(int _height, int _width, const Pixel &_pixel=Pixel());
    size_t getHeight() const { return height; }
    size_t getWidth() const { return width; }

    // Public image process functions
    template<typename HistoSize>
    std::vector<HistoSize> getHistogram();
    template<typename HistoSize>
    std::vector<HistoSize> getColorHistorgram(COLOR _color);

};

#endif // IMAGEEFFECT_H

