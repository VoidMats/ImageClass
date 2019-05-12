#include "imageprocess.h"

ImageProcess::ImageProcess(const Image &_image):
    org{_image},mod{_image}
{

}

ImageProcess::~ImageProcess()
{

}

/* This function will write over the modified image to the original
 * after this processed image can't go back to original
 *
 *
 */
void ImageProcess::setProcess()
{
    org = mod;
}

/* This function will write over the original image to the modified
 * which can make new process function.
 *
 */
void ImageProcess::resetProcess()
{
    mod = org;
}

Image ImageProcess::getOriginalImage()
{
    return org;
}

Image ImageProcess::getProcessImage()
{
    return mod;
}

void ImageProcess::convToGray()
{
    mod.convGray();
}

/* Function will do a binarisation of the image
 * @_color [COLOR]
 * @_threshold [uint8_t]
 *
 * B2(i,j) = fi,j( B1(i,j) ) where f=threshold
 *
 *         B2   Threshold
 *  B2(2)  |    ______
 *         |    |
 *         |    |
 *  B2(1)  |____|
 *         |__________ B1
 */
void ImageProcess::binarisation(COLOR _color,
                                uint8_t _threshold,
                                uint8_t _min,
                                uint8_t _max)
{
    size_t height = org.getHeight();
    size_t width = org.getWidth();

    for (size_t h=0; h<height; h++ ) {
        for( size_t w=0; w<width; w++ ) {
            Pixel pix = org.getPixel(w, h);
            if( pix.getColor(_color) <= _threshold )
                pix.setColor(_color, _min);
            else {
                pix.setColor(_color, _max);
            }
            mod.setPixel(w, h, pix);
        }
    }
}

/* This will manipulate the color with a linear relation up to the threshold
 * @_color [COLOR]
 * @_threshold [uint8_t]
 *
 * B2(i,j) = fi,j( B1(i,j) ) where f is linear f=k*x
 *
 *         B2   Threshold
 *  Outmax |    ______
 *         |   /|
 *         |  / |
 *         | /  |
 *         |/_________ B1
 */
void ImageProcess::linearColorManipulation(COLOR _color, uint8_t _threshold)
{
    size_t height = org.getHeight();
    size_t width = org.getWidth();

    // Calculate k value
    uint8_t k = COLORMAX/_threshold;
    // Loop through picture
    for (size_t h=0; h<height; h++ ) {
        for( size_t w=0; w<width; w++ ) {
            Pixel pix = org.getPixel(w, h);
            if( pix.getColor(_color) <= _threshold ) {
                //uint8_t value = k * pix.getColor(_color);
                pix.setColor(_color, k * pix.getColor(_color));
            } else {
                pix.setColor(_color, COLORMAX);
            }
            mod.setPixel(w, h, pix);
        }
    }
}

/* This will manipulate the color according to a table. The table has to have a size of 255
 * @_color [COLOR]
 * @_table [uint8_t[255]]
 *
 *         B2      Threshold
 *          |          ______
 *  Outmax  |          |
 *          |      ____|
 *          |   ___|
 *          |  /
 *          |_/______________ B1
 */
void ImageProcess::nonlinearColorManipulation(COLOR _color, std::array<uint8_t,COLORMAX+1> _table)
{
    size_t height = org.getHeight();
    size_t width = org.getWidth();

    for (size_t h=0; h<height; h++ ) {
        for( size_t w=0; w<width; w++ ) {
            Pixel pix = org.getPixel(w, h);
            //int color = static_cast<int>(pix.getColor(_color));
            //if( color>static_cast<int>(COLORMAX) )
            //    color = COLORMAX;
            //std::cout << color << " ";
            uint8_t value = _table.at(pix.getColor(_color));
            pix.setColor(_color, value);
            mod.setPixel(w, h, pix);
        }
    }
}

/* This will manipulate the image with a filter according to a submatrix
 * @_color  [COLOR]
 * @_factor [uint8_t]
 *
 *  [ ][c][ ]
 *  [a][x][b] formula B2(i,j)=( (|a-b|+|c-d|)/2 ) for all i,j
 *  [ ][d][ ]
 */
void ImageProcess::pointDifferentFilter(COLOR _color, uint8_t _factor)
{
    size_t height = org.getHeight();
    size_t width = org.getWidth();

    for (size_t h=1; h<height-1; h++ ) {
        for( size_t w=1; w<width-1; w++ ) {
            Pixel pixA{ org.getPixel(w-1, h) };
            Pixel pixB{ org.getPixel(w+1, h) };
            Pixel pixC{ org.getPixel(w, h-1) };
            Pixel pixD{ org.getPixel(w, h+1) };

            uint8_t result = static_cast<uint8_t>(
                    ( abs(pixA.getColor(_color)-pixB.getColor(_color)) +
                      abs(pixC.getColor(_color)-pixD.getColor(_color)) ) / 2 );
            result = static_cast<uint8_t>(result * _factor);
            if( result>COLORMAX )
                result = COLORMAX;

            Pixel pix{ org.getPixel(w,h) };
            pix.setColor(_color, result);
            mod.setPixel(w, h, pix);
        }
    }

}

/* This will manipulate the image with a filter according to a submatrix
 * @_color  [COLOR]
 *
 *  size kxl (3x3)
 *  [1][1][1]
 *  [1][1][1] formula B2(i,j)= f(k,l) * B1(i+k,j+l)
 *  [1][1][1]
 */
void ImageProcess::meanFilter(COLOR _color)
{
    size_t height = org.getHeight();
    size_t width = org.getWidth();

    for (size_t h=1; h<height-1; h++ ) {
        for ( size_t w=1; w<width-1; w++ ) {
            // Internal loop for submatrix
            size_t value{0};
            for (int k=-1; k<=1; ++k) {
                for (int l=-1; l<=1; ++l) {
                    value += 1*org.getPixel(w+k,h+l).getColor(_color);
                }
            }
            Pixel pix = org.getPixel(w,h);
            pix.setColor(_color,static_cast<uint8_t>(value/9));
            mod.setPixel(w,h,pix);
        }
    }
}

/* This will manipulate the image with a filter according to a submatrix
 * @_color  [COLOR]
 *
 *  size kxl (3x3)
 *  [a][b][c]
 *  [d][e][f] Formula: B2(i,j) = medianValueFromB1(i+k,j+l)
 *  [g][h][m]
 *
 *  ex: 2,2,4,6,8,9,12,23,23 => 8
 */
void ImageProcess::medianFilter(COLOR _color)
{
    size_t height = org.getHeight();
    size_t width = org.getWidth();

    for (size_t h=1; h<height-1; h++ ) {
        for ( size_t w=1; w<width-1; w++ ) {
            std::vector<uint8_t> vec;
            // Internal loop for submatrix
            for (int k=-1; k<=1; ++k) {
                for (int l=-1; l<=1; ++l) {
                    vec.push_back(org.getPixel(w+k,h+l).getColor(_color));
                }
            }
            std::sort(vec.begin(), vec.end());
            Pixel pix = org.getPixel(w,h);
            pix.setColor(_color,static_cast<uint8_t>(vec.at(4)));
            mod.setPixel(w,h,pix);
        }
    }
}

/* This will manipulate the image with a filter according to a submatrix
 * @_color  [COLOR]
 *
 *  size kxl (3x3)
 *  [0][-1][0]
 *  [-1][4][-1] formula B2(i,j)= f(k,l) * B1(i+k,j+l)
 *  [0][-1][0]
 */
void ImageProcess::laplaceFilter(COLOR _color)
{
    size_t height = org.getHeight();
    size_t width = org.getWidth();
    std::vector<int> sub{0,-1,0,-1,4,-1,0,-1,0};

    for (size_t h=1; h<height-1; h++ ) {
        for ( size_t w=1; w<width-1; w++ ) {
            // Internal loop for submatrix
            int value{0};
            for (int k=-1; k<=1; ++k) {
                for (int l=-1; l<=1; ++l) {
                    int tmp = org.getPixel(w+k,h+l).getColor(_color);
                    tmp = sub.at((k+1)*2 + (l+1))*tmp;
                    value += tmp;
                }
            }
            Pixel pix = org.getPixel(w,h);
            pix.setColor(_color,static_cast<uint8_t>(value/9));
            mod.setPixel(w,h,pix);
        }
    }
}

/* This will manipulate the image with a filter according to a submatrix
 * @_color  [COLOR]
 *
 *  size kxl (3x3)
 *  [0][-1][0]
 *  [-1][5][-1] formula B2(i,j)= f(k,l) * B1(i+k,j+l)
 *  [0][-1][0]
 */
void ImageProcess::contrastEnhancementFilter(COLOR _color)
{
    size_t height = org.getHeight();
    size_t width = org.getWidth();
    std::vector<int> sub{0,-1,0,-1,5,-1,0,-1,0};

    for (size_t h=1; h<height-1; h++ ) {
        for ( size_t w=1; w<width-1; w++ ) {
            // Internal loop for submatrix
            int value{0};
            for (int k=-1; k<=1; ++k) {
                for (int l=-1; l<=1; ++l) {
                    int tmp = org.getPixel(w+k,h+l).getColor(_color);
                    tmp = sub.at((k+1)*2 + (l+1))*tmp;
                    value += tmp;
                }
            }
            Pixel pix = org.getPixel(w,h);
            pix.setColor(_color,static_cast<uint8_t>(value/9));
            mod.setPixel(w,h,pix);
        }
    }
}
