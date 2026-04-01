#ifndef SRC_FILTERS_COMPRESS
#define SRC_FILTERS_COMPRESS

#include "base_filter.h"
#include "bmp.h"

namespace image_processor {

class Compress : public BaseFilter {
public:  // ===== Common member functions =====
    BMPImage& Apply(BMPImage& img) const override;

public:  // ===== Static member functions =====
    // Creates `BaseFilter*` of type `Compress` from descriptor `d`
    // `std::invalid_argument` is thrown when `descriptor.name` is not `compress`
    // `image_processor::utils::InvalidDescriptor` is thrown when descriptor is invalid
    static BaseFilter* Make(const image_processor::FilterDescriptor& d);

    static void CheckDescriptor(const image_processor::FilterDescriptor& d);

public:  // ===== Member constants =====
    static const std::string FILTER_NAME;
    static const size_t PARAMS_COUNT;
};

class Decompress : public BaseFilter {
public:  // ===== Common member functions =====
    BMPImage& Apply(BMPImage& img) const override;

public:  // ===== Static member functions =====
    // Creates `BaseFilter*` of type `Decompress` from descriptor `d`
    // `std::invalid_argument` is thrown when `descriptor.name` is not `decompress`
    // `image_processor::utils::InvalidDescriptor` is thrown when descriptor is invalid
    static BaseFilter* Make(const image_processor::FilterDescriptor& d);

    static void CheckDescriptor(const image_processor::FilterDescriptor& d);

public:  // ===== Member constants =====
    static const std::string FILTER_NAME;
    static const size_t PARAMS_COUNT;
};

}  // namespace image_processor

#endif  // SRC_FILTERS_COMPRESS