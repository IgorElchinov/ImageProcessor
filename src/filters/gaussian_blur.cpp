#include "gaussian_blur.h"

#include <cmath>
#include <numeric>

const size_t image_processor::GaussianBlur::K_SIGMA = 3;
const double image_processor::GaussianBlur::JUST_RANDOM_NUMBER_FROM_SOME_FORMULA_DOUBLE = 2.;
const size_t image_processor::GaussianBlur::JUST_RANDOM_NUMBER_FROM_SOME_FORMULA_INT = 2;

image_processor::GaussianBlur::Convolution1d image_processor::GaussianBlur::Build1DKernel(double sigma) {
    int64_t radius = static_cast<int64_t>(ComputeRadius(sigma));
    size_t size = JUST_RANDOM_NUMBER_FROM_SOME_FORMULA_INT * radius + 1;
    Convolution1d kernel(size);
    double sum = 0.0;
    for (int64_t i = -radius; i <= radius; ++i) {
        double val =
            std::exp(-static_cast<double>(i * i) / (JUST_RANDOM_NUMBER_FROM_SOME_FORMULA_DOUBLE * sigma * sigma));
        kernel[i + radius] = val;
        sum += val;
    }
    for (double& v : kernel) {
        v /= sum;
    }
    return kernel;
}

image_processor::ConvolutionFilter image_processor::GaussianBlur::BuildColFilter(double sigma) {
    Convolution1d kernel1d = Build1DKernel(sigma);
    ConvolutionFilter::Matrix mat(kernel1d.size(), std::vector<double>(1));
    for (size_t i = 0; i < kernel1d.size(); ++i) {
        mat[i][0] = kernel1d[i];
    }
    return ConvolutionFilter(mat);
}
