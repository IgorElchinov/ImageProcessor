#include "edge_detection.h"
#include "utils.h"

const image_processor::EdgeDetection::Detector::Matrix image_processor::EdgeDetection::Detector::MATRIX = {
    {0, -1, 0},
    {-1, 4, -1},
    {0, -1, 0},
};

uint8_t image_processor::EdgeDetection::Detector::ToPixelVal(double val) const {
    if (val > threshold_) {
        return BMPImage::PixelType::MAX_PIXEL_VAL;
    } else {
        return 0;
    }
}
