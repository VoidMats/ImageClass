#include "image.h"

template<typename HistoSize>
HistoSize Image::calcHistogramSize()
{
    unsigned long long int temp = height*width;
    if( temp < sizeof (unsigned short int) ) {
        unsigned short int ret=0;
        return ret;
    }
    else if ( temp < sizeof (unsigned int) ) {
        unsigned int ret=0;
        return ret;
    }
    else if ( temp < sizeof (unsigned long long int) ) {
        temp = 0;
        return temp;
    }
}

/* Constructor for Image
 * Parameters:
 * [size_t] height
 * [size_t] width */
Image::Image(const size_t &_height, const size_t &_width, const Pixel &_pixel)
    :height{_height}, width{_width}, data{nullptr}, sizeByte{0}
{
    //data = std::make_shared<Pixel[]>(height*width); This does not work https://gcc.gnu.org/bugzilla/show_bug.cgi?id=58822
    data = new Pixel[height*width];

    const size_t total = height * width;
    for (size_t i=0; i<total; ++i) {
        data[i] = _pixel;
    }
    // Set the size of the array
    sizeByte = sizeof(Pixel)*height*width;

    // Fill the Image with pixels
    /*
    for (unsigned int h{0}; h<height; h++) {
        for (unsigned int w{0}; w<width; w++) {
            data[(_height+1)*(_width+1)] = _pixel;
        }
    }*/
}

Image::~Image()
{
    if(data != nullptr || sizeByte != 0) {
        delete [] data;
    }
    sizeByte = 0;
    height = 0;
    width = 0;
}

/* Copy constructor for Image */
Image::Image(const Image &_copy)
    :height{_copy.getHeight()}, width{_copy.getWidth()}, data{nullptr}
{
    //data = std::make_shared<Pixel[]>(height*width);
    /*
    for(size_t i=0;  i<sizeByte; ++i) {
        data[i] = _copy.getPixel(i);
    }*/

    data = new Pixel[height*width];
    sizeByte = sizeof(Pixel)*height*width;
    std::memcpy(data, _copy.data, sizeByte);
}

/* Copy assignment operator */
Image &Image::operator =(const Image &_copy)
{
    if(data != nullptr)
        delete [] data;
    data = new Pixel[height*width];
    sizeByte = sizeof(Pixel)*height*width;
    std::memcpy(data, _copy.data, sizeByte);
    return *this;
}

/* Move constructor for Image */
Image::Image(Image &&_move)
    :height{_move.height}, width{_move.width}, data{_move.data}
{
    sizeByte = sizeof(Pixel)*height*width;
    delete [] _move.data;
    _move.data = nullptr;
    _move.height = 0;
    _move.width = 0;
}

/* Move assigment operator */
Image &Image::operator =(Image &&_move)
{
    if(this != &_move) {        // hmm this should be checked
        if(data != nullptr)
            delete [] data;
        height = _move.height;
        width = _move.width;
        data = _move.data;
        sizeByte = sizeof(Pixel)*height*width;
        // Delete move
        delete [] _move.data;
        _move.data = nullptr;
        _move.height = 0;
        _move.width = 0;
    }
    return *this;
}

/*
const Pixel &Image::operator =(size_t const &_i) const
{
    return data[_i];
}

Pixel &Image::operator =(const size_t &_i)
{
    return data[_i];
}
*/
const Pixel &Image::operator [](const size_t &_i) const
{
    return data[_i];
}

Pixel &Image::operator [](const size_t &_i)
{
    return data[_i];
}

template<typename HistoSize>
std::vector<HistoSize> Image::getHistogram ()
{
    std::vector<HistoSize> histogram(255,0);
    for(size_t h=0; h<height; h++) {
        for(size_t w=0; w<width; w++) {
            histogram[getPixel(h,w).getGray()] += 1;
        }
    }
    return histogram;
}

/* Return the histogram of the image. Depending which
 * value _color has it will return that histogram. */
template<typename HistoSize>
std::vector<HistoSize> Image::getColorHistorgram (COLOR _color)
{
    std::vector<HistoSize> histogram(255,0);
    switch(_color)
    {
    case COLOR::red:
        for ( unsigned long h=0; h<height; h++ ) {
            for( unsigned long w=0; w<width; w++ ) {
                //histogram[image.at(h).at(w).getRed()] += 1;
            }
        }
        break;
    case COLOR::green:
        for(unsigned long h=0; h<height; h++) {
            for(unsigned long w=0; w<width; w++) {
                //histogram[image.at(h).at(w).getGreen()] += 1;
            }
        }
        break;
    case COLOR::blue:
        for(unsigned long h=0; h<height; h++) {
            for(unsigned long w=0; w<width; w++) {
                //histogram[image.at(h).at(w).getBlue()] += 1;
            }
        }
        break;
    case COLOR::gray:
        for(unsigned long h=0; h<height; h++) {
            for(unsigned long w=0; w<width; w++) {
                //histogram[image.at(h).at(w).getBlue()] += 1;
            }
        }
        break;
    default:
        // Error code instead
        std::cerr << "This color does not exist. Please use RGB" << std::endl;
    }

    return histogram;
}

Pixel Image::getPixel(const size_t &_width, const size_t &_height) const
{
    // TODO assert(_width < width && _height < height);
    return data[_height*width + _width];
}

void Image::setPixel(const size_t &_width, const size_t &_height, const Pixel &_pixel)
{
    data[ _height * width +_width] = _pixel;
}

/*
void Image::setPixel(int _height, int _width, const Pixel &_pixel)
{
    if(_height<0 || _width<0) {
        throw("Error Image::setPixel - parameter out of range"); //TODO proper throw
    }
    else {
        data[(_height+1)*(_width+1)] = _pixel;
    }
}*/
