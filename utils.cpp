#include "utils.h"

#include <string>
#include <charconv>
#include <cmath>

bool image_processor::utils::IsInt(const std::string& s) {
    if (s.empty()) {
        return false;
    }
    try {
        size_t parsed = 0;
        std::stoi(s, &parsed);
        if (parsed != s.size()) {
            return false;
        }
    } catch (...) {
        return false;
    }
    return true;
}

bool image_processor::utils::IsFloat(const std::string& s) {
    if (s.empty()) {
        return false;
    }
    try {
        size_t parsed = 0;
        double value = std::stod(s, &parsed);
        if (parsed != s.size()) {
            return false;
        }
        if (!std::isfinite(value)) {
            return false;
        }
    } catch (...) {
        return false;
    }
    return true;
}
