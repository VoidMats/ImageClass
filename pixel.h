#ifndef PIXEL_H
#define PIXEL_H
// C++ includes
#include <stdint.h>

//using namespace std;

enum COLOR{ red, green, blue, gray };

class Pixel
{
private:
    uint8_t redPixel;
    uint8_t greenPixel;
    uint8_t bluePixel;
    uint8_t grayPixel;
    uint8_t alpha;
    void calcGrayPixel();

public:
    // Constructors
    Pixel() : redPixel{0}, greenPixel{0}, bluePixel{0}, grayPixel{0}, alpha{0} {}
    Pixel(int redPixel, int greenPixel, int bluePixel, int alpha=255);
    Pixel(uint8_t redPixel, uint8_t greenPixel, uint8_t bluePixel, uint8_t alpha=255);
    ~Pixel() = default;
    // Copy constructor
    Pixel(Pixel const &_copy) = default;
    Pixel &operator = (Pixel const &_copy) = default;
    // Move constructor
    Pixel(Pixel &&_move) = default;
    Pixel &operator = (Pixel &&_move) = default;
    // Other operators
    bool operator != (const Pixel &_comp) const
    {
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
    void setRed(uint8_t _red);
    void setGreen(uint8_t _green);
    void setBlue(uint8_t _blue);
    void setRGB(uint8_t _red, uint8_t _green, uint8_t _blue);
};

#endif // PIXEL_H
