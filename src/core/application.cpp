#include "application.h"

#include <iostream>
#include <exception>
#include <stdexcept>

#include "bmp.h"
#include "factory.h"
#include "parse.h"
#include "pipeline.h"
#include "utils.h"

const std::string image_processor::Application::USAGE_MESSAGE =
    "Usage:\n"
    "image_processor {input file} {output file} "
    "[-{filter 1} [filter argument 1] [filter argument 2] ...] "
    "[-{filter 2} [filter argument 1] [filter argument 2] ...] ...\n\n"
    "Currently available filters:\n\n"
    "\t-crop [width] [height] -- crops image to height x wight (must be two non-negative integers)\n"
    "\t-neg -- creates a negative of the image\n"
    "\t-gs -- creates black & white version of the image\n"
    "\t-sharp -- sharpens the image\n"
    "\t-edge [threshold] -- applies edge detection with given threshold (must be a float between 0 and 1)\n"
    "\t-blur [sigma] -- applies gaussian blur (sigma be a non-negative number)\n";

static const std::string UNEXPECTED_ERROR_MESSAGE =
    "Something went wrong!\n"
    "Please check that input file exists and is valid BMP.\n\n"
    "Please also check application usage.\n" +
    image_processor::Application::USAGE_MESSAGE;

static const std::string INPUT_FILE_NOT_GIVEN_MESSAGE =
    "You should specify input filename!\n"
    "Please check application usage.\n\n" +
    image_processor::Application::USAGE_MESSAGE;

static const std::string OUTPUT_FILE_NOT_GIVEN_MESSAGE =
    "You should specify output filename!\n"
    "Please check application usage.\n\n" +
    image_processor::Application::USAGE_MESSAGE;

static const std::string WRONG_FORMAT_MESSAGE =
    "Wrong arguments.\n"
    "Please check application usage.\n\n" +
    image_processor::Application::USAGE_MESSAGE;

image_processor::Application::Application(int argc, char* argv[]) : parser(), factory(), initialised_correctly(false) {
    image_processor::Parser::ParseResult res = parser.Parse(argc, argv);
    switch (res) {
        case image_processor::Parser::ParseResult::OK:
            initialised_correctly = true;
            break;

        case image_processor::Parser::ParseResult::INPUT_FILE_NOT_GIVEN:
            std::cout << INPUT_FILE_NOT_GIVEN_MESSAGE << std::endl;
            break;

        case image_processor::Parser::ParseResult::OUTPUT_FILE_NOT_GIVEN:
            std::cout << OUTPUT_FILE_NOT_GIVEN_MESSAGE << std::endl;
            break;

        case image_processor::Parser::ParseResult::WRONG_FORMAT:
            std::cout << WRONG_FORMAT_MESSAGE << std::endl;
            break;

        default:
            std::cout << UNEXPECTED_ERROR_MESSAGE << std::endl;
            break;
    }
}

int image_processor::Application::Run() const {
    if (!initialised_correctly) {
        return 2;
    }
    try {
        BMPImage img = ReadBMP(parser.GetInputFile());
        Pipeline pl = factory.CreatePipeline(parser.GetDescriptors());
        pl.Apply(img);
        WriteBMP(parser.GetOutputFile(), img);
        return 0;
    } catch (const image_processor::utils::InvalidDescriptor& e) {
        std::cout << "Wrong argument format: " << e.what() << std::endl;
        std::cout << USAGE_MESSAGE << std::endl;
        return 2;
    } catch (const std::runtime_error& e) {
        std::cout << "Error occurred while processing image: " << e.what() << std::endl;
        std::cout << "Please check that input and output files exist and are valid BMP files." << std::endl;
        std::cout << "Usage" << std::endl;
        std::cout << USAGE_MESSAGE << std::endl;
        return 1;
    }
}