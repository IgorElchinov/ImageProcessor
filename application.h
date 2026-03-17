#ifndef SRC_CORE_APPLICATION_H
#define SRC_CORE_APPLICATION_H

#include <string>

#include "factory.h"
#include "parse.h"

namespace image_processor {

class Application {

public:  // ===== Constructors =====
    Application(int argc, char* argv[]);

public:  // ===== Common member functions =====
    // Runs the application. Returns `0` if ok, `1` if runtime error, `2` if arguments are invalid
    int Run() const;

public:  // ===== Member constants =====
    // Message with application usage
    static const std::string USAGE_MESSAGE;

protected:  // ===== Private members =====
    Parser parser;
    FilterFactory factory;
    bool initialised_correctly;
};

}  // namespace image_processor

#endif  // SRC_CORE_APPLICATION_H