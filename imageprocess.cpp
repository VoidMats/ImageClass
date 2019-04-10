#include "imageprocess.h"

ImageProcess::ImageProcess(const Image &_image):
    org{_image},mod{_image}
{

}

/* This function will write over the modified image to the original
 * after this processed image can't go back to original
 *
 *  */
void ImageProcess::setProcess()
{
    org = mod;
}

/* This function will write over the original image to the modified
 * which can make new process function.
 *    */
void ImageProcess::resetProcess()
{
    mod = org;
}


void ImageProcess::binarisation(COLOR _color, uint8_t _threshold)
{
    size_t height = org.getHeight();
    size_t width = org.getWidth();

    for (size_t h=0; h<height; h++ ) {
        for( size_t w=0; w<width; w++ ) {
            Pixel pix = org.getPixel(h,w);
            if( pix.getColor(_color) >= _threshold ) // TODO Has to be checked
                pix.setColor(_color, 0);
            else {
                pix.setColor(_color, COLORMAX);
            }
            mod.setPixel(h,w,pix);
        }
    }
}

void ImageProcess::linearColorManipulation(COLOR _color, uint8_t _threshold)
{
    size_t height = org.getHeight();
    size_t width = org.getWidth();

    for (size_t h=0; h<height; h++ ) {
        for( size_t w=0; w<width; w++ ) {
            Pixel pix = org.getPixel(h,w);
            if( pix.getColor(_color) >= _threshold )
                pix.setColor(_color, 0);
            else {
                uint8_t value = COLORMAX/_threshold;
                pix.setColor(_color, value);
            }
            mod.setPixel(h,w,pix);
        }
    }
}

/* This will manipulate the color according to a table. The table has to be 255
 * @_color [COLOR]
 * @_table [uint8_t[255]]
 */
void ImageProcess::nonlinearColorManipulation(COLOR _color, std::array<uint8_t,COLORMAX> _table)
{
    size_t height = org.getHeight();
    size_t width = org.getWidth();

    for (size_t h=0; h<height; h++ ) {
        for( size_t w=0; w<width; w++ ) {
            Pixel pix = org.getPixel(h,w);
            pix.setColor(_color, _table.at(pix.getColor(_color)));
            mod.setPixel(h,w,pix);
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
    // TODO add factor
    size_t height = org.getHeight();
    size_t width = org.getWidth();

    for (size_t h=1; h<height-1; h++ ) {
        for( size_t w=1; w<width-1; w++ ) {
            Pixel pixA{ org.getPixel(h,w-1) };
            Pixel pixB{ org.getPixel(h,w+1) };
            Pixel pixC{ org.getPixel(h-1,w) };
            Pixel pixD{ org.getPixel(h+1,w) };

            uint8_t result = static_cast<uint8_t>(
                    ( abs(pixA.getColor(_color)-pixB.getColor(_color)) +
                      abs(pixC.getColor(_color)-pixD.getColor(_color)) ) / 2 );

            Pixel pix{ org.getPixel(h,w) };
            pix.setColor(_color, result);
            mod.setPixel(height,width,pix);
        }
    }

}
