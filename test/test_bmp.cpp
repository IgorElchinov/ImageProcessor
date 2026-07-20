#include "bmp.h"

#include <cassert>
#include <iostream>
#include <vector>

using BMP = image_processor::BMPImage;
using image_processor::utils::EnumClassToInteger;

const std::string PATH = "test/data/";

void TestConvolutionFilterDefaultConstructor() {
    std::cout << __func__ << std::endl;

    BMP img;

    std::cout << "passed" << std::endl;
}

void TestGetters() {
    std::cout << __func__ << std::endl;

    BMP img;
    assert(img.GetBitmap() == BMP::Bitmap{});
    assert(img.GetWidth() == 0);
    assert(img.GetHeight() == 0);
    assert(img.GetColorPlanes() == BMP::DEFAULT_COLOR_PLANES);
    assert(img.GetBitsPerPixel() == BMP::DEFAULT_BITS_PER_PIXEL);
    assert(img.GetCompressionMethod() == BMP::CompressionMethod::BI_RGB);
    assert(img.GetHorizontalResolution() == BMP::DEFAULT_HORIZONTAL_RESOLUTION);
    assert(img.GetVerticalResolution() == BMP::DEFAULT_VERTICAL_RESOLUTION);
    assert(img.GetColorsInPalette() == BMP::DEFAULT_COLORS_IN_PALETTE);
    assert(img.GetImportantColors() == BMP::DEFAULT_IMPORTANT_COLORS);

    std::cout << "passed" << std::endl;
}

void TestWidthHeightConstructor(size_t w, size_t h) {
    std::cout << __func__ << " with h=" << h << " w=" << w << std::endl;

    const BMP::Bitmap DATA(h, BMP::Bitmap::value_type(w));

    BMP img(w, h);
    assert(img.GetBitmap() == DATA);
    assert(img.GetWidth() == w);
    assert(img.GetHeight() == h);
    assert(img.GetColorPlanes() == BMP::DEFAULT_COLOR_PLANES);
    assert(img.GetBitsPerPixel() == BMP::DEFAULT_BITS_PER_PIXEL);
    assert(img.GetCompressionMethod() == BMP::CompressionMethod::BI_RGB);
    assert(img.GetHorizontalResolution() == BMP::DEFAULT_HORIZONTAL_RESOLUTION);
    assert(img.GetVerticalResolution() == BMP::DEFAULT_VERTICAL_RESOLUTION);
    assert(img.GetColorsInPalette() == BMP::DEFAULT_COLORS_IN_PALETTE);
    assert(img.GetImportantColors() == BMP::DEFAULT_IMPORTANT_COLORS);

    std::cout << "passed" << std::endl;
}

void TestSetColorPlanes(uint8_t color_planes) {
    std::cout << __func__ << " with color planes=" << static_cast<int>(color_planes) << std::endl;

    size_t W = 42;
    size_t H = 52;
    const BMP::Bitmap DATA(H, BMP::Bitmap::value_type(W));

    BMP img(W, H);
    img.SetColorPlanes(color_planes);

    assert(img.GetBitmap() == DATA);
    assert(img.GetWidth() == W);
    assert(img.GetHeight() == H);
    assert(img.GetColorPlanes() == color_planes);
    assert(img.GetBitsPerPixel() == BMP::DEFAULT_BITS_PER_PIXEL);
    assert(img.GetCompressionMethod() == BMP::CompressionMethod::BI_RGB);
    assert(img.GetHorizontalResolution() == BMP::DEFAULT_HORIZONTAL_RESOLUTION);
    assert(img.GetVerticalResolution() == BMP::DEFAULT_VERTICAL_RESOLUTION);
    assert(img.GetColorsInPalette() == BMP::DEFAULT_COLORS_IN_PALETTE);
    assert(img.GetImportantColors() == BMP::DEFAULT_IMPORTANT_COLORS);

    std::cout << "passed" << std::endl;
}

void TestSetCompressionMethod(BMP::CompressionMethod method) {
    std::cout << __func__ << " with compression method=" << BMP::COMPRESSION_TYPES[EnumClassToInteger(method)]
              << std::endl;

    size_t W = 42;
    size_t H = 52;
    const BMP::Bitmap DATA(H, BMP::Bitmap::value_type(W));

    BMP img(W, H);
    img.SetCompressionMethod(method);

    assert(img.GetBitmap() == DATA);
    assert(img.GetWidth() == W);
    assert(img.GetHeight() == H);
    assert(img.GetColorPlanes() == BMP::DEFAULT_COLOR_PLANES);
    assert(img.GetBitsPerPixel() == BMP::DEFAULT_BITS_PER_PIXEL);
    assert(img.GetCompressionMethod() == method);
    assert(img.GetHorizontalResolution() == BMP::DEFAULT_HORIZONTAL_RESOLUTION);
    assert(img.GetVerticalResolution() == BMP::DEFAULT_VERTICAL_RESOLUTION);
    assert(img.GetColorsInPalette() == BMP::DEFAULT_COLORS_IN_PALETTE);
    assert(img.GetImportantColors() == BMP::DEFAULT_IMPORTANT_COLORS);

    std::cout << "passed" << std::endl;
}

void TestSetResolution(uint32_t w, uint32_t h) {
    std::cout << __func__ << " with h=" << h << " w=" << w << std::endl;

    size_t W = 42;
    size_t H = 52;
    const BMP::Bitmap DATA(H, BMP::Bitmap::value_type(W));

    BMP img(W, H);
    img.SetHorizontalResolution(h);
    img.SetVerticalResolution(w);
    assert(img.GetBitmap() == DATA);
    assert(img.GetWidth() == W);
    assert(img.GetHeight() == H);
    assert(img.GetColorPlanes() == BMP::DEFAULT_COLOR_PLANES);
    assert(img.GetBitsPerPixel() == BMP::DEFAULT_BITS_PER_PIXEL);
    assert(img.GetCompressionMethod() == BMP::CompressionMethod::BI_RGB);
    assert(img.GetHorizontalResolution() == h);
    assert(img.GetVerticalResolution() == w);
    assert(img.GetColorsInPalette() == BMP::DEFAULT_COLORS_IN_PALETTE);
    assert(img.GetImportantColors() == BMP::DEFAULT_IMPORTANT_COLORS);

    std::cout << "passed" << std::endl;
}

void TestMultipleSetters(size_t w, size_t h, uint8_t color_planes, BMP::CompressionMethod method, uint32_t wr,
                         uint32_t hr) {
    std::cout << __func__ << " with" << "h=" << h << " w=" << w << " color planes=" << color_planes
              << " compression method=" << BMP::COMPRESSION_TYPES[EnumClassToInteger(method)] << " hr=" << hr
              << " wr=" << wr << std::endl;

    const BMP::Bitmap DATA(h, BMP::Bitmap::value_type(w));

    BMP img(w, h);
    img.SetHorizontalResolution(h)
        .SetVerticalResolution(w)
        .SetColorPlanes(color_planes)
        .SetCompressionMethod(method)
        .SetHorizontalResolution(hr)
        .SetVerticalResolution(wr);
    assert(img.GetBitmap() == DATA);
    assert(img.GetWidth() == w);
    assert(img.GetHeight() == h);
    assert(img.GetColorPlanes() == color_planes);
    assert(img.GetBitsPerPixel() == BMP::DEFAULT_BITS_PER_PIXEL);
    assert(img.GetCompressionMethod() == BMP::CompressionMethod::BI_RGB);
    assert(img.GetHorizontalResolution() == hr);
    assert(img.GetVerticalResolution() == wr);
    assert(img.GetColorsInPalette() == BMP::DEFAULT_COLORS_IN_PALETTE);
    assert(img.GetImportantColors() == BMP::DEFAULT_IMPORTANT_COLORS);

    std::cout << "passed" << std::endl;
}

void TestAt() {
    std::cout << __func__ << std::endl;

    BMP img(4, 5);
    img.At(0, 0).red = 255;
    img.At(1, 0).green = 255;
    img.At(0, 1).blue = 255;

    assert((img.At(0, 0) == BMP::PixelType{.red = 255, .green = 0, .blue = 0}));
    assert((img.At(1, 0) == BMP::PixelType{.red = 0, .green = 255, .blue = 0}));
    assert((img.At(0, 1) == BMP::PixelType{.red = 0, .green = 0, .blue = 255}));

    std::cout << "passed" << std::endl;
}

void TestConstAt() {
    std::cout << __func__ << std::endl;

    BMP img(4, 5);
    img.At(0, 0).red = 255;
    img.At(1, 0).green = 255;
    img.At(0, 1).blue = 255;

    const BMP img2 = img;

    assert((img2.At(0, 0) == BMP::PixelType{.red = 255, .green = 0, .blue = 0}));
    assert((img2.At(1, 0) == BMP::PixelType{.red = 0, .green = 255, .blue = 0}));
    assert((img2.At(0, 1) == BMP::PixelType{.red = 0, .green = 0, .blue = 255}));

    std::cout << "passed" << std::endl;
}

void TestToString(size_t w, size_t h, uint8_t color_planes, BMP::CompressionMethod method, uint32_t wr, uint32_t hr) {
    std::cout << __func__ << " with" << "h=" << h << " w=" << w << " color planes=" << color_planes
              << " compression method=" << BMP::COMPRESSION_TYPES[EnumClassToInteger(method)] << " hr=" << hr
              << " wr=" << wr << std::endl;

    const BMP::Bitmap DATA(h, BMP::Bitmap::value_type(w));

    BMP img(w, h);
    img.SetHorizontalResolution(h)
        .SetVerticalResolution(w)
        .SetColorPlanes(color_planes)
        .SetCompressionMethod(method)
        .SetHorizontalResolution(hr)
        .SetVerticalResolution(wr);
    std::cout << img << std::endl;

    std::cout << "passed" << std::endl;
}

void TestToStringWithFill(size_t w, size_t h, uint8_t color_planes, BMP::CompressionMethod method, uint32_t wr,
                          uint32_t hr, uint8_t rfill, uint8_t gfill, uint8_t bfill) {
    std::cout << __func__ << " with" << "h=" << h << " w=" << w << " color planes=" << color_planes
              << " compression method=" << BMP::COMPRESSION_TYPES[EnumClassToInteger(method)] << " hr=" << hr
              << " wr=" << wr << std::endl;

    const BMP::Bitmap DATA(h, BMP::Bitmap::value_type(w));

    BMP img(w, h);
    img.SetHorizontalResolution(h)
        .SetVerticalResolution(w)
        .SetColorPlanes(color_planes)
        .SetCompressionMethod(method)
        .SetHorizontalResolution(hr)
        .SetVerticalResolution(wr);

    for (size_t i = 0; i < h; ++i) {
        for (size_t j = 0; j < w; ++j) {
            img.At(i, j) = {.red = rfill, .green = gfill, .blue = bfill};
        }
    }
    std::cout << img << std::endl;

    std::cout << "passed" << std::endl;
}

void TestResizeHorizontalShrink() {
    std::cout << __func__ << std::endl;

    size_t h = 6;
    size_t w = 5;
    image_processor::BMPImage img(w, h);
    std::vector<std::vector<image_processor::Pixel>> data{
        {{1, 0, 1}, {2, 0, 1}, {3, 0, 1}, {4, 0, 1}, {5, 0, 1}},
        {{1, 0, 2}, {2, 0, 2}, {3, 0, 2}, {4, 0, 2}, {5, 0, 2}},
        {{1, 0, 3}, {2, 0, 3}, {3, 0, 3}, {4, 0, 3}, {5, 0, 3}},
        {{1, 0, 4}, {2, 0, 4}, {3, 0, 4}, {4, 0, 4}, {5, 0, 4}},
        {{1, 0, 5}, {2, 0, 5}, {3, 0, 5}, {4, 0, 5}, {5, 0, 5}},
        {{1, 0, 6}, {2, 0, 6}, {3, 0, 6}, {4, 0, 6}, {5, 0, 6}},
    };
    for (size_t i = 0; i < h; ++i) {
        for (size_t j = 0; j < w; ++j) {
            img.At(i, j) = data[i][j];
        }
    }
    assert(img.GetWidth() == w);
    assert(img.GetHeight() == h);
    assert(img.GetBitmap() == data);

    size_t nw = 3;
    std::vector<std::vector<image_processor::Pixel>> new_data{
        {{1, 0, 1}, {2, 0, 1}, {3, 0, 1}}, {{1, 0, 2}, {2, 0, 2}, {3, 0, 2}}, {{1, 0, 3}, {2, 0, 3}, {3, 0, 3}},
        {{1, 0, 4}, {2, 0, 4}, {3, 0, 4}}, {{1, 0, 5}, {2, 0, 5}, {3, 0, 5}}, {{1, 0, 6}, {2, 0, 6}, {3, 0, 6}},
    };
    img.ResizeHorizontal(nw);

    assert(img.GetWidth() == nw);
    assert(img.GetHeight() == h);
    assert(img.GetBitmap() == new_data);

    std::cout << "passed" << std::endl;
}

void TestResizeHorizontalEnlarge() {
    std::cout << __func__ << std::endl;

    size_t h = 6;
    size_t w = 5;
    image_processor::BMPImage img(w, h);
    std::vector<std::vector<image_processor::Pixel>> data{
        {{1, 0, 1}, {2, 0, 1}, {3, 0, 1}, {4, 0, 1}, {5, 0, 1}},
        {{1, 0, 2}, {2, 0, 2}, {3, 0, 2}, {4, 0, 2}, {5, 0, 2}},
        {{1, 0, 3}, {2, 0, 3}, {3, 0, 3}, {4, 0, 3}, {5, 0, 3}},
        {{1, 0, 4}, {2, 0, 4}, {3, 0, 4}, {4, 0, 4}, {5, 0, 4}},
        {{1, 0, 5}, {2, 0, 5}, {3, 0, 5}, {4, 0, 5}, {5, 0, 5}},
        {{1, 0, 6}, {2, 0, 6}, {3, 0, 6}, {4, 0, 6}, {5, 0, 6}},
    };
    for (size_t i = 0; i < h; ++i) {
        for (size_t j = 0; j < w; ++j) {
            img.At(i, j) = data[i][j];
        }
    }
    assert(img.GetWidth() == w);
    assert(img.GetHeight() == h);
    assert(img.GetBitmap() == data);

    size_t nw = 7;
    std::vector<std::vector<image_processor::Pixel>> new_data{
        {{1, 0, 1}, {2, 0, 1}, {3, 0, 1}, {4, 0, 1}, {5, 0, 1}, {0, 0, 0}, {0, 0, 0}},
        {{1, 0, 2}, {2, 0, 2}, {3, 0, 2}, {4, 0, 2}, {5, 0, 2}, {0, 0, 0}, {0, 0, 0}},
        {{1, 0, 3}, {2, 0, 3}, {3, 0, 3}, {4, 0, 3}, {5, 0, 3}, {0, 0, 0}, {0, 0, 0}},
        {{1, 0, 4}, {2, 0, 4}, {3, 0, 4}, {4, 0, 4}, {5, 0, 4}, {0, 0, 0}, {0, 0, 0}},
        {{1, 0, 5}, {2, 0, 5}, {3, 0, 5}, {4, 0, 5}, {5, 0, 5}, {0, 0, 0}, {0, 0, 0}},
        {{1, 0, 6}, {2, 0, 6}, {3, 0, 6}, {4, 0, 6}, {5, 0, 6}, {0, 0, 0}, {0, 0, 0}},
    };
    img.ResizeHorizontal(nw);

    assert(img.GetWidth() == nw);
    assert(img.GetHeight() == h);
    assert(img.GetBitmap() == new_data);

    std::cout << "passed" << std::endl;
}

void TestResizeVerticalShrink() {
    std::cout << __func__ << std::endl;

    size_t h = 6;
    size_t w = 5;
    image_processor::BMPImage img(w, h);
    std::vector<std::vector<image_processor::Pixel>> data{
        {{1, 0, 1}, {2, 0, 1}, {3, 0, 1}, {4, 0, 1}, {5, 0, 1}},
        {{1, 0, 2}, {2, 0, 2}, {3, 0, 2}, {4, 0, 2}, {5, 0, 2}},
        {{1, 0, 3}, {2, 0, 3}, {3, 0, 3}, {4, 0, 3}, {5, 0, 3}},
        {{1, 0, 4}, {2, 0, 4}, {3, 0, 4}, {4, 0, 4}, {5, 0, 4}},
        {{1, 0, 5}, {2, 0, 5}, {3, 0, 5}, {4, 0, 5}, {5, 0, 5}},
        {{1, 0, 6}, {2, 0, 6}, {3, 0, 6}, {4, 0, 6}, {5, 0, 6}},
    };
    for (size_t i = 0; i < h; ++i) {
        for (size_t j = 0; j < w; ++j) {
            img.At(i, j) = data[i][j];
        }
    }
    assert(img.GetWidth() == w);
    assert(img.GetHeight() == h);
    assert(img.GetBitmap() == data);

    size_t nh = 3;
    std::vector<std::vector<image_processor::Pixel>> new_data{
        {{1, 0, 1}, {2, 0, 1}, {3, 0, 1}, {4, 0, 1}, {5, 0, 1}},
        {{1, 0, 2}, {2, 0, 2}, {3, 0, 2}, {4, 0, 2}, {5, 0, 2}},
        {{1, 0, 3}, {2, 0, 3}, {3, 0, 3}, {4, 0, 3}, {5, 0, 3}},
    };
    img.ResizeVertical(nh);

    assert(img.GetWidth() == w);
    assert(img.GetHeight() == nh);
    assert(img.GetBitmap() == new_data);

    std::cout << "passed" << std::endl;
}

void TestResizeVerticalEnlarge() {
    std::cout << __func__ << std::endl;

    size_t h = 6;
    size_t w = 5;
    image_processor::BMPImage img(w, h);
    std::vector<std::vector<image_processor::Pixel>> data{
        {{1, 0, 1}, {2, 0, 1}, {3, 0, 1}, {4, 0, 1}, {5, 0, 1}},
        {{1, 0, 2}, {2, 0, 2}, {3, 0, 2}, {4, 0, 2}, {5, 0, 2}},
        {{1, 0, 3}, {2, 0, 3}, {3, 0, 3}, {4, 0, 3}, {5, 0, 3}},
        {{1, 0, 4}, {2, 0, 4}, {3, 0, 4}, {4, 0, 4}, {5, 0, 4}},
        {{1, 0, 5}, {2, 0, 5}, {3, 0, 5}, {4, 0, 5}, {5, 0, 5}},
        {{1, 0, 6}, {2, 0, 6}, {3, 0, 6}, {4, 0, 6}, {5, 0, 6}},
    };
    for (size_t i = 0; i < h; ++i) {
        for (size_t j = 0; j < w; ++j) {
            img.At(i, j) = data[i][j];
        }
    }
    assert(img.GetWidth() == w);
    assert(img.GetHeight() == h);
    assert(img.GetBitmap() == data);

    size_t nh = 10;
    std::vector<std::vector<image_processor::Pixel>> new_data{
        {{1, 0, 1}, {2, 0, 1}, {3, 0, 1}, {4, 0, 1}, {5, 0, 1}},
        {{1, 0, 2}, {2, 0, 2}, {3, 0, 2}, {4, 0, 2}, {5, 0, 2}},
        {{1, 0, 3}, {2, 0, 3}, {3, 0, 3}, {4, 0, 3}, {5, 0, 3}},
        {{1, 0, 4}, {2, 0, 4}, {3, 0, 4}, {4, 0, 4}, {5, 0, 4}},
        {{1, 0, 5}, {2, 0, 5}, {3, 0, 5}, {4, 0, 5}, {5, 0, 5}},
        {{1, 0, 6}, {2, 0, 6}, {3, 0, 6}, {4, 0, 6}, {5, 0, 6}},
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    };
    img.ResizeVertical(nh);

    assert(img.GetWidth() == w);
    assert(img.GetHeight() == nh);
    assert(img.GetBitmap() == new_data);

    std::cout << "passed" << std::endl;
}

void TestNegPixel() {
    std::cout << __func__ << std::endl;

    image_processor::Pixel p{42, 52, 69};
    image_processor::Pixel np{255 - 42, 255 - 52, 255 - 69};
    assert(~p == np);

    std::cout << "passed" << std::endl;
}

void TestPrintImage(const std::string& filename) {
    std::cout << __func__ << std::endl;

    image_processor::BMPImage img = image_processor::ReadBMP(PATH + filename);
    std::cout << img << std::endl;

    std::cout << "passed" << std::endl;
}

int main(int argc, char* argv[]) {
    std::cout << "test_bmp" << std::endl;

    TestConvolutionFilterDefaultConstructor();
    TestGetters();

    TestWidthHeightConstructor(1, 2);
    TestWidthHeightConstructor(5, 7);
    TestWidthHeightConstructor(3, 3);

    TestSetColorPlanes(1);
    TestSetColorPlanes(2);

    TestSetCompressionMethod(BMP::CompressionMethod::BI_RGB);
    TestSetCompressionMethod(BMP::CompressionMethod::BI_RLE4);
    TestSetCompressionMethod(BMP::CompressionMethod::BI_PNG);

    TestSetResolution(1, 2);
    TestSetResolution(4, 7);
    TestSetResolution(2, 9);

    TestMultipleSetters(42, 17, 1, BMP::CompressionMethod::BI_RGB, 2, 3);

    TestAt();
    TestConstAt();

    TestToString(5, 7, 1, BMP::CompressionMethod::BI_RGB, 2, 3);
    TestToStringWithFill(9, 4, 3, BMP::CompressionMethod::BI_RLE4, 1, 1, 42, 52, 69);

    TestResizeHorizontalShrink();
    TestResizeHorizontalEnlarge();
    TestResizeVerticalShrink();
    TestResizeVerticalEnlarge();

    TestNegPixel();

    std::vector<std::string> files = {
        "flag.bmp",
        "flag_edge.bmp",
        "flag_edge_edge.bmp",
        "out.bmp",
    };
    for (const std::string& file : files) {
        TestPrintImage(file);
    }

    std::cout << "finished" << std::endl;
    return 0;
}