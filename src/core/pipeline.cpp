#include "pipeline.h"

image_processor::Pipeline::~Pipeline() {
    for (BaseFilter* flt : filters_) {
        delete flt;
    }
}

image_processor::BMPImage& image_processor::Pipeline::Apply(image_processor::BMPImage& img) const {
    for (BaseFilter* flt : filters_) {
        flt->Apply(img);
    }
    return img;
}