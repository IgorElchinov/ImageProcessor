#ifndef SRC_CORE_BMP_H
#define SRC_CORE_BMP_H

#include <cstdint>
#include <map>
#include <string>
#include <sstream>
#include <tuple>
#include <vector>

#include "utils.h"

namespace image_processor {

// Structure to hold pixel.
struct Pixel {
    uint8_t blue = 0;
    uint8_t green = 0;
    uint8_t red = 0;

    static const uint8_t MAX_PIXEL_VAL;

    bool operator==(const Pixel& other) const;
    Pixel operator~() const {
        return Pixel{static_cast<uint8_t>(~blue), static_cast<uint8_t>(~green), static_cast<uint8_t>(~red)};
    }
};

std::ostream& operator<<(std::ostream& os, const Pixel& p);

// BMP image class.
// Holds both pixel values and metadata.
class BMPImage {
public:  // ===== Member types =====
    using Bitmap = std::vector<std::vector<Pixel>>;
    using PixelType = Pixel;

    enum class CompressionMethod : uint32_t {
        BI_RGB,
        BI_RLE8,
        BI_RLE4,
        BI_BITFIELDS,
        BI_JPEG,
        BI_PNG,
    };

public:  // ===== Constructors & destructor =====
    BMPImage() : BMPImage(0, 0) {
    }

    BMPImage(size_t width, size_t height)
        : data_(height, Bitmap::value_type(width)),
          width_{width},
          height_{height},
          color_planes_{DEFAULT_COLOR_PLANES},
          bits_per_pixel_{DEFAULT_BITS_PER_PIXEL},
          compression_method_{CompressionMethod::BI_RGB},
          horizontal_resolution_{DEFAULT_HORIZONTAL_RESOLUTION},
          vertical_resolution_{DEFAULT_VERTICAL_RESOLUTION},
          colors_in_palette_{DEFAULT_COLORS_IN_PALETTE},
          important_colors_{DEFAULT_IMPORTANT_COLORS} {
    }

    BMPImage(const BMPImage& other) = default;
    BMPImage(BMPImage&& other) noexcept = default;
    BMPImage& operator=(const BMPImage& other) = default;
    BMPImage& operator=(BMPImage&& other) noexcept = default;
    ~BMPImage() = default;

public:  // ===== Operators =====
    // Compares sizes and pixel values
    bool operator==(const image_processor::BMPImage& other) const {
        return width_ == other.width_ && height_ == other.height_ && data_ == other.data_;
    }

public:  // ===== Common member functions =====
    // Pixel access by 2 indexes
    Pixel& At(size_t h, size_t w) {
        return data_[h][w];
    }
    // Pixel access by 2 indexes
    Pixel At(size_t h, size_t w) const {
        return data_[h][w];
    }

    // Converts BMP image to the string representation
    std::string ToString() const;

    // Resizes image along horizontal axis. Fills new pixels with zeros if `count` > `cur.GetWidth()`
    void ResizeHorizontal(size_t count);

    // Resizes image along vertical axis. Fills new pixels with zeros if `count` > `cur.GetHeight()`
    void ResizeVertical(size_t count);

public:  // ===== Getters =====
    const Bitmap& GetBitmap() const {
        return data_;
    }

    size_t GetWidth() const {
        return width_;
    }

    size_t GetHeight() const {
        return height_;
    }

    uint16_t GetColorPlanes() const {
        return color_planes_;
    }

    uint16_t GetBitsPerPixel() const {
        return bits_per_pixel_;
    }

    CompressionMethod GetCompressionMethod() const {
        return compression_method_;
    }

    int32_t GetHorizontalResolution() const {
        return horizontal_resolution_;
    }

    int32_t GetVerticalResolution() const {
        return vertical_resolution_;
    }

    uint32_t GetColorsInPalette() const {
        return colors_in_palette_;
    }

    uint32_t GetImportantColors() const {
        return important_colors_;
    }

    const Bitmap::value_type& GetRow(size_t row) const {
        return data_[row];
    }

    Bitmap::value_type& GetRow(size_t row) {
        return data_[row];
    }

public:  // ===== Setters =====
    BMPImage& SetColorPlanes(uint16_t color_planes) {
        color_planes_ = color_planes;
        return *this;
    }

    BMPImage& SetBitsPerPixel(uint16_t bits_per_pixel) {
        bits_per_pixel_ = bits_per_pixel;
        return *this;
    }

    BMPImage& SetCompressionMethod(CompressionMethod compression_method) {
        compression_method_ = compression_method;
        return *this;
    }

    BMPImage& SetHorizontalResolution(int32_t horizontal_resolution) {
        horizontal_resolution_ = horizontal_resolution;
        return *this;
    }

    BMPImage& SetVerticalResolution(int32_t vertical_resolution) {
        vertical_resolution_ = vertical_resolution;
        return *this;
    }

    BMPImage& SetColorsInPalette(uint32_t colors_in_palette) {
        colors_in_palette_ = colors_in_palette;
        return *this;
    }

    BMPImage& SetImportantColors(uint32_t important_colors) {
        important_colors_ = important_colors;
        return *this;
    }

public:  // ===== Member constants =====
    static const uint8_t DEFAULT_COLOR_PLANES;
    static const uint8_t DEFAULT_BITS_PER_PIXEL;
    static const int32_t DEFAULT_HORIZONTAL_RESOLUTION;
    static const int32_t DEFAULT_VERTICAL_RESOLUTION;
    static const uint32_t DEFAULT_COLORS_IN_PALETTE;
    static const uint32_t DEFAULT_IMPORTANT_COLORS;
    static const std::vector<std::string> COMPRESSION_TYPES;

protected:  // ===== Main image data =====
    Bitmap data_;
    size_t width_;
    size_t height_;

protected:  // ===== Image metadata (currently useless, added for scalability) =====
    uint16_t color_planes_;
    uint16_t bits_per_pixel_;
    CompressionMethod compression_method_;
    int32_t horizontal_resolution_;
    int32_t vertical_resolution_;
    uint32_t colors_in_palette_;
    uint32_t important_colors_;
};

std::ostream& operator<<(std::ostream& os, const BMPImage& img);

// Reads BMP image from `file`, `std::runtime_error` is thrown if problem occurs
BMPImage ReadBMP(const std::string& file);
// Writes BMP image `bmp` to `file`, `std::runtime_error` is thrown if problem occurs
void WriteBMP(const std::string& file, const BMPImage& bmp);
};  // namespace image_processor

#endif  // SRC_CORE_BMP_H