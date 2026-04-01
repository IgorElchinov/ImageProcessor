#include "negative.h"
#include "bmp.h"

image_processor::BMPImage& image_processor::Negative::Apply(image_processor::BMPImage& bmp) const {
    for (size_t i = 0; i < bmp.GetHeight(); ++i) {
        for (size_t j = 0; j < bmp.GetWidth(); ++j) {
            bmp.At(i, j) = ~bmp.At(i, j);
        }
    }
    return bmp;
}
