#ifndef SRC_FILTERS_CROP_H
#define SRC_FILTERS_CROP_H

#include "base_filter.h"
#include "utils.h"

namespace image_processor {

// Crop filter
class Crop : public BaseFilter {
public:  // ===== Constructors =====
    Crop(size_t h, size_t w) : nh_(h), nw_(w) {
    }

public:  // ===== Common member functions =====
    BMPImage& Apply(BMPImage& bmp) const override;

public:  // ===== Getters =====
    size_t GetNewHeight() const {
        return nh_;
    }

    size_t GetNewWidth() const {
        return nw_;
    }

public:  // ===== Static member functions =====
    // Creates `BaseFilter*` of type `Crop` from descriptor `d`
    // `std::invalid_argument` is thrown when `descriptor.name` is not `crop`
    // `image_processor::utils::InvalidDescriptor` is thrown when descriptor is invalid
    static BaseFilter* Make(const FilterDescriptor& d);

    static void CheckDescriptor(const FilterDescriptor& d);

public:  // ===== Member constants =====
    static const std::string FILTER_NAME;
    static const size_t PARAMS_COUNT;

protected:  // ===== Private members =====
    size_t nh_;
    size_t nw_;
};

}  // namespace image_processor

#endif  // SRC_FILTERS_CROP_H