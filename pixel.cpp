#include "pixel.h"

void Pixel::calcGrayPixel()
{
    grayPixel = static_cast<uint8_t>(redPixel*0.299 +
                                     greenPixel*0.587 +
                                     bluePixel*0.144);
}

Pixel::Pixel(int redPixel, int greenPixel, int bluePixel, int alpha)
{
    redPixel = static_cast<uint8_t>(redPixel);
    greenPixel = static_cast<uint8_t>(greenPixel);
    bluePixel = static_cast<uint8_t>(bluePixel);
    alpha = static_cast<uint8_t>(alpha);
    calcGrayPixel();
}

Pixel::Pixel(uint8_t redPixel, uint8_t greenPixel, uint8_t bluePixel, uint8_t alpha)
    :redPixel{redPixel}, greenPixel{greenPixel}, bluePixel{bluePixel}, alpha{alpha}
{
    calcGrayPixel();
}

uint8_t Pixel::getColor(COLOR _color)
{
    uint8_t temp = 0;
    switch(_color)
    {
    case COLOR::red:
        temp = getRed();
        break;
    case COLOR::green:
        temp = getGreen();
        break;
    case COLOR::blue:
        temp = getBlue();
        break;
    case COLOR::gray:
        temp = getGray();
        break;
    }
    return temp;
}

std::string Pixel::getHex()
{
    std::stringstream stream;
    stream << "#" << std::setfill('0') << std::setw(sizeof(uint8_t) * 2) << std::hex << static_cast<int>(redPixel)
           << std::hex << static_cast<int>(greenPixel) << std::hex << static_cast<int>(bluePixel);
    return stream.str();
}

void Pixel::setRed(uint8_t _red)
{
    redPixel = _red;
    calcGrayPixel();
}

void Pixel::setGreen(uint8_t _green)
{
    greenPixel = _green;
    calcGrayPixel();
}

void Pixel::setBlue(uint8_t _blue)
{
    bluePixel = _blue;
    calcGrayPixel();
}

void Pixel::setColor(COLOR _color, uint8_t _value)
{
    switch(_color)
    {
    case COLOR::red:
        setRed(_value);
        break;
    case COLOR::green:
        setGreen(_value);
        break;
    case COLOR::blue:
        setBlue(_value);
        break;
    case COLOR::gray:
        grayPixel = _value;
        break;
    }
}

void Pixel::setRGB(uint8_t _red, uint8_t _green, uint8_t _blue)
{
    redPixel = _red;
    greenPixel = _green;
    bluePixel = _blue;
    calcGrayPixel();
}

