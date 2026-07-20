#include <cassert>
#include <iostream>

#include "bmp.h"
#include "factory.h"
#include "negative.h"
#include "test_utils.h"

void TestDefaultConstructor() {
    std::cout << __func__ << std::endl;

    image_processor::Negative flt;

    std::cout << "passed" << std::endl;
}

void TestMoveConstructor() {
    std::cout << __func__ << std::endl;

    image_processor::Negative flt1;
    image_processor::Negative flt2(std::move(flt1));

    std::cout << "passed" << std::endl;
}

void TestCopyConstructor() {
    std::cout << __func__ << std::endl;

    image_processor::Negative flt1;
    image_processor::Negative flt2(flt1);

    std::cout << "passed" << std::endl;
}

void TestCopyAssignmentOperator() {
    std::cout << __func__ << std::endl;

    image_processor::Negative flt1;
    image_processor::Negative flt2;

    flt2 = flt1;

    std::cout << "passed" << std::endl;
}

void TestMoveAssignmentOperator() {
    std::cout << __func__ << std::endl;

    image_processor::Negative flt1;
    image_processor::Negative flt2;

    flt2 = std::move(flt1);

    std::cout << "passed" << std::endl;
}

void TestApply() {
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

    image_processor::Negative flt;
    std::vector<std::vector<image_processor::Pixel>> new_data{
        {{254, 255, 254}, {253, 255, 254}, {252, 255, 254}, {251, 255, 254}, {250, 255, 254}},
        {{254, 255, 253}, {253, 255, 253}, {252, 255, 253}, {251, 255, 253}, {250, 255, 253}},
        {{254, 255, 252}, {253, 255, 252}, {252, 255, 252}, {251, 255, 252}, {250, 255, 252}},
        {{254, 255, 251}, {253, 255, 251}, {252, 255, 251}, {251, 255, 251}, {250, 255, 251}},
        {{254, 255, 250}, {253, 255, 250}, {252, 255, 250}, {251, 255, 250}, {250, 255, 250}},
        {{254, 255, 249}, {253, 255, 249}, {252, 255, 249}, {251, 255, 249}, {250, 255, 249}},
    };
    flt.Apply(img);

    assert(img.GetWidth() == w);
    assert(img.GetHeight() == h);
    assert(img.GetBitmap() == new_data);

    std::cout << "passed" << std::endl;
}

void TestChain() {
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

    image_processor::Negative flt1;
    image_processor::Negative flt2;

    flt2.Apply(flt1.Apply(img));

    assert(img.GetWidth() == w);
    assert(img.GetHeight() == h);
    assert(img.GetBitmap() == data);

    std::cout << "passed" << std::endl;
}

void TestMakeFunction() {
    std::cout << __func__ << std::endl;

    image_processor::FilterDescriptor d = {.name = "neg", .params = {}};
    image_processor::BaseFilter* flt = image_processor::FilterFactory::MAKE_FILTER.at("neg")(d);

    size_t h = 6;
    size_t w = 5;
    image_processor::BMPImage img = test_utils::CreateImage(h, w,
                                                            {
                                                                {{1, 0, 1}, {2, 0, 1}, {3, 0, 1}, {4, 0, 1}, {5, 0, 1}},
                                                                {{1, 0, 2}, {2, 0, 2}, {3, 0, 2}, {4, 0, 2}, {5, 0, 2}},
                                                                {{1, 0, 3}, {2, 0, 3}, {3, 0, 3}, {4, 0, 3}, {5, 0, 3}},
                                                                {{1, 0, 4}, {2, 0, 4}, {3, 0, 4}, {4, 0, 4}, {5, 0, 4}},
                                                                {{1, 0, 5}, {2, 0, 5}, {3, 0, 5}, {4, 0, 5}, {5, 0, 5}},
                                                                {{1, 0, 6}, {2, 0, 6}, {3, 0, 6}, {4, 0, 6}, {5, 0, 6}},
                                                            });

    flt->Apply(img);

    assert(img == test_utils::CreateImage(
                      h, w,
                      {
                          {{254, 255, 254}, {253, 255, 254}, {252, 255, 254}, {251, 255, 254}, {250, 255, 254}},
                          {{254, 255, 253}, {253, 255, 253}, {252, 255, 253}, {251, 255, 253}, {250, 255, 253}},
                          {{254, 255, 252}, {253, 255, 252}, {252, 255, 252}, {251, 255, 252}, {250, 255, 252}},
                          {{254, 255, 251}, {253, 255, 251}, {252, 255, 251}, {251, 255, 251}, {250, 255, 251}},
                          {{254, 255, 250}, {253, 255, 250}, {252, 255, 250}, {251, 255, 250}, {250, 255, 250}},
                          {{254, 255, 249}, {253, 255, 249}, {252, 255, 249}, {251, 255, 249}, {250, 255, 249}},
                      }));

    delete flt;

    std::cout << "passed" << std::endl;
}

void TestMakeFunctionWrongDescriptor() {
    std::cout << __func__ << std::endl;

    bool expected = false;
    try {
        image_processor::FilterDescriptor d = {.name = "missing-filter", .params = {}};
        image_processor::BaseFilter* flt = image_processor::FilterFactory::MAKE_FILTER.at("neg")(d);
        image_processor::BMPImage empty;
        flt->Apply(empty);
    } catch (const std::invalid_argument& e) {
        std::string correct_msg = "Filter name mismatch: neg expected.";
        assert(e.what() == correct_msg);
        expected = true;
    }

    assert(expected);

    std::cout << "passed" << std::endl;
}

void TestMakeFunctionWrongParamsCount() {
    std::cout << __func__ << std::endl;

    bool expected = false;
    try {
        image_processor::FilterDescriptor d = {.name = "neg", .params = {"42", "3.14"}};
        image_processor::BaseFilter* flt = image_processor::FilterFactory::MAKE_FILTER.at("neg")(d);
        image_processor::BMPImage empty;
        flt->Apply(empty);
    } catch (const image_processor::utils::InvalidDescriptor& e) {
        std::string correct_msg = "Wrong number of parameters for neg: 0 expected.";
        assert(e.what() == correct_msg);
        expected = true;
    }

    assert(expected);

    std::cout << "passed" << std::endl;
}

int main(int argc, char* argv[]) {
    std::cout << "test_negative" << std::endl;

    TestDefaultConstructor();
    TestCopyConstructor();
    TestMoveConstructor();
    TestCopyAssignmentOperator();
    TestMoveAssignmentOperator();

    TestApply();
    TestChain();

    TestMakeFunction();
    TestMakeFunctionWrongDescriptor();
    TestMakeFunctionWrongParamsCount();

    std::cout << "finished" << std::endl;
}