#ifndef PIXEL_H
#define PIXEL_H
// C++ includes
#include <stdint.h>
#include <iostream>
#include <sstream>
#include <iomanip>
//#include <cstdio>

//using namespace std;

enum COLOR{ red, green, blue, gray };

class Pixel
{
private:
    uint8_t redPixel, greenPixel, bluePixel;
    uint8_t grayPixel;
    float alpha;
    void calcGrayPixel();

public:
    // Constructors
    Pixel();
    Pixel(int redPixel, int greenPixel, int bluePixel, float alpha=1.0);
    Pixel(uint8_t _redPixel, uint8_t _greenPixel, uint8_t _bluePixel, float alpha=1.0);
    ~Pixel() = default;
    // Copy constructor
    Pixel(Pixel const &_copy) = default;
    Pixel &operator = (Pixel const &_copy) = default;
    // Move constructor
    Pixel(Pixel &&_move) = default;
    Pixel &operator = (Pixel &&_move) = default;
    // Other operators
    bool operator != (const Pixel &_comp) const {
        return _comp.redPixel != redPixel ||
               _comp.greenPixel != greenPixel ||
               _comp.bluePixel != bluePixel;
    }

    // **** More operators needed

    // Public functions
    uint8_t getRed() { return redPixel; }
    uint8_t getGreen() { return greenPixel; }
    uint8_t getBlue() { return bluePixel; }
    uint8_t getGray() { return grayPixel; }
    uint8_t getColor(COLOR _color);
    std::string getHex();
    void setRed(uint8_t _red);
    void setGreen(uint8_t _green);
    void setBlue(uint8_t _blue);
    void setgray(uint8_t _gray);
    void setColor(COLOR _color, uint8_t _value);
    void setRGB(uint8_t _red, uint8_t _green, uint8_t _blue);
};

#endif // PIXEL_H
