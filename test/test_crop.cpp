#include <cassert>
#include <iostream>

#include "bmp.h"
#include "crop.h"
#include "factory.h"

void TestConvolutionFilterDefaultConstructor() {
    std::cout << __func__ << std::endl;

    // image_processor::Crop flt; // Should not compile

    std::cout << "passed" << std::endl;
}

void TestTwoNumbersConstructor() {
    std::cout << __func__ << std::endl;

    size_t h = 5;
    size_t w = 7;
    image_processor::Crop flt(h, w);

    assert(flt.GetNewHeight() == h);
    assert(flt.GetNewWidth() == w);

    std::cout << "passed" << std::endl;
}

void TestMoveConstructor() {
    std::cout << __func__ << std::endl;

    size_t h = 5;
    size_t w = 7;
    image_processor::Crop flt1(h, w);
    image_processor::Crop flt2(std::move(flt1));

    assert(flt1.GetNewHeight() == flt2.GetNewHeight());
    assert(flt1.GetNewWidth() == flt2.GetNewWidth());

    std::cout << "passed" << std::endl;
}

void TestCopyConstructor() {
    std::cout << __func__ << std::endl;

    size_t h = 5;
    size_t w = 7;
    image_processor::Crop flt1(h, w);
    image_processor::Crop flt2(flt1);

    assert(flt1.GetNewHeight() == flt2.GetNewHeight());
    assert(flt1.GetNewWidth() == flt2.GetNewWidth());

    std::cout << "passed" << std::endl;
}

void TestCopyAssignmentOperator() {
    std::cout << __func__ << std::endl;

    size_t h1 = 5;
    size_t w1 = 7;
    size_t h2 = 3;
    size_t w2 = 9;
    assert(h1 != h2);
    assert(w1 != w2);

    image_processor::Crop flt1(h1, w1);
    assert(flt1.GetNewHeight() == h1);
    assert(flt1.GetNewWidth() == w1);

    image_processor::Crop flt2(h2, w2);
    assert(flt2.GetNewHeight() == h2);
    assert(flt2.GetNewWidth() == w2);

    flt2 = flt1;
    assert(flt1.GetNewHeight() == flt2.GetNewHeight());
    assert(flt1.GetNewWidth() == flt2.GetNewWidth());

    std::cout << "passed" << std::endl;
}

void TestMoveAssignmentOperator() {
    std::cout << __func__ << std::endl;

    size_t h1 = 5;
    size_t w1 = 7;
    size_t h2 = 3;
    size_t w2 = 9;
    assert(h1 != h2);
    assert(w1 != w2);

    image_processor::Crop flt1(h1, w1);
    assert(flt1.GetNewHeight() == h1);
    assert(flt1.GetNewWidth() == w1);

    image_processor::Crop flt2(h2, w2);
    assert(flt2.GetNewHeight() == h2);
    assert(flt2.GetNewWidth() == w2);

    flt2 = std::move(flt1);
    assert(flt1.GetNewHeight() == flt2.GetNewHeight());
    assert(flt1.GetNewWidth() == flt2.GetNewWidth());

    std::cout << "passed" << std::endl;
}

void TestGetters() {
    std::cout << __func__ << std::endl;

    size_t h = 5;
    size_t w = 7;
    image_processor::Crop flt1(h, w);
    const image_processor::Crop& flt2 = flt1;

    assert(flt2.GetNewHeight() == h);
    assert(flt2.GetNewWidth() == w);

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
    assert(nw < w);
    image_processor::Crop flt(h, nw);
    std::vector<std::vector<image_processor::Pixel>> new_data{
        {{1, 0, 1}, {2, 0, 1}, {3, 0, 1}}, {{1, 0, 2}, {2, 0, 2}, {3, 0, 2}}, {{1, 0, 3}, {2, 0, 3}, {3, 0, 3}},
        {{1, 0, 4}, {2, 0, 4}, {3, 0, 4}}, {{1, 0, 5}, {2, 0, 5}, {3, 0, 5}}, {{1, 0, 6}, {2, 0, 6}, {3, 0, 6}},
    };
    flt.Apply(img);

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
    assert(nw > w);
    image_processor::Crop flt(h, nw);
    std::vector<std::vector<image_processor::Pixel>> new_data{
        {{1, 0, 1}, {2, 0, 1}, {3, 0, 1}, {4, 0, 1}, {5, 0, 1}},
        {{1, 0, 2}, {2, 0, 2}, {3, 0, 2}, {4, 0, 2}, {5, 0, 2}},
        {{1, 0, 3}, {2, 0, 3}, {3, 0, 3}, {4, 0, 3}, {5, 0, 3}},
        {{1, 0, 4}, {2, 0, 4}, {3, 0, 4}, {4, 0, 4}, {5, 0, 4}},
        {{1, 0, 5}, {2, 0, 5}, {3, 0, 5}, {4, 0, 5}, {5, 0, 5}},
        {{1, 0, 6}, {2, 0, 6}, {3, 0, 6}, {4, 0, 6}, {5, 0, 6}},
    };
    flt.Apply(img);

    assert(img.GetWidth() == w);
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
    assert(nh < h);
    image_processor::Crop flt(nh, w);
    std::vector<std::vector<image_processor::Pixel>> new_data{
        {{1, 0, 1}, {2, 0, 1}, {3, 0, 1}, {4, 0, 1}, {5, 0, 1}},
        {{1, 0, 2}, {2, 0, 2}, {3, 0, 2}, {4, 0, 2}, {5, 0, 2}},
        {{1, 0, 3}, {2, 0, 3}, {3, 0, 3}, {4, 0, 3}, {5, 0, 3}},
    };
    flt.Apply(img);

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
    assert(nh > h);
    image_processor::Crop flt(nh, w);
    std::vector<std::vector<image_processor::Pixel>> new_data{
        {{1, 0, 1}, {2, 0, 1}, {3, 0, 1}, {4, 0, 1}, {5, 0, 1}},
        {{1, 0, 2}, {2, 0, 2}, {3, 0, 2}, {4, 0, 2}, {5, 0, 2}},
        {{1, 0, 3}, {2, 0, 3}, {3, 0, 3}, {4, 0, 3}, {5, 0, 3}},
        {{1, 0, 4}, {2, 0, 4}, {3, 0, 4}, {4, 0, 4}, {5, 0, 4}},
        {{1, 0, 5}, {2, 0, 5}, {3, 0, 5}, {4, 0, 5}, {5, 0, 5}},
        {{1, 0, 6}, {2, 0, 6}, {3, 0, 6}, {4, 0, 6}, {5, 0, 6}},
    };
    flt.Apply(img);

    assert(img.GetWidth() == w);
    assert(img.GetHeight() == h);
    assert(img.GetBitmap() == new_data);

    std::cout << "passed" << std::endl;
}

void TestResizeBothAxes() {
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

    size_t nh = 4;
    size_t nw = 3;
    image_processor::Crop flt(nh, nw);
    std::vector<std::vector<image_processor::Pixel>> new_data{
        {{1, 0, 1}, {2, 0, 1}, {3, 0, 1}},
        {{1, 0, 2}, {2, 0, 2}, {3, 0, 2}},
        {{1, 0, 3}, {2, 0, 3}, {3, 0, 3}},
        {{1, 0, 4}, {2, 0, 4}, {3, 0, 4}},
    };

    flt.Apply(img);

    assert(img.GetWidth() == nw);
    assert(img.GetHeight() == nh);
    assert(img.GetBitmap() == new_data);

    std::cout << "passed" << std::endl;
}

void TestChain() {
    std::cout << __func__ << std::endl;

    size_t h0 = 6;
    size_t w0 = 5;
    image_processor::BMPImage img(w0, h0);
    std::vector<std::vector<image_processor::Pixel>> data{
        {{1, 0, 1}, {2, 0, 1}, {3, 0, 1}, {4, 0, 1}, {5, 0, 1}},
        {{1, 0, 2}, {2, 0, 2}, {3, 0, 2}, {4, 0, 2}, {5, 0, 2}},
        {{1, 0, 3}, {2, 0, 3}, {3, 0, 3}, {4, 0, 3}, {5, 0, 3}},
        {{1, 0, 4}, {2, 0, 4}, {3, 0, 4}, {4, 0, 4}, {5, 0, 4}},
        {{1, 0, 5}, {2, 0, 5}, {3, 0, 5}, {4, 0, 5}, {5, 0, 5}},
        {{1, 0, 6}, {2, 0, 6}, {3, 0, 6}, {4, 0, 6}, {5, 0, 6}},
    };
    for (size_t i = 0; i < h0; ++i) {
        for (size_t j = 0; j < w0; ++j) {
            img.At(i, j) = data[i][j];
        }
    }
    assert(img.GetWidth() == w0);
    assert(img.GetHeight() == h0);
    assert(img.GetBitmap() == data);

    size_t h1 = 5;
    size_t w1 = 4;
    image_processor::Crop flt1(h1, w1);
    size_t h2 = 4;
    size_t w2 = 3;
    image_processor::Crop flt2(h2, w2);
    std::vector<std::vector<image_processor::Pixel>> new_data{
        {{1, 0, 1}, {2, 0, 1}, {3, 0, 1}},
        {{1, 0, 2}, {2, 0, 2}, {3, 0, 2}},
        {{1, 0, 3}, {2, 0, 3}, {3, 0, 3}},
        {{1, 0, 4}, {2, 0, 4}, {3, 0, 4}},
    };

    flt2.Apply(flt1.Apply(img));

    assert(img.GetWidth() == w2);
    assert(img.GetHeight() == h2);
    assert(img.GetBitmap() == new_data);

    std::cout << "passed" << std::endl;
}

void TestMakerFunctionValid() {
    std::cout << __func__ << std::endl;

    image_processor::FilterDescriptor d = {.name = "crop", .params = {"3", "4"}};
    image_processor::BaseFilter* flt = image_processor::FilterFactory::MAKE_FILTER.at("crop")(d);

    assert(flt);

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

    size_t nh = 4;
    size_t nw = 3;
    std::vector<std::vector<image_processor::Pixel>> new_data{
        {{1, 0, 1}, {2, 0, 1}, {3, 0, 1}},
        {{1, 0, 2}, {2, 0, 2}, {3, 0, 2}},
        {{1, 0, 3}, {2, 0, 3}, {3, 0, 3}},
        {{1, 0, 4}, {2, 0, 4}, {3, 0, 4}},
    };

    flt->Apply(img);

    assert(img.GetWidth() == nw);
    assert(img.GetHeight() == nh);
    assert(img.GetBitmap() == new_data);

    delete flt;

    std::cout << "passed" << std::endl;
}

void TestMakerFunctionWrongParamsCount() {
    std::cout << __func__ << std::endl;

    bool expected = false;

    try {
        image_processor::FilterDescriptor d = {.name = "crop", .params = {"3", "4", "5"}};
        image_processor::BaseFilter* flt = image_processor::FilterFactory::MAKE_FILTER.at("crop")(d);
        image_processor::BMPImage empty;
        flt->Apply(empty);
    } catch (image_processor::utils::InvalidDescriptor& e) {
        std::string correct_msg = "Wrong number of parameters for crop: 2 expected.";
        assert((e.what() == correct_msg));
        expected = true;
    }

    assert(expected);

    std::cout << "passed" << std::endl;
}

void TestMakerFunctionWrongFormat() {
    std::cout << __func__ << std::endl;

    bool expected = false;

    try {
        image_processor::FilterDescriptor d = {.name = "crop", .params = {"3", "4.0"}};
        image_processor::BaseFilter* flt = image_processor::FilterFactory::MAKE_FILTER.at("crop")(d);
        image_processor::BMPImage empty;
        flt->Apply(empty);
    } catch (image_processor::utils::InvalidDescriptor& e) {
        std::string correct_msg = "Wrong type for 1 parameter of crop: integer number expected.";
        assert((e.what() == correct_msg));
        expected = true;
    }

    assert(expected);

    std::cout << "passed" << std::endl;
}

void TestMakerFunctionWrongValue() {
    std::cout << __func__ << std::endl;

    bool expected = false;

    try {
        image_processor::FilterDescriptor d = {.name = "crop", .params = {"-3", "4"}};
        image_processor::BaseFilter* flt = image_processor::FilterFactory::MAKE_FILTER.at("crop")(d);
        image_processor::BMPImage empty;
        flt->Apply(empty);
    } catch (image_processor::utils::InvalidDescriptor& e) {
        std::string correct_msg = "Wrong value for 2 parameter of crop: should be non-negative.";
        assert((e.what() == correct_msg));
        expected = true;
    }

    assert(expected);

    std::cout << "passed" << std::endl;
}

void TestMakerFunctionWrongDescriptor() {
    std::cout << __func__ << std::endl;

    bool expected = false;

    try {
        image_processor::FilterDescriptor d = {.name = "missing-filter", .params = {"42", "foo"}};
        image_processor::BaseFilter* flt = image_processor::FilterFactory::MAKE_FILTER.at("crop")(d);
        image_processor::BMPImage empty;
        flt->Apply(empty);
    } catch (std::invalid_argument& e) {
        std::string correct_msg = "Filter name mismatch: crop expected.";
        assert((e.what() == correct_msg));
        expected = true;
    }

    assert(expected);

    std::cout << "passed" << std::endl;
}

int main(int argc, char* argv[]) {
    std::cout << "test_crop" << std::endl;

    TestConvolutionFilterDefaultConstructor();
    TestTwoNumbersConstructor();
    TestCopyConstructor();
    TestMoveConstructor();
    TestCopyAssignmentOperator();
    TestMoveAssignmentOperator();
    TestGetters();

    TestResizeHorizontalShrink();
    TestResizeHorizontalEnlarge();
    TestResizeVerticalShrink();
    TestResizeVerticalEnlarge();
    TestResizeBothAxes();
    TestChain();

    TestMakerFunctionValid();
    TestMakerFunctionWrongParamsCount();
    TestMakerFunctionWrongFormat();
    TestMakerFunctionWrongValue();
    TestMakerFunctionWrongDescriptor();

    std::cout << "finished" << std::endl;
}