#include "parse.h"

const size_t image_processor::Parser::INPUT_FILE_INDEX = 1;
const size_t image_processor::Parser::OUTPUT_FILE_INDEX = 2;

image_processor::Parser::ParseResult image_processor::Parser::ParseInternal(size_t argc, char *argv[]) {
    if (argc <= INPUT_FILE_INDEX) {
        return image_processor::Parser::ParseResult::INPUT_FILE_NOT_GIVEN;
    } else {
        input_filename_ = argv[INPUT_FILE_INDEX];
    }
    if (argc <= OUTPUT_FILE_INDEX) {
        return image_processor::Parser::ParseResult::OUTPUT_FILE_NOT_GIVEN;
    } else {
        output_filename_ = argv[OUTPUT_FILE_INDEX];
    }
    for (size_t i = OUTPUT_FILE_INDEX + 1; i < argc; ++i) {
        if (argv[i][0] == '-') {
            descriptors_.emplace_back();
            descriptors_.back().name = argv[i] + 1;
        } else {
            if (descriptors_.empty()) {
                return image_processor::Parser::ParseResult::WRONG_FORMAT;
            } else {
                descriptors_.back().params.push_back(argv[i]);
            }
        }
    }
    return image_processor::Parser::ParseResult::OK;
}