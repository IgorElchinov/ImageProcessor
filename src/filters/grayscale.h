#ifndef SRC_FILTERS_GRAYSCALE_H
#define SRC_FILTERS_GRAYSCALE_H

#include "base_filter.h"

namespace image_processor {

// Grayscale filter
class Grayscale : public BaseFilter {
public:  // ===== Common methods =====
    BMPImage& Apply(BMPImage& img) const override;

public:  // ===== Member constants =====
    static const double RED_CHANNEL_FACTOR;
    static const double GREEN_CHANNEL_FACTOR;
    static const double BLUE_CHANNEL_FACTOR;
};

}  // namespace image_processor

#endif  // SRC_FILTERS_GRAYSCALE_H