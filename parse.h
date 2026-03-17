#ifndef SRC_CORE_PARSE_H
#define SRC_CORE_PARSE_H

#include <string>
#include <vector>

#include "utils.h"

namespace image_processor {

// CLA parser class
class Parser {
public:  // ===== Member types =====
    enum class ParseResult {
        OK,
        INPUT_FILE_NOT_GIVEN,
        OUTPUT_FILE_NOT_GIVEN,
        WRONG_FORMAT,
    };

    using DescriptorCollection = std::vector<FilterDescriptor>;

public:  // ===== Common member functions =====
    ParseResult Parse(int argc, char* argv[]) {
        return ParseInternal(static_cast<size_t>(argc), argv);
    }

public:  // ===== Getters =====
    const std::string& GetInputFile() const {
        return input_filename_;
    }

    const std::string& GetOutputFile() const {
        return output_filename_;
    }

    const std::vector<FilterDescriptor>& GetDescriptors() const {
        return descriptors_;
    }

public:  // ===== Member constants =====
    static const size_t INPUT_FILE_INDEX;
    static const size_t OUTPUT_FILE_INDEX;

protected:  // ===== Private member functions =====
    ParseResult ParseInternal(size_t argc, char* argv[]);

protected:  // ===== Private members =====
    std::string input_filename_;
    std::string output_filename_;
    DescriptorCollection descriptors_;
};

}  // namespace image_processor

#endif  // SRC_CORE_PARSE_H