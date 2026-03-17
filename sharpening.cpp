#include "sharpening.h"

const image_processor::Sharpening::Matrix image_processor::Sharpening::MATRIX = {
    {0, -1, 0},
    {-1, 5, -1},
    {0, -1, 0},
};
