#ifndef SRC_CORE_UTILS_H
#define SRC_CORE_UTILS_H

#include <type_traits>
#include <string>
#include <vector>

#include "bmp.h"

namespace image_processor {

// Filter descriptor structure
struct FilterDescriptor {
    std::string name;
    std::vector<std::string> params;
};

}  // namespace image_processor

namespace image_processor::utils {

class InvalidDescriptor : public std::runtime_error {
public:  // ===== Constructors =====
    explicit InvalidDescriptor(char* msg) : std::runtime_error(msg) {
    }

    explicit InvalidDescriptor(const std::string& msg) : std::runtime_error(msg) {
    }

    InvalidDescriptor(const InvalidDescriptor& msg) = default;
};

template <typename Enumeration>
inline auto EnumClassToInteger(Enumeration const value) -> typename std::underlying_type<Enumeration>::type {
    return static_cast<typename std::underlying_type<Enumeration>::type>(value);
}

// Checks if `s` represents an integer
bool IsInt(const std::string& s);

// Checks if `s` represents a floating-point number
bool IsFloat(const std::string& s);

}  // namespace image_processor::utils

#endif  // SRC_CORE_UTILS_H