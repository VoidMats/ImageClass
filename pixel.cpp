#include "pixel.h"

uint8_t Pixel::calcGrayPixel()
{
    uint8_t grayPixel = static_cast<uint8_t>(redPixel*0.299 +
                                     greenPixel*0.587 +
                                     bluePixel*0.144);
    return grayPixel;
}

Pixel::Pixel():
    redPixel{255}, greenPixel{255}, bluePixel{255}, alpha{0}
{
    pixelGray = false;
}

Pixel::Pixel(int _redPixel, int _greenPixel, int _bluePixel, float _alpha)
{
    redPixel = static_cast<uint8_t>(_redPixel);
    greenPixel = static_cast<uint8_t>(_greenPixel);
    bluePixel = static_cast<uint8_t>(_bluePixel);
    alpha = _alpha;
    pixelGray = false;
}

Pixel::Pixel(uint8_t _redPixel, uint8_t _greenPixel, uint8_t _bluePixel, float _alpha)
    :redPixel{_redPixel}, greenPixel{_greenPixel}, bluePixel{_bluePixel}, alpha{_alpha}
{
    pixelGray = false;
}

uint8_t Pixel::getGray()
{
    if( pixelGray )
        return redPixel;  // All rgb values are the same
    else
        return calcGrayPixel();
}

uint8_t Pixel::getColor(COLOR _color)
{
    uint8_t temp = 0;
    switch(_color)
    {
    case COLOR::red:
        temp = redPixel;
        break;
    case COLOR::green:
        temp = greenPixel;
        break;
    case COLOR::blue:
        temp = bluePixel;
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
}

void Pixel::setGreen(uint8_t _green)
{
    greenPixel = _green;
}

void Pixel::setBlue(uint8_t _blue)
{
    bluePixel = _blue;
}

void Pixel::setgray()
{
    uint8_t tmp = calcGrayPixel();
    setRGB(tmp, tmp, tmp);
    pixelGray = true;
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
        setRGB(_value, _value, _value);
        pixelGray = true;
        break;
    }
}

void Pixel::setRGB(uint8_t _red, uint8_t _green, uint8_t _blue)
{
    redPixel = _red;
    greenPixel = _green;
    bluePixel = _blue;
}

