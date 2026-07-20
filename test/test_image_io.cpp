#include <cassert>
#include <exception>
#include <iostream>
#include <vector>

#include "bmp.h"

const std::string path = "test/data/";

void TestReadMissingFile() {
    std::cout << __func__ << std::endl;

    bool was_exception = false;
    const std::string FILENAME = "missing_file.bmp";
    const std::string CORRECT_MESSAGE = "Could not open file";
    try {
        image_processor::BMPImage img = image_processor::ReadBMP(FILENAME);
    } catch (const std::runtime_error& e) {
        std::cout << "Message: '" << e.what() << "'" << std::endl;
        assert(e.what() == CORRECT_MESSAGE);
        was_exception = true;
    }
    assert(was_exception);

    std::cout << "passed" << std::endl << std::endl;
}

void TestReadWrongFormat(const std::string& filename) {
    std::cout << __func__ << " with filename=" << filename << std::endl;

    bool was_exception = false;
    try {
        image_processor::BMPImage img = image_processor::ReadBMP(path + filename);
    } catch (const std::runtime_error& e) {
        std::cout << "Message: '" << e.what() << "'" << std::endl;
        was_exception = true;
    }
    assert(was_exception);

    std::cout << "passed" << std::endl << std::endl;
}

struct DIBHeaderInfo {
    size_t width;
    size_t height;
    uint16_t color_planes;
    uint16_t bits_per_pixel;
    image_processor::BMPImage::CompressionMethod compression_method;
    uint32_t horizontal_resolution;
    uint32_t vertical_resolution;
    uint32_t colors_in_palette;
    uint32_t important_colors;
};

void TestReadCorrectFile(const std::string& filename, const DIBHeaderInfo& bid) {
    std::cout << __func__ << " with filename=" << filename << std::endl;

    image_processor::BMPImage img = image_processor::ReadBMP(path + filename);
    assert(img.GetWidth() == bid.width);
    assert(img.GetHeight() == bid.height);
    assert(img.GetColorPlanes() == bid.color_planes);
    assert(img.GetBitsPerPixel() == bid.bits_per_pixel);
    assert(img.GetCompressionMethod() == bid.compression_method);
    assert(img.GetHorizontalResolution() == bid.horizontal_resolution);
    assert(img.GetVerticalResolution() == bid.vertical_resolution);
    assert(img.GetColorsInPalette() == bid.colors_in_palette);
    assert(img.GetImportantColors() == bid.important_colors);

    std::cout << img << std::endl;

    std::cout << "passed" << std::endl << std::endl;
}

void TestCopy(const std::string& from, const std::string& to) {
    std::cout << __func__ << " with from=" << from << " to=" << to << std::endl;

    image_processor::BMPImage img = image_processor::ReadBMP(path + from);
    image_processor::WriteBMP(path + to, img);

    std::cout << "passed" << std::endl;
}

int main(int argc, char* argv[]) {
    std::cout << "test_image_io" << std::endl;

    TestReadMissingFile();

    std::vector<std::string> wrong_files = {
        "empty.bmp",
        "junk.bmp",
        "small1.bmp",
        "small2.bmp",
        "small3.bmp",
        "small4.bmp",
        "small5.bmp",
        "wrong_header_field.bmp",
        "wrong_dib_header_size.bmp",
    };
    for (const std::string& file : wrong_files) {
        TestReadWrongFormat(file);
    }

    DIBHeaderInfo flag_dib = {
        .width = 10,
        .height = 20,
        .color_planes = 1,
        .bits_per_pixel = 24,
        .compression_method = image_processor::BMPImage::CompressionMethod::BI_RGB,
        .horizontal_resolution = 0,
        .vertical_resolution = 0,
        .colors_in_palette = 0,
        .important_colors = 0,
    };

    DIBHeaderInfo square_dib = {
        .width = 2,
        .height = 2,
        .color_planes = 1,
        .bits_per_pixel = 24,
        .compression_method = image_processor::BMPImage::CompressionMethod::BI_RGB,
        .horizontal_resolution = 2835,
        .vertical_resolution = 2835,
        .colors_in_palette = 0,
        .important_colors = 0,
    };

    std::vector<std::pair<std::string, DIBHeaderInfo>> correct_files = {{"flag.bmp", flag_dib},
                                                                        {"square.bmp", square_dib}};
    for (auto& [file, dib] : correct_files) {
        TestReadCorrectFile(file, dib);
    }

    std::vector<std::pair<std::string, std::string>> files_to_copy{
        {"square.bmp", "square_copy.bmp"}, {"flag.bmp", "flag_copy.bmp"}, {"lenna.bmp", "lenna_copy.bmp"}};
    for (auto& [from, to] : files_to_copy) {
        TestCopy(from, to);
    }

    std::cout << "finished" << std::endl;
    return 0;
}