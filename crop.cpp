#include "crop.h"

#include <exception>
#include <stdexcept>

#include "utils.h"

image_processor::BMPImage& image_processor::Crop::Apply(image_processor::BMPImage& bmp) const {
    if (nh_ < bmp.GetHeight()) {
        bmp.ResizeVertical(nh_);
    }
    if (nw_ < bmp.GetWidth()) {
        bmp.ResizeHorizontal(nw_);
    }
    return bmp;
}
