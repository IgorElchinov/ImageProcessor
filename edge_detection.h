#ifndef SRC_FILTERS_EDGE_DETECTION_H
#define SRC_FILTERS_EDGE_DETECTION_H

#include "base_filter.h"
#include "bmp.h"
#include "grayscale.h"

namespace image_processor {

// Edge detection filter
class EdgeDetection : public BaseFilter {
public:  // ===== Member types =====
    // Class to apply edge detection on previously grayscaled image
    class Detector : public ConvolutionFilter {
    public:  // ===== Constructors =====
        explicit Detector(double threshold)
            : ConvolutionFilter(MATRIX), threshold_(threshold * BMPImage::PixelType::MAX_PIXEL_VAL) {
        }
        Detector(const Detector& other) = default;
        Detector(Detector&& other) = default;
        Detector& operator=(const Detector& other) = default;
        Detector& operator=(Detector&& other) = default;

    public:  // ===== Getters =====
        double GetThreshold() const {
            return threshold_;
        }

    public:  // ===== Member constants =====
        static const Matrix MATRIX;

    protected:  // ===== Private member functions =====
        // Checks if val is too large or too small
        uint8_t ToPixelVal(double val) const override;

    protected:  // ===== Private members =====
        double threshold_;
    };

public:  // ===== Constructors =====
    explicit EdgeDetection(double threshold) : gs_(), detector_(threshold) {
    }
    EdgeDetection(const EdgeDetection& other) = default;
    EdgeDetection(EdgeDetection&& other) = default;
    EdgeDetection& operator=(const EdgeDetection& other) = default;
    EdgeDetection& operator=(EdgeDetection&& other) = default;

public:  // ===== Common member functions =====
    BMPImage& Apply(BMPImage& img) const override {
        return detector_.Apply(gs_.Apply(img));
    }

public:  // ===== Getters =====
    double GetThreshold() const {
        return detector_.GetThreshold();
    }

protected:  // ===== Private members =====
    Grayscale gs_;
    Detector detector_;
};

}  // namespace image_processor

#endif  // SRC_FILTERS_EDGE_DETECTION_H