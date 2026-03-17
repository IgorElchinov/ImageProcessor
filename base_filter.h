#ifndef SRC_FILTERS_BASE_FILTER_H
#define SRC_FILTERS_BASE_FILTER_H

#include <vector>

#include "bmp.h"

namespace image_processor {

// Base class for filters. Each filter class must inherit it
class BaseFilter {
public:  // ===== Destructor =====
    virtual ~BaseFilter() = default;

public:  // ===== Common member functions =====
    // Applies filter to the image `img` (in-place)
    virtual BMPImage& Apply(BMPImage& img) const = 0;
};

// Base class for convolution filters. Each convolution filter class must inherit it
class ConvolutionFilter : public BaseFilter {
public:  // ===== Member types =====
    using Matrix = std::vector<std::vector<double>>;

public:  // ===== Constructors =====
    // May throw `std::invalid_argument` if either dimension of `m` is zero or even
    explicit ConvolutionFilter(const Matrix& m);

    ConvolutionFilter(const ConvolutionFilter& other) = default;
    ConvolutionFilter(ConvolutionFilter&& other) = default;
    ConvolutionFilter& operator=(const ConvolutionFilter& other) = default;
    ConvolutionFilter& operator=(ConvolutionFilter&& other) = default;
    ~ConvolutionFilter() override = default;

public:  // ===== Common member functions =====
    BMPImage& Apply(BMPImage& bmp) const override {
        return Convolute(bmp);
    }

public:  // ===== Getters =====
    const Matrix& GetMatrix() const {
        return m_;
    }

protected:  // ===== Private member functions =====
    // Applies convolution to `img` (in-place)
    virtual BMPImage& Convolute(BMPImage& img) const;

    // Applies convolution to a single pixel
    virtual BMPImage::PixelType ApplyMatrix(const BMPImage& img, size_t row, size_t col) const;

    // Converts `val` from `double` to `uint8_t` (clamped, can be overriden)
    virtual uint8_t ToPixelVal(double val) const {
        return static_cast<uint8_t>(std::min<double>(BMPImage::PixelType::MAX_PIXEL_VAL, std::max<double>(0, val)));
    }

    // Fixes badd coordinated. Returns closest valid pixel
    virtual size_t FixCoord(int64_t coord, size_t limit) const;

protected:  // ===== Private members =====
    Matrix m_;
};

}  // namespace image_processor

#endif  // SRC_FILTERS_BASE_FILTER_H