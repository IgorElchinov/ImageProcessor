#include "test_utils.h"

image_processor::BMPImage test_utils::CreateImage(size_t h, size_t w, image_processor::BMPImage::Bitmap data) {
    image_processor::BMPImage img(w, h);
    for (size_t i = 0; i < h; ++i) {
        for (size_t j = 0; j < w; ++j) {
            img.At(i, j) = data[i][j];
        }
    }
    return img;
}