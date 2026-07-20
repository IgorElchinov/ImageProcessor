#include <cassert>
#include <iostream>
#include <vector>

#include "base_filter.h"
#include "filters.h"
#include "utils.h"
#include "test_utils.h"

using test_utils::CreateImage;

void TestCreateBaseFilter() {
    std::cout << __func__ << std::endl;

    // image_processor::BaseFilter flt; // Should not compile

    std::cout << "passed" << std::endl;
}

void TestCreateBaseFilterReferenceFromOther() {
    std::cout << __func__ << std::endl;

    size_t h = 5;
    size_t w = 6;
    image_processor::Crop crop(h, w);
    image_processor::BaseFilter& flt = crop;

    image_processor::BMPImage empty;
    flt.Apply(empty);

    std::cout << "passed" << std::endl;
}

void TestCreateBaseFilterPointerFromOther() {
    std::cout << __func__ << std::endl;

    size_t h = 5;
    size_t w = 6;
    image_processor::BaseFilter* flt = new image_processor::Crop(h, w);

    image_processor::BMPImage empty;
    flt->Apply(empty);

    delete flt;

    std::cout << "passed" << std::endl;
}

void TestApplyCropTroughBaseFilter() {
    std::cout << __func__ << std::endl;

    size_t h = 6;
    size_t w = 5;
    image_processor::BMPImage img = CreateImage(h, w,
                                                {
                                                    {{1, 0, 1}, {2, 0, 1}, {3, 0, 1}, {4, 0, 1}, {5, 0, 1}},
                                                    {{1, 0, 2}, {2, 0, 2}, {3, 0, 2}, {4, 0, 2}, {5, 0, 2}},
                                                    {{1, 0, 3}, {2, 0, 3}, {3, 0, 3}, {4, 0, 3}, {5, 0, 3}},
                                                    {{1, 0, 4}, {2, 0, 4}, {3, 0, 4}, {4, 0, 4}, {5, 0, 4}},
                                                    {{1, 0, 5}, {2, 0, 5}, {3, 0, 5}, {4, 0, 5}, {5, 0, 5}},
                                                    {{1, 0, 6}, {2, 0, 6}, {3, 0, 6}, {4, 0, 6}, {5, 0, 6}},
                                                });

    size_t nh = 4;
    size_t nw = 3;
    image_processor::BaseFilter* flt = new image_processor::Crop(nh, nw);

    flt->Apply(img);

    assert(img == CreateImage(nh, nw,
                              {
                                  {{1, 0, 1}, {2, 0, 1}, {3, 0, 1}},
                                  {{1, 0, 2}, {2, 0, 2}, {3, 0, 2}},
                                  {{1, 0, 3}, {2, 0, 3}, {3, 0, 3}},
                                  {{1, 0, 4}, {2, 0, 4}, {3, 0, 4}},
                              }));

    delete flt;

    std::cout << "passed" << std::endl;
}

void TestApplyNegativeTroughBaseFilter() {
    std::cout << __func__ << std::endl;

    size_t h = 4;
    size_t w = 3;
    image_processor::BMPImage img = CreateImage(h, w,
                                                {
                                                    {{1, 0, 1}, {2, 0, 1}, {3, 0, 1}},
                                                    {{1, 0, 2}, {2, 0, 2}, {3, 0, 2}},
                                                    {{1, 0, 3}, {2, 0, 3}, {3, 0, 3}},
                                                    {{1, 0, 4}, {2, 0, 4}, {3, 0, 4}},
                                                });

    image_processor::BaseFilter* flt = new image_processor::Negative();

    flt->Apply(img);
    assert(img == CreateImage(h, w,
                              {
                                  {{254, 255, 254}, {253, 255, 254}, {252, 255, 254}},
                                  {{254, 255, 253}, {253, 255, 253}, {252, 255, 253}},
                                  {{254, 255, 252}, {253, 255, 252}, {252, 255, 252}},
                                  {{254, 255, 251}, {253, 255, 251}, {252, 255, 251}},
                              }));

    delete flt;

    std::cout << "passed" << std::endl;
}

void TestApplyDifferentFilters() {
    std::cout << __func__ << std::endl;

    size_t h = 4;
    size_t w = 3;
    std::vector<std::vector<image_processor::Pixel>> data{
        {{1, 0, 1}, {2, 0, 1}, {3, 0, 1}},
        {{1, 0, 2}, {2, 0, 2}, {3, 0, 2}},
        {{1, 0, 3}, {2, 0, 3}, {3, 0, 3}},
        {{1, 0, 4}, {2, 0, 4}, {3, 0, 4}},
    };

    size_t nh = 3;
    size_t nw = 2;
    std::vector<image_processor::BaseFilter*> flts{
        new image_processor::Crop(nh, nw),
        new image_processor::Negative(),
        new image_processor::Grayscale(),
        new image_processor::Sharpening(),
    };

    std::vector<image_processor::BMPImage> imgs(flts.size(), CreateImage(h, w, data));

    for (size_t i = 0; i < flts.size(); ++i) {
        flts[i]->Apply(imgs[i]);
    }

    assert(imgs[0] == CreateImage(nh, nw,
                                  {
                                      {{1, 0, 1}, {2, 0, 1}},
                                      {{1, 0, 2}, {2, 0, 2}},
                                      {{1, 0, 3}, {2, 0, 3}},
                                  }));

    assert(imgs[1] == CreateImage(h, w,
                                  {
                                      {{254, 255, 254}, {253, 255, 254}, {252, 255, 254}},
                                      {{254, 255, 253}, {253, 255, 253}, {252, 255, 253}},
                                      {{254, 255, 252}, {253, 255, 252}, {252, 255, 252}},
                                      {{254, 255, 251}, {253, 255, 251}, {252, 255, 251}},
                                  }));

    assert(imgs[2] == CreateImage(h, w,
                                  {
                                      {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
                                      {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
                                      {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}},
                                      {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}},
                                  }));

    assert(imgs[3] == CreateImage(h, w,
                                  {
                                      {{0, 0, 0}, {2, 0, 0}, {4, 0, 0}},
                                      {{0, 0, 2}, {2, 0, 2}, {4, 0, 2}},
                                      {{0, 0, 3}, {2, 0, 3}, {4, 0, 3}},
                                      {{0, 0, 5}, {2, 0, 5}, {4, 0, 5}},
                                  }));

    for (image_processor::BaseFilter* flt : flts) {
        delete flt;
    }

    std::cout << "passed" << std::endl;
}

void TestConvolutionFilterDefaultConstructor() {
    std::cout << __func__ << std::endl;

    // image_processor::ConvolutionFilter flt; // should not compile

    std::cout << "passed" << std::endl;
}

void TestConvolutionFilterMatrixConstructor() {
    std::cout << __func__ << std::endl;

    image_processor::ConvolutionFilter::Matrix fmatrix{
        {-1, -1, -1},
        {-1, -1, -1},
        {-1, -1, -1},
    };

    image_processor::ConvolutionFilter flt(fmatrix);

    std::cout << "passed" << std::endl;
}

void TestMoveConstructor() {
    std::cout << __func__ << std::endl;

    image_processor::ConvolutionFilter::Matrix fmatrix{
        {-1, -1, -1},
        {-1, -1, -1},
        {-1, -1, -1},
    };

    image_processor::ConvolutionFilter flt1(fmatrix);
    image_processor::ConvolutionFilter flt2(std::move(flt1));

    std::cout << "passed" << std::endl;
}

void TestCopyConstructor() {
    std::cout << __func__ << std::endl;

    image_processor::ConvolutionFilter::Matrix fmatrix{
        {-1, -1, -1},
        {-1, -1, -1},
        {-1, -1, -1},
    };

    image_processor::ConvolutionFilter flt1(fmatrix);
    image_processor::ConvolutionFilter flt2(flt1);

    std::cout << "passed" << std::endl;
}

void TestCopyAssignmentOperator() {
    std::cout << __func__ << std::endl;

    image_processor::ConvolutionFilter::Matrix fmatrix1{
        {-1, -1, -1},
        {-1, -1, -1},
        {-1, -1, -1},
    };

    image_processor::ConvolutionFilter::Matrix fmatrix2{
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1},
    };

    image_processor::ConvolutionFilter flt1(fmatrix1);
    image_processor::ConvolutionFilter flt2(fmatrix2);

    flt2 = flt1;
    assert(flt1.GetMatrix() == flt2.GetMatrix());

    std::cout << "passed" << std::endl;
}

void TestMoveAssignmentOperator() {
    std::cout << __func__ << std::endl;

    image_processor::ConvolutionFilter::Matrix fmatrix1{
        {-1, -1, -1},
        {-1, -1, -1},
        {-1, -1, -1},
    };

    image_processor::ConvolutionFilter::Matrix fmatrix2{
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1},
    };

    image_processor::ConvolutionFilter flt1(fmatrix1);
    image_processor::ConvolutionFilter flt2(fmatrix2);

    flt2 = std::move(flt1);
    assert(flt2.GetMatrix() == fmatrix1);

    std::cout << "passed" << std::endl;
}

void TestConvolutionFilterApply1() {
    std::cout << __func__ << std::endl;

    size_t h = 3;
    size_t w = 3;
    image_processor::BMPImage img = CreateImage(h, w,
                                                {
                                                    {{9, 9, 9}, {6, 6, 6}, {3, 3, 3}},
                                                    {{8, 8, 8}, {5, 5, 5}, {2, 2, 2}},
                                                    {{7, 7, 7}, {4, 4, 4}, {1, 1, 1}},
                                                });

    image_processor::ConvolutionFilter::Matrix fmatrix{
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9},
    };

    image_processor::BaseFilter* flt = new image_processor::ConvolutionFilter(fmatrix);

    flt->Apply(img);

    // std::cout << img << std::endl;
    assert(img == CreateImage(h, w,
                              {
                                  {{255, 255, 255}, {228, 228, 228}, {147, 147, 147}},
                                  {{255, 255, 255}, {189, 189, 189}, {108, 108, 108}},
                                  {{255, 255, 255}, {168, 168, 168}, {87, 87, 87}},
                              }));

    delete flt;

    std::cout << "passed" << std::endl;
}

void TestConvolutionFilterApply2() {
    std::cout << __func__ << std::endl;

    size_t h = 3;
    size_t w = 3;
    image_processor::BMPImage img = CreateImage(h, w,
                                                {
                                                    {{9, 9, 9}, {6, 6, 6}, {3, 3, 3}},
                                                    {{8, 8, 8}, {5, 5, 5}, {2, 2, 2}},
                                                    {{7, 7, 7}, {4, 4, 4}, {1, 1, 1}},
                                                });

    image_processor::ConvolutionFilter::Matrix fmatrix{
        {-1, -1, -1},
        {-1, -1, -1},
        {-1, -1, -1},
    };

    image_processor::BaseFilter* flt = new image_processor::ConvolutionFilter(fmatrix);

    flt->Apply(img);

    // std::cout << img << std::endl;
    assert(img == CreateImage(h, w,
                              {
                                  {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
                                  {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
                                  {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
                              }));

    delete flt;

    std::cout << "passed" << std::endl;
}

int main(int argc, char* argv[]) {
    std::cout << "test_base_filter" << std::endl;

    TestCreateBaseFilter();
    TestCreateBaseFilterReferenceFromOther();
    TestCreateBaseFilterPointerFromOther();
    TestApplyCropTroughBaseFilter();
    TestApplyNegativeTroughBaseFilter();
    TestApplyDifferentFilters();

    TestConvolutionFilterDefaultConstructor();
    TestConvolutionFilterMatrixConstructor();
    TestMoveConstructor();
    TestCopyConstructor();
    TestCopyAssignmentOperator();
    TestMoveAssignmentOperator();

    TestConvolutionFilterApply1();
    TestConvolutionFilterApply2();

    std::cout << "finished" << std::endl;
}