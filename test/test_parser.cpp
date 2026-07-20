#include <cassert>
#include <iostream>

#include "parse.h"

void TestConvolutionFilterDefaultConstructor() {
    std::cout << __func__ << std::endl;

    image_processor::Parser parser;

    std::cout << "passed" << std::endl;
}

void TestEmptyCLA() {
    std::cout << __func__ << std::endl;

    const int argc = 1;
    char name[] = "parser";
    char *argv[argc] = {name};

    image_processor::Parser parser;
    image_processor::Parser::ParseResult res = parser.Parse(argc, argv);

    assert(res == image_processor::Parser::ParseResult::INPUT_FILE_NOT_GIVEN);

    std::cout << "passed" << std::endl;
}

void TestInputFileOnly() {
    std::cout << __func__ << std::endl;

    const int argc = 2;
    char name[] = "parser";
    char input[] = "input.bmp";
    char *argv[argc] = {name, input};

    image_processor::Parser parser;
    image_processor::Parser::ParseResult res = parser.Parse(argc, argv);

    assert(res == image_processor::Parser::ParseResult::OUTPUT_FILE_NOT_GIVEN);

    std::cout << "passed" << std::endl;
}

void TestOnlyFiles() {
    std::cout << __func__ << std::endl;

    const int argc = 3;
    char name[] = "parser";
    char input[] = "input.bmp";
    char output[] = "output.bmp";
    char *argv[argc] = {name, input, output};

    image_processor::Parser parser;
    image_processor::Parser::ParseResult res = parser.Parse(argc, argv);

    assert(res == image_processor::Parser::ParseResult::OK);
    assert(parser.GetInputFile() == input);
    assert(parser.GetOutputFile() == output);
    assert(parser.GetDescriptors().empty());

    std::cout << "passed" << std::endl;
}

void TestOneFilterNoParams() {
    std::cout << __func__ << std::endl;

    const int argc = 4;
    char name[] = "parser";
    char input[] = "input.bmp";
    char output[] = "output.bmp";
    char filter1[] = "-gs";
    char filter1_name[] = "gs";
    char *argv[argc] = {name, input, output, filter1};

    image_processor::Parser parser;
    image_processor::Parser::ParseResult res = parser.Parse(argc, argv);

    assert(res == image_processor::Parser::ParseResult::OK);
    assert(parser.GetInputFile() == input);
    assert(parser.GetOutputFile() == output);
    assert(parser.GetDescriptors().size() == 1);
    // std::cout << parser.GetDescriptors()[0].name << std::endl;
    assert(parser.GetDescriptors()[0].name == filter1_name);
    assert(parser.GetDescriptors()[0].params == std::vector<std::string>{});

    std::cout << "passed" << std::endl;
}

void TestOneFilterOneParam() {
    std::cout << __func__ << std::endl;

    const int argc = 5;
    char name[] = "parser";
    char input[] = "input.bmp";
    char output[] = "output.bmp";
    char filter1[] = "-blur";
    char filter1_name[] = "blur";
    char param11[] = "0.5";
    char *argv[argc] = {name, input, output, filter1, param11};

    image_processor::Parser parser;
    image_processor::Parser::ParseResult res = parser.Parse(argc, argv);

    assert(res == image_processor::Parser::ParseResult::OK);
    assert(parser.GetInputFile() == input);
    assert(parser.GetOutputFile() == output);
    assert(parser.GetDescriptors().size() == 1);
    // std::cout << parser.GetDescriptors()[0].name << std::endl;
    assert(parser.GetDescriptors()[0].name == filter1_name);
    assert(parser.GetDescriptors()[0].params == std::vector<std::string>{param11});

    std::cout << "passed" << std::endl;
}

void TestOneFilterTwoParams() {
    std::cout << __func__ << std::endl;

    const int argc = 6;
    char name[] = "parser";
    char input[] = "input.bmp";
    char output[] = "output.bmp";
    char filter1[] = "-crop";
    char filter1_name[] = "crop";
    char param11[] = "10";
    char param12[] = "15";
    char *argv[argc] = {name, input, output, filter1, param11, param12};

    image_processor::Parser parser;
    image_processor::Parser::ParseResult res = parser.Parse(argc, argv);

    assert(res == image_processor::Parser::ParseResult::OK);
    assert(parser.GetInputFile() == input);
    assert(parser.GetOutputFile() == output);
    assert(parser.GetDescriptors().size() == 1);
    // std::cout << parser.GetDescriptors()[0].name << std::endl;
    assert(parser.GetDescriptors()[0].name == filter1_name);
    assert((parser.GetDescriptors()[0].params == std::vector<std::string>{param11, param12}));

    std::cout << "passed" << std::endl;
}

void TestManyFilters1() {
    std::cout << __func__ << std::endl;

    const int argc = 9;
    char name[] = "parser";
    char input[] = "input.bmp";
    char output[] = "output.bmp";

    char filter1[] = "-blur";
    char filter1_name[] = "blur";
    char param11[] = "0.5";

    char filter2[] = "-gs";
    char filter2_name[] = "gs";

    char filter3[] = "-crop";
    char filter3_name[] = "crop";
    char param31[] = "10";
    char param32[] = "15";

    char *argv[argc] = {name, input, output, filter1, param11, filter2, filter3, param31, param32};

    image_processor::Parser parser;
    image_processor::Parser::ParseResult res = parser.Parse(argc, argv);

    assert(res == image_processor::Parser::ParseResult::OK);
    assert(parser.GetInputFile() == input);
    assert(parser.GetOutputFile() == output);
    assert(parser.GetDescriptors().size() == 3);

    assert(parser.GetDescriptors()[0].name == filter1_name);
    assert(parser.GetDescriptors()[0].params == std::vector<std::string>{param11});

    assert(parser.GetDescriptors()[1].name == filter2_name);
    assert(parser.GetDescriptors()[1].params == std::vector<std::string>{});

    assert(parser.GetDescriptors()[2].name == filter3_name);
    assert((parser.GetDescriptors()[2].params == std::vector<std::string>{param31, param32}));

    std::cout << "passed" << std::endl;
}

void TestManyFilters2() {
    std::cout << __func__ << std::endl;

    const int argc = 9;
    char name[] = "parser";
    char input[] = "input.bmp";
    char output[] = "output.bmp";

    char filter1[] = "-crop";
    char filter1_name[] = "crop";
    char param11[] = "10";
    char param12[] = "15";

    char filter2[] = "-blur";
    char filter2_name[] = "blur";
    char param21[] = "0.5";

    char filter3[] = "-gs";
    char filter3_name[] = "gs";

    char *argv[argc] = {name, input, output, filter1, param11, param12, filter2, param21, filter3};

    image_processor::Parser parser;
    image_processor::Parser::ParseResult res = parser.Parse(argc, argv);

    assert(res == image_processor::Parser::ParseResult::OK);
    assert(parser.GetInputFile() == input);
    assert(parser.GetOutputFile() == output);
    assert(parser.GetDescriptors().size() == 3);

    assert(parser.GetDescriptors()[0].name == filter1_name);
    assert((parser.GetDescriptors()[0].params == std::vector<std::string>{param11, param12}));

    assert(parser.GetDescriptors()[1].name == filter2_name);
    assert((parser.GetDescriptors()[1].params == std::vector<std::string>{param21}));

    assert(parser.GetDescriptors()[2].name == filter3_name);
    assert((parser.GetDescriptors()[2].params == std::vector<std::string>{}));

    std::cout << "passed" << std::endl;
}

void TestNoFilterTwoParams() {
    std::cout << __func__ << std::endl;

    const int argc = 6;
    char name[] = "parser";
    char input[] = "input.bmp";
    char output[] = "output.bmp";
    char param11[] = "10";
    char param12[] = "15";
    char *argv[argc] = {name, input, output, param11, param12};

    image_processor::Parser parser;
    image_processor::Parser::ParseResult res = parser.Parse(argc, argv);

    assert(res == image_processor::Parser::ParseResult::WRONG_FORMAT);

    std::cout << "passed" << std::endl;
}

void TestEmptyStrings1() {
    std::cout << __func__ << std::endl;

    const int argc = 6;
    char cla1[] = "parser";
    char cla2[] = "input.bmp";
    char cla3[] = "output.bmp";
    char cla4[] = "10";
    char cla5[] = "15";
    char *argv[argc] = {cla1, cla2, cla3, cla4, cla5};

    image_processor::Parser parser;
    image_processor::Parser::ParseResult res = parser.Parse(argc, argv);

    assert(res == image_processor::Parser::ParseResult::WRONG_FORMAT);

    std::cout << "passed" << std::endl;
}

void TestEmptyStrings2() {
    std::cout << __func__ << std::endl;

    const int argc = 4;
    char name[] = "parser";
    char input[] = "";
    char output[] = "";
    char filter1[] = "-gs";
    char filter1_name[] = "gs";
    char *argv[argc] = {name, input, output, filter1};

    image_processor::Parser parser;
    image_processor::Parser::ParseResult res = parser.Parse(argc, argv);

    assert(res == image_processor::Parser::ParseResult::OK);
    assert(parser.GetInputFile() == input);
    assert(parser.GetOutputFile() == output);
    assert(parser.GetDescriptors().size() == 1);
    // std::cout << parser.GetDescriptors()[0].name << std::endl;
    assert(parser.GetDescriptors()[0].name == filter1_name);
    assert(parser.GetDescriptors()[0].params == std::vector<std::string>{});

    std::cout << "passed" << std::endl;
}

void TestEmptyStrings3() {
    std::cout << __func__ << std::endl;

    const int argc = 5;
    char name[] = "parser";
    char input[] = "input.bmp";
    char output[] = "output.bmp";
    char filter1[] = "-blur";
    char filter1_name[] = "blur";
    char param11[] = "";
    char *argv[argc] = {name, input, output, filter1, param11};

    image_processor::Parser parser;
    image_processor::Parser::ParseResult res = parser.Parse(argc, argv);

    assert(res == image_processor::Parser::ParseResult::OK);
    assert(parser.GetInputFile() == input);
    assert(parser.GetOutputFile() == output);
    assert(parser.GetDescriptors().size() == 1);
    // std::cout << parser.GetDescriptors()[0].name << std::endl;
    assert(parser.GetDescriptors()[0].name == filter1_name);
    assert(parser.GetDescriptors()[0].params == std::vector<std::string>{param11});

    std::cout << "passed" << std::endl;
}

void TestEmptyStrings4() {
    std::cout << __func__ << std::endl;

    const int argc = 5;
    char name[] = "parser";
    char input[] = "input.bmp";
    char output[] = "output.bmp";
    char filter1[] = "-";
    char filter1_name[] = "";
    char param11[] = "param";
    char *argv[argc] = {name, input, output, filter1, param11};

    image_processor::Parser parser;
    image_processor::Parser::ParseResult res = parser.Parse(argc, argv);

    assert(res == image_processor::Parser::ParseResult::OK);
    assert(parser.GetInputFile() == input);
    assert(parser.GetOutputFile() == output);
    assert(parser.GetDescriptors().size() == 1);
    // std::cout << parser.GetDescriptors()[0].name << std::endl;
    assert(parser.GetDescriptors()[0].name == filter1_name);
    assert(parser.GetDescriptors()[0].params == std::vector<std::string>{param11});

    std::cout << "passed" << std::endl;
}

void TestRealCLA(int argc, char *argv[]) {
    std::cout << __func__ << std::endl;

    image_processor::Parser parser;
    image_processor::Parser::ParseResult res = parser.Parse(argc, argv);

    switch (res) {
        case image_processor::Parser::ParseResult::OK:
            std::cout << "Success!" << std::endl;
            std::cout << "Input file: " << parser.GetInputFile() << std::endl;
            std::cout << "Output file: " << parser.GetOutputFile() << std::endl;
            for (const image_processor::FilterDescriptor &descr : parser.GetDescriptors()) {
                std::cout << "Filter: " << descr.name << std::endl;
                std::cout << "Params: ";
                for (const std::string &param : descr.params) {
                    std::cout << param << " ";
                }
                std::cout << std::endl;
            }
            break;

        case image_processor::Parser::ParseResult::INPUT_FILE_NOT_GIVEN:
            std::cout << "No input file" << std::endl;
            break;

        case image_processor::Parser::ParseResult::OUTPUT_FILE_NOT_GIVEN:
            std::cout << "No output file" << std::endl;
            break;

        case image_processor::Parser::ParseResult::WRONG_FORMAT:
            std::cout << "Wrong format" << std::endl;
            break;

        default:
            std::cout << "A?" << std::endl;
            break;
    }

    std::cout << "passed" << std::endl;
}

int main(int argc, char *argv[]) {
    std::cout << "test_parser" << std::endl;

    TestConvolutionFilterDefaultConstructor();
    TestEmptyCLA();
    TestInputFileOnly();
    TestOnlyFiles();
    TestOneFilterNoParams();
    TestOneFilterOneParam();
    TestOneFilterTwoParams();
    TestManyFilters1();
    TestManyFilters2();
    TestNoFilterTwoParams();
    TestEmptyStrings1();
    TestEmptyStrings2();
    TestEmptyStrings3();
    TestEmptyStrings4();

    std::cout << std::endl << std::endl << std::endl;

    TestRealCLA(argc, argv);

    std::cout << "finished" << std::endl;
}