#ifndef SRC_FILTERS_GAUSSIAN_BLUR_H
#define SRC_FILTERS_GAUSSIAN_BLUR_H

#include "base_filter.h"

#include <vector>
#include <cmath>

namespace image_processor {

// Gaussian blur filter
class GaussianBlur : public BaseFilter {
public:  // ===== Member types =====
    using Convolution1d = std::vector<double>;

public:  // ===== Constructors =====
    explicit GaussianBlur(double sigma)
        : sigma_(sigma), row_filter_(BuildRowFilter(sigma)), col_filter_(BuildColFilter(sigma)) {
    }

public:  // ===== Common member functions =====
    BMPImage& Apply(BMPImage& img) const override {
        return col_filter_.Apply(row_filter_.Apply(img));
    }

public:  // ===== Static member functions =====
    // Computes kernel radius
    static size_t ComputeRadius(double sigma) {
        return std::max(K_SIGMA, static_cast<size_t>(std::ceil(static_cast<double>(K_SIGMA) * sigma)));
    }

    // Builds 1D kernel
    static Convolution1d Build1DKernel(double sigma);

    // Builds row filter
    static ConvolutionFilter BuildRowFilter(double sigma) {
        return ConvolutionFilter({Build1DKernel(sigma)});
    }

    // Builds columns filter
    static ConvolutionFilter BuildColFilter(double sigma);

public:  // ===== Member constants =====
    static const size_t K_SIGMA;
    static const double JUST_RANDOM_NUMBER_FROM_SOME_FORMULA_DOUBLE;
    static const size_t JUST_RANDOM_NUMBER_FROM_SOME_FORMULA_INT;

protected:  // ===== Private members =====
    double sigma_;
    ConvolutionFilter row_filter_;
    ConvolutionFilter col_filter_;
};

}  // namespace image_processor

#endif  // SRC_FILTERS_GAUSSIAN_BLUR_H