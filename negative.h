#ifndef SRC_FILTERS_NEGATIVE_H
#define SRC_FILTERS_NEGATIVE_H

#include "base_filter.h"

namespace image_processor {

// Negative filter
class Negative : public BaseFilter {
public:  // ===== Common member functions =====
    BMPImage& Apply(BMPImage& bmp) const override;
};

}  // namespace image_processor

#endif  // SRC_FILTERS_NEGATIVE_H