#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include "utils.h"
#include "bmp.h"

namespace test_utils {

::image_processor::BMPImage CreateImage(size_t h, size_t w, ::image_processor::BMPImage::Bitmap data);

}  // namespace test_utils

#endif  // TEST_UTILS_H