#include <exception>
#include <iostream>

#include "application.h"

int main(int argc, char** argv) {
    try {
        image_processor::Application app(argc, argv);
        return app.Run();
    } catch (const std::runtime_error& e) {
        std::cout << "Unexpected error occurred while processing image!" << std::endl;
        std::cerr << "Error: " << e.what() << std::endl;
        std::cout << "Please check that input and output files exist and are valid BMP." << std::endl;
        std::cout << "Please also check application usage." << std::endl << std::endl;
        std::cout << image_processor::Application::USAGE_MESSAGE << std::endl;
        return 1;
    } catch (...) {
        std::cout << "Unexpected error occurred while processing image!" << std::endl;
        std::cout << "Please check that input and output files exist and are valid BMP." << std::endl;
        std::cout << "Please also check application usage." << std::endl << std::endl;
        std::cout << image_processor::Application::USAGE_MESSAGE << std::endl;
        return 3;
    }
    return 4;
}
