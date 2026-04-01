#ifndef SRC_FILTERS_SHARPENING_H
#define SRC_FILTERS_SHARPENING_H

#include "base_filter.h"

namespace image_processor {

// Sharpening filter
class Sharpening : public ConvolutionFilter {
public:  // ===== Constructors =====
    Sharpening() : ConvolutionFilter(MATRIX){};
    Sharpening(const Sharpening& other) = default;
    Sharpening(Sharpening&& other) = default;
    Sharpening& operator=(const Sharpening& other) = default;
    Sharpening& operator=(Sharpening&& other) = default;

public:  // ===== Member constants =====
    static const Matrix MATRIX;
};

}  // namespace image_processor

#endif  // SRC_FILTERS_SHARPENING_H