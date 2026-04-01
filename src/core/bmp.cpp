#include "bmp.h"

#include <climits>
#include <exception>
#include <fstream>
#include <tuple>
#include <iostream>

#include "utils.h"

const uint8_t image_processor::Pixel::MAX_PIXEL_VAL = 0xffu;

const uint8_t image_processor::BMPImage::DEFAULT_COLOR_PLANES = 1;
const uint8_t image_processor::BMPImage::DEFAULT_BITS_PER_PIXEL = 24;
const int32_t image_processor::BMPImage::DEFAULT_HORIZONTAL_RESOLUTION = 0;
const int32_t image_processor::BMPImage::DEFAULT_VERTICAL_RESOLUTION = 0;
const uint32_t image_processor::BMPImage::DEFAULT_COLORS_IN_PALETTE = 0;
const uint32_t image_processor::BMPImage::DEFAULT_IMPORTANT_COLORS = 0;
const std::vector<std::string> image_processor::BMPImage::COMPRESSION_TYPES = {
    "BI_RGB", "BI_RLE8", "BI_RLE4", "BI_BITFIELDS", "BI_JPEG", "BI_PNG",
};

bool image_processor::Pixel::operator==(const image_processor::Pixel& other) const {
    return std::tie(red, green, blue) == std::tie(other.red, other.green, other.blue);
}

std::ostream& image_processor::operator<<(std::ostream& os, const image_processor::Pixel& p) {
    os << "(b=" << static_cast<int>(p.blue) << ",g=" << static_cast<int>(p.green) << ",r=" << static_cast<int>(p.red)
       << ")";
    return os;
}

std::string image_processor::BMPImage::ToString() const {
    std::stringstream s;
    s << "===== BMP Image =====" << std::endl;
    s << "=== Metadata ===" << std::endl;
    s << "color planes = " << static_cast<int>(color_planes_) << std::endl;
    s << "bits per pixel = " << static_cast<int>(bits_per_pixel_) << std::endl;
    s << "compression method = " << COMPRESSION_TYPES[utils::EnumClassToInteger(compression_method_)] << std::endl;
    s << "horizontal resolution = " << static_cast<size_t>(horizontal_resolution_) << std::endl;
    s << "vertical resolution = " << static_cast<size_t>(vertical_resolution_) << std::endl;
    s << "colors in palette = " << static_cast<int>(colors_in_palette_) << std::endl;
    s << "important colors = " << static_cast<int>(important_colors_) << std::endl;
    s << "=== Image ===" << std::endl;
    s << "width = " << width_ << std::endl;
    s << "height = " << height_ << std::endl;
    for (const Bitmap::value_type& row : data_) {
        for (Pixel p : row) {
            s << p << " ";
        }
        s << std::endl;
    }
    return s.str();
}

void image_processor::BMPImage::ResizeHorizontal(size_t count) {
    for (Bitmap::value_type& row : data_) {
        row.resize(count, {0, 0, 0});
    }
    width_ = count;
}

void image_processor::BMPImage::ResizeVertical(size_t count) {
    data_.resize(count, Bitmap::value_type(width_, {0, 0, 0}));
    height_ = count;
}

std::ostream& image_processor::operator<<(std::ostream& os, const image_processor::BMPImage& img) {
    os << img.ToString();
    return os;
}

// ReadBMP auxilary functions

// Reads value of integral type `T` to variable `res` from input file stream `f` (little-endian, `false` is returned if
// failed)
template <typename T>
static bool ReadInt(std::ifstream& f, T& res) {
    static_assert(std::is_integral_v<T>, "ReadInt can be used only with integral types");
    char buff[sizeof(res)];
    f.read(buff, static_cast<std::streamsize>(sizeof(res)));
    if (f.gcount() != sizeof(res)) {
        return false;
    }
    using U = std::make_unsigned_t<T>;
    U temp = 0;
    for (size_t i = 0; i < sizeof(res); ++i) {
        temp |= static_cast<uint8_t>(buff[i]) << (i * CHAR_BIT);
    }
    res = static_cast<T>(temp);
    return true;
}

// Reads value of enum class `E` to variable `res` from input file stream `f` (little-endian, `false` is returned if
// failed)
template <typename E>
static bool ReadEnum(std::ifstream& f, E& res) {
    static_assert(std::is_enum_v<E>, "ReadEnum can be used only with enum types");
    using Underlying = std::underlying_type_t<E>;

    Underlying temp;
    if (!ReadInt(f, temp)) {
        return false;
    }
    res = static_cast<E>(temp);
    return true;
}

static const uint32_t HEADER_FIELD_SIZE = 2;
static const char CORRECT_HEADER_FIELD_VALUE[2] = {'B', 'M'};
static const uint32_t DIB_HEADER_OFFSET = 14;
static const uint32_t DIB_HEADER_SIZE = 40;
static const uint32_t MINIMAL_BITMAP_OFFSET = DIB_HEADER_OFFSET + DIB_HEADER_SIZE;
static const uint32_t MAX_PADDING = 4;

enum class ReadBMPHeaderResult {
    OK,
    WRONG_HEADER_FIELD,
    SMALL_FILE,
};

static const char* const READ_BMP_HEADER_MESSAGES[3] = {
    "OK",
    "Given file is not a valid BMP: wrong header field.",
    "Given file is not a valid BMP: too small file.",
};

struct [[gnu::packed]] BMPHeaderInfo {
    char header_field[HEADER_FIELD_SIZE];
    uint32_t file_size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t bitmap_offset;
};

static ReadBMPHeaderResult ReadBMPHeaderResultReinterpretInternal(std::istream& f, BMPHeaderInfo& res) {
    f.read(reinterpret_cast<char*>(&res), sizeof(res));
    if (f.gcount() != sizeof(res)) {
        return ReadBMPHeaderResult::SMALL_FILE;
    }
    if (res.header_field[0] != CORRECT_HEADER_FIELD_VALUE[0] || res.header_field[1] != CORRECT_HEADER_FIELD_VALUE[1]) {
        return ReadBMPHeaderResult::WRONG_HEADER_FIELD;
    }
    return ReadBMPHeaderResult::OK;
}

static ReadBMPHeaderResult ReadBMPHeaderResultReinterpret(std::ifstream& f, BMPHeaderInfo& res) {
    f.seekg(0, std::ios::beg);
    ReadBMPHeaderResult result = ReadBMPHeaderResultReinterpretInternal(f, res);
    f.seekg(0, std::ios::beg);
    return result;
}

enum class ReadDIBHeaderResult {
    OK,
    WRONG_HEADER_SIZE,
    SMALL_FILE,
};

static const char* const READ_DIB_HEADER_MESSAGES[3] = {
    "OK",
    "Given file is not a valid BMP: wrong header size.",
    "Given file is not a valid BMP: too small file.",
};

struct [[gnu::packed]] DIBHeaderInfo {
    uint32_t header_size;
    int32_t width;
    int32_t height;
    uint16_t color_planes;
    uint16_t bits_per_pixel;
    image_processor::BMPImage::CompressionMethod compression_method;
    uint32_t bitmap_size;
    int32_t horizontal_resolution;
    int32_t vertical_resolution;
    uint32_t colors_in_palette;
    uint32_t important_colors;
};

static ReadDIBHeaderResult ReadDIBHeaderReinterpretInternal(std::istream& f, DIBHeaderInfo& res) {
    f.read(reinterpret_cast<char*>(&res), sizeof(res));
    if (f.gcount() != sizeof(res)) {
        return ReadDIBHeaderResult::SMALL_FILE;
    }
    if (res.header_size != DIB_HEADER_SIZE) {
        return ReadDIBHeaderResult::WRONG_HEADER_SIZE;
    }
    return ReadDIBHeaderResult::OK;
}

static ReadDIBHeaderResult ReadDIBHeaderReinterpret(std::ifstream& f, DIBHeaderInfo& res) {
    f.seekg(DIB_HEADER_OFFSET, std::ios::beg);
    ReadDIBHeaderResult result = ReadDIBHeaderReinterpretInternal(f, res);
    f.seekg(0, std::ios::beg);
    return result;
}

enum class ReadBitmapResult {
    OK,
    SMALL_FILE,
};

// Reads bitmap into `res` from the beginning of `f`. Returns pointer to the beginning of `f`
static ReadBitmapResult ReadBitmap(std::ifstream& f, size_t bitmap_offset, size_t padding,
                                   image_processor::BMPImage& img) {
    f.seekg(static_cast<std::streamoff>(bitmap_offset), std::ios::beg);
    for (size_t i = 0; i < img.GetHeight(); ++i) {
        for (size_t j = 0; j < img.GetWidth(); ++j) {
            if (!ReadInt(f, img.At(i, j).blue)) {
                return ReadBitmapResult::SMALL_FILE;
            }
            if (!ReadInt(f, img.At(i, j).green)) {
                return ReadBitmapResult::SMALL_FILE;
            }
            if (!ReadInt(f, img.At(i, j).red)) {
                return ReadBitmapResult::SMALL_FILE;
            }
        }
        f.seekg(static_cast<std::streamoff>(padding), std::ios::cur);
    }
    f.seekg(0, std::ios::beg);
    return ReadBitmapResult::OK;
}

static ReadBitmapResult ReadBitmapReversedReinterpretInternal(std::istream& f, size_t padding,
                                                              image_processor::BMPImage& img) {
    size_t row_size = img.GetWidth() * 3;
    for (size_t i = img.GetHeight() - 1; i != -1; --i) {
        f.read(reinterpret_cast<char*>(img.GetRow(i).data()), static_cast<std::streamsize>(row_size));
        if (f.gcount() != row_size) {
            return ReadBitmapResult::SMALL_FILE;
        }
        char pad[MAX_PADDING] = {0};
        f.read(pad, static_cast<std::streamsize>(padding));
        if (f.gcount() != padding) {
            return ReadBitmapResult::SMALL_FILE;
        }
    }
    return ReadBitmapResult::OK;
}

static ReadBitmapResult ReadBitmapReversedReinterpret(std::ifstream& f, size_t bitmap_offset, size_t padding,
                                                      image_processor::BMPImage& img) {
    f.seekg(static_cast<std::streamoff>(bitmap_offset), std::ios::beg);
    ReadBitmapResult result = ReadBitmapReversedReinterpretInternal(f, padding, img);
    f.seekg(0, std::ios::beg);
    return result;
}

static const size_t BITMAP_ROW_ALIGNMENT = 4;

static size_t CalculatePadding(const DIBHeaderInfo& dib) {
    size_t real_len = dib.width * (dib.bits_per_pixel / CHAR_BIT);
    if (real_len == 0 || real_len % BITMAP_ROW_ALIGNMENT == 0) {
        return 0;
    }
    return BITMAP_ROW_ALIGNMENT - real_len % BITMAP_ROW_ALIGNMENT;
}

image_processor::BMPImage image_processor::ReadBMP(const std::string& filename) {
    using image_processor::utils::EnumClassToInteger;

    std::ifstream f(filename, std::ios::binary);
    if (!f.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    BMPHeaderInfo head;
    ReadBMPHeaderResult head_res = ReadBMPHeaderResultReinterpret(f, head);

    if (head_res != ReadBMPHeaderResult::OK) {
        throw std::runtime_error(READ_BMP_HEADER_MESSAGES[EnumClassToInteger(head_res)]);
    }
    if (head.file_size < MINIMAL_BITMAP_OFFSET) {
        throw std::runtime_error("Given file is not a valid BMP: too small file.");
    }
    if (head.bitmap_offset < MINIMAL_BITMAP_OFFSET) {
        throw std::runtime_error("Given file is not a valid BMP: too small bitmap offset.");
    }

    DIBHeaderInfo dib;
    ReadDIBHeaderResult dib_res = ReadDIBHeaderReinterpret(f, dib);

    if (dib_res != ReadDIBHeaderResult::OK) {
        throw std::runtime_error(READ_DIB_HEADER_MESSAGES[EnumClassToInteger(dib_res)]);
    }
    bool reversed = true;
    if (static_cast<int32_t>(dib.height) < 0) {
        reversed = false;
        dib.height *= -1;
    }

    image_processor::BMPImage img(dib.width, dib.height);
    if (dib.color_planes != image_processor::BMPImage::DEFAULT_COLOR_PLANES) {
        throw std::runtime_error("Given file has unsupported number of color planes.");
    } else {
        img.SetColorPlanes(dib.color_planes);
    }
    if (dib.bits_per_pixel != image_processor::BMPImage::DEFAULT_BITS_PER_PIXEL) {
        throw std::runtime_error("Given file has unsupported bits per pixel value.");
    } else {
        img.SetBitsPerPixel(dib.bits_per_pixel);
    }
    if (dib.compression_method != image_processor::BMPImage::CompressionMethod::BI_RGB) {
        throw std::runtime_error("Given file has unsupported compression method.");
    } else {
        img.SetCompressionMethod(dib.compression_method);
    }
    img.SetHorizontalResolution(dib.horizontal_resolution);
    img.SetVerticalResolution(dib.vertical_resolution);
    if (dib.colors_in_palette != image_processor::BMPImage::DEFAULT_COLORS_IN_PALETTE) {
        throw std::runtime_error("Given file has unsupported number of colors in palette.");
    } else {
        img.SetColorsInPalette(dib.colors_in_palette);
    }
    if (dib.important_colors != image_processor::BMPImage::DEFAULT_IMPORTANT_COLORS) {
        throw std::runtime_error("Given file has unsupported number of important colors.");
    } else {
        img.SetImportantColors(dib.important_colors);
    }

    ReadBitmapResult bitmap_res = ReadBitmapResult{0};
    if (reversed) {
        bitmap_res = ReadBitmapReversedReinterpret(f, head.bitmap_offset, CalculatePadding(dib), img);
    } else {
        bitmap_res = ReadBitmap(f, head.bitmap_offset, CalculatePadding(dib), img);
    }
    if (bitmap_res != ReadBitmapResult::OK) {
        throw std::runtime_error("Given file is not a valid BMP: too small file.");
    }
    return img;
}

static const uint8_t ONE_BYTE = 0xffu;

// Writes value `val` of integral type `T` to output file stream `f` (little-endian)
template <typename T>
static void WriteInt(std::ofstream& f, T val) {
    static_assert(std::is_integral_v<T>, "WriteInt can be used only with integral types");
    char buff[sizeof(T)];
    using U = std::make_unsigned_t<T>;
    U tmp = static_cast<U>(val);
    for (size_t i = 0; i < sizeof(T); ++i) {
        buff[i] = static_cast<char>((tmp >> (i * CHAR_BIT)) & ONE_BYTE);
    }
    f.write(buff, static_cast<std::streamsize>(sizeof(T)));
};

// Writes value `val` of enum class `E` to output file stream `f` (little-endian)
template <typename E>
static void WriteEnum(std::ofstream& f, E val) {
    static_assert(std::is_enum_v<E>, "WriteEnum can be used only with enum class");
    using Underlying = std::underlying_type_t<E>;
    Underlying tmp = static_cast<Underlying>(val);
    WriteInt(f, tmp);
};

static void WriteBMPHeaderReinterpretInternal(std::ostream& f, const BMPHeaderInfo& header) {
    f.seekp(0, std::ios::beg);
    f.write(reinterpret_cast<const char*>(&header), sizeof(header));
    f.seekp(0, std::ios::beg);
}

static void WriteBMPHeaderReinterpret(std::ofstream& f, const BMPHeaderInfo& header) {
    f.seekp(0, std::ios::beg);
    WriteBMPHeaderReinterpretInternal(f, header);
    f.seekp(0, std::ios::beg);
}

static void WriteDIBHeaderReinterpretInternal(std::ostream& f, const DIBHeaderInfo& dib) {
    f.seekp(DIB_HEADER_OFFSET, std::ios::beg);
    f.write(reinterpret_cast<const char*>(&dib), sizeof(dib));
    f.seekp(0, std::ios::beg);
}

static void WriteDIBHeaderReinterpret(std::ofstream& f, const DIBHeaderInfo& dib) {
    f.seekp(DIB_HEADER_OFFSET, std::ios::beg);
    WriteDIBHeaderReinterpretInternal(f, dib);
    f.seekp(0, std::ios::beg);
}

static void WriteBitmapReinterpretInternal(std::ofstream& f, size_t padding, const image_processor::BMPImage& img) {
    const char pad[3] = {0, 0, 0};
    for (size_t i = img.GetHeight() - 1; i != -1; --i) {
        size_t row_size = img.GetWidth() * 3;
        f.write(reinterpret_cast<const char*>(img.GetRow(i).data()), static_cast<std::streamsize>(row_size));
        f.write(pad, static_cast<std::streamsize>(padding));
    }
}

static void WriteBitmapReinterpret(std::ofstream& f, size_t offset, size_t padding,
                                   const image_processor::BMPImage& img) {
    f.seekp(static_cast<std::streamoff>(offset), std::ios::beg);
    WriteBitmapReinterpretInternal(f, padding, img);
    f.seekp(0, std::ios::beg);
}

static uint32_t CalculateBitmapSize(const DIBHeaderInfo& dib) {
    uint32_t row_size = dib.width * dib.bits_per_pixel / CHAR_BIT + CalculatePadding(dib);
    return dib.height * row_size;
}

void image_processor::WriteBMP(const std::string& filename, const image_processor::BMPImage& img) {
    std::ofstream f(filename, std::ios::binary);
    if (!f.is_open()) {
        throw std::runtime_error("Could not open file.");
    }
    DIBHeaderInfo dib = {
        .header_size = DIB_HEADER_SIZE,
        .width = static_cast<int32_t>(img.GetWidth()),
        .height = static_cast<int32_t>(img.GetHeight()),
        .color_planes = img.GetColorPlanes(),
        .bits_per_pixel = img.GetBitsPerPixel(),
        .compression_method = img.GetCompressionMethod(),
        .bitmap_size = 0,
        .horizontal_resolution = img.GetHorizontalResolution(),
        .vertical_resolution = img.GetVerticalResolution(),
        .colors_in_palette = img.GetColorsInPalette(),
        .important_colors = img.GetImportantColors(),
    };
    dib.bitmap_size = CalculateBitmapSize(dib);
    BMPHeaderInfo header = {
        .header_field = "",
        .file_size = MINIMAL_BITMAP_OFFSET + dib.bitmap_size,
        .reserved1 = 0,
        .reserved2 = 0,
        .bitmap_offset = MINIMAL_BITMAP_OFFSET,
    };
    header.header_field[0] = CORRECT_HEADER_FIELD_VALUE[0];
    header.header_field[1] = CORRECT_HEADER_FIELD_VALUE[1];
    WriteBMPHeaderReinterpret(f, header);
    WriteDIBHeaderReinterpret(f, dib);
    WriteBitmapReinterpret(f, header.bitmap_offset, CalculatePadding(dib), img);
}
