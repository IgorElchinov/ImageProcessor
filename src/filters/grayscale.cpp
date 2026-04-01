#include "grayscale.h"

const double image_processor::Grayscale::RED_CHANNEL_FACTOR = 0.299;
const double image_processor::Grayscale::GREEN_CHANNEL_FACTOR = 0.587;
const double image_processor::Grayscale::BLUE_CHANNEL_FACTOR = 0.114;

image_processor::BMPImage& image_processor::Grayscale::Apply(image_processor::BMPImage& img) const {
    for (size_t i = 0; i < img.GetHeight(); ++i) {
        for (size_t j = 0; j < img.GetWidth(); ++j) {
            uint8_t new_val =
                static_cast<uint8_t>(BLUE_CHANNEL_FACTOR * img.At(i, j).blue +
                                     GREEN_CHANNEL_FACTOR * img.At(i, j).green + RED_CHANNEL_FACTOR * img.At(i, j).red);
            img.At(i, j).blue = img.At(i, j).green = img.At(i, j).red = new_val;
        }
    }
    return img;
}
