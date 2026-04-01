#include "compress.h"

image_processor::BMPImage& image_processor::Compress::Apply(BMPImage& img) const {
    img.SetCompressionMethod(BMPImage::CompressionMethod::BI_RLE4);
    return img;
}

const std::string image_processor::Compress::FILTER_NAME = "compress";
const size_t image_processor::Compress::PARAMS_COUNT = 0;

void image_processor::Compress::CheckDescriptor(const FilterDescriptor& d) {
    if (d.name != FILTER_NAME) {
        throw std::invalid_argument("Filter name mismatch: compress expected, " + d.name + " given.");
    }
    if (d.params.size() != PARAMS_COUNT) {
        throw image_processor::utils::InvalidDescriptor(
            "Wrong number of parameters for compress: " + std::to_string(PARAMS_COUNT) + " expected, " +
            std::to_string(d.params.size()) + " given.");
    }
}

image_processor::BaseFilter* image_processor::Compress::Make(const image_processor::FilterDescriptor& d) {
    CheckDescriptor(d);
    return new Compress();
}

image_processor::BMPImage& image_processor::Decompress::Apply(BMPImage& img) const {
    img.SetCompressionMethod(BMPImage::CompressionMethod::BI_RGB);
    return img;
}

const std::string image_processor::Decompress::FILTER_NAME = "decompress";
const size_t image_processor::Decompress::PARAMS_COUNT = 0;

void image_processor::Decompress::CheckDescriptor(const FilterDescriptor& d) {
    if (d.name != FILTER_NAME) {
        throw std::invalid_argument("Filter name mismatch: decompress expected, " + d.name + " given.");
    }
    if (d.params.size() != PARAMS_COUNT) {
        throw image_processor::utils::InvalidDescriptor(
            "Wrong number of parameters for decompress: " + std::to_string(PARAMS_COUNT) + " expected, " +
            std::to_string(d.params.size()) + " given.");
    }
}

image_processor::BaseFilter* image_processor::Decompress::Make(const image_processor::FilterDescriptor& d) {
    CheckDescriptor(d);
    return new Decompress();
}