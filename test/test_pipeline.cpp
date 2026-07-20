#include <cassert>
#include <iostream>
#include <optional>
#include <random>

#include "pipeline.h"
#include "filters.h"
#include "test_utils.h"

void TestConvolutionFilterDefaultConstructor() {
    std::cout << __func__ << std::endl;

    image_processor::Pipeline p;

    std::cout << "passed" << std::endl;
}

std::optional<image_processor::Pipeline> CreatePipeline() {
    std::mt19937 rnd;
    if (rnd() % 2) {
        return std::nullopt;
    }
    image_processor::Pipeline p;
    p.Add(new image_processor::Negative());
    return p;
}

void TestReturn() {
    std::cout << __func__ << std::endl;

    std::optional<image_processor::Pipeline> p = CreatePipeline();
    size_t h = 3;
    size_t w = 4;
    image_processor::BMPImage img = test_utils::CreateImage(h, w,
                                                            {
                                                                {
                                                                    {1, 0, 1},
                                                                    {1, 0, 2},
                                                                    {1, 0, 3},
                                                                    {1, 0, 4},
                                                                },
                                                                {
                                                                    {2, 0, 1},
                                                                    {2, 0, 2},
                                                                    {2, 0, 3},
                                                                    {2, 0, 4},
                                                                },
                                                                {
                                                                    {3, 0, 1},
                                                                    {3, 0, 2},
                                                                    {3, 0, 3},
                                                                    {3, 0, 4},
                                                                },
                                                            });

    if (!p.has_value()) {
        std::cout << "Empty" << std::endl;
        return;
    }
    p->Apply(img);

    assert(img == test_utils::CreateImage(h, w,
                                          {
                                              {
                                                  {254, 255, 254},
                                                  {254, 255, 253},
                                                  {254, 255, 252},
                                                  {254, 255, 251},
                                              },
                                              {
                                                  {253, 255, 254},
                                                  {253, 255, 253},
                                                  {253, 255, 252},
                                                  {253, 255, 251},
                                              },
                                              {
                                                  {252, 255, 254},
                                                  {252, 255, 253},
                                                  {252, 255, 252},
                                                  {252, 255, 251},
                                              },
                                          }));

    std::cout << "passed" << std::endl;
}

void TestAdd() {
    std::cout << __func__ << std::endl;

    size_t h = 3;
    size_t w = 4;
    image_processor::BMPImage img = test_utils::CreateImage(h, w,
                                                            {
                                                                {
                                                                    {1, 0, 1},
                                                                    {1, 0, 2},
                                                                    {1, 0, 3},
                                                                    {1, 0, 4},
                                                                },
                                                                {
                                                                    {2, 0, 1},
                                                                    {2, 0, 2},
                                                                    {2, 0, 3},
                                                                    {2, 0, 4},
                                                                },
                                                                {
                                                                    {3, 0, 1},
                                                                    {3, 0, 2},
                                                                    {3, 0, 3},
                                                                    {3, 0, 4},
                                                                },
                                                            });

    image_processor::Pipeline p;
    p.Add(new image_processor::Negative());
    size_t nh = 2;
    size_t nw = 1;
    p.Add(new image_processor::Crop(nh, nw));

    p.Apply(img);

    assert(img == test_utils::CreateImage(nh, nw, {{{254, 255, 254}}, {{253, 255, 254}}}));

    std::cout << "passed" << std::endl;
}

int main(int argc, char* argv[]) {
    std::cout << "test_pipeline" << std::endl;

    TestConvolutionFilterDefaultConstructor();
    for (size_t i = 0; i < 10; ++i) {
        TestReturn();
    }
    TestAdd();

    std::cout << "finished" << std::endl;
    return 0;
}