#include "base_filter.h"

#include <exception>
#include <stdexcept>

image_processor::ConvolutionFilter::ConvolutionFilter(const Matrix& m) : m_{m} {
    if (m.empty() || m[0].empty() || m.size() % 2 == 0 || m[0].size() % 2 == 0) {
        throw std::invalid_argument("Convolution matrix must have odd non-zero dimensions.");
    }
}

image_processor::BMPImage& image_processor::ConvolutionFilter::Convolute(BMPImage& img) const {
    BMPImage orig(img);
    for (size_t i = 0; i < orig.GetHeight(); ++i) {
        for (size_t j = 0; j < orig.GetWidth(); ++j) {
            img.At(i, j) = ApplyMatrix(orig, i, j);
        }
    }
    return img;
}

image_processor::BMPImage::PixelType image_processor::ConvolutionFilter::ApplyMatrix(const BMPImage& img, size_t row,
                                                                                     size_t col) const {
    double b_res = 0;
    double g_res = 0;
    double r_res = 0;

    const size_t rows = m_.size();
    const size_t cols = m_[0].size();
    const int64_t row_center = static_cast<int64_t>(rows) / 2;
    const int64_t col_center = static_cast<int64_t>(cols) / 2;

    for (size_t i = 0; i < m_.size(); ++i) {
        size_t real_i = FixCoord(static_cast<int64_t>(i) - row_center + static_cast<int64_t>(row), img.GetHeight());
        for (size_t j = 0; j < m_[i].size(); ++j) {
            size_t real_j = FixCoord(static_cast<int64_t>(j) - col_center + static_cast<int64_t>(col), img.GetWidth());
            b_res += m_[i][j] * img.At(real_i, real_j).blue;
            g_res += m_[i][j] * img.At(real_i, real_j).green;
            r_res += m_[i][j] * img.At(real_i, real_j).red;
        }
    }
    return {ToPixelVal(b_res), ToPixelVal(g_res), ToPixelVal(r_res)};
}

size_t image_processor::ConvolutionFilter::FixCoord(int64_t coord, size_t limit) const {
    if (coord < 0) {
        return 0;
    }
    if (coord >= limit) {
        return limit - 1;
    }
    return static_cast<size_t>(coord);
}