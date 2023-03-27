#include "constants.h"
#include "parser_com_str.h"
#include <catch.hpp>
#include <iostream>

namespace parser_tests {

TEST_CASE("BasicParseWorks") {
    const std::string binary_name = "./image_processor\0";
    const std::string input_name = "input_path\0";
    const std::string output_name = "output_path\0";

    int argc = 3;
    char** argv = new char*[argc];
    argv[0] = new char[binary_name.length() + 1];
    std::strncpy(argv[0], binary_name.data(), binary_name.length() + 1);
    argv[1] = new char[input_name.length() + 1];
    std::strncpy(argv[1], input_name.data(), input_name.length() + 1);
    argv[2] = new char[output_name.length() + 1];
    std::strncpy(argv[2], output_name.data(), output_name.length() + 1);

    parse_arguments::ParserComStr parser;
    parser.Parse(argc, argv);

    REQUIRE(input_name == parser.GetInputPath());
    REQUIRE(output_name == parser.GetOutputPath());

    delete[] argv;
}

TEST_CASE("LessThanTreeParameters") {
    const std::string binary_name = "./image_processor\0";
    const std::string input_name = "input_path\0";

    int argc = 2;
    char** argv = new char*[argc];
    argv[0] = new char[binary_name.length() + 1];
    std::strncpy(argv[0], binary_name.data(), binary_name.length() + 1);
    argv[1] = new char[input_name.length() + 1];
    std::strncpy(argv[1], input_name.data(), input_name.length() + 1);

    try {
        parse_arguments::ParserComStr parser;
        parser.Parse(argc, argv);
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    delete[] argv;
}

TEST_CASE("MoreThanThreeParameters") {
    const std::string binary_name = "./image_processor\0";
    const std::string input_name = "input_path\0";
    const std::string output_name = "output_path\0";
    const std::string_view name_filter = "-crop\0";
    const std::string_view par_of_width = "5\0";
    const std::string_view par_of_height = "5\0";

    int argc = constants::P_T_NUM_ARGC;
    char** argv = new char*[argc];
    argv[0] = new char[binary_name.length() + 1];
    std::strncpy(argv[0], binary_name.data(), binary_name.length() + 1);
    argv[1] = new char[input_name.length() + 1];
    std::strncpy(argv[1], input_name.data(), input_name.length() + 1);
    argv[2] = new char[output_name.length() + 1];
    std::strncpy(argv[2], output_name.data(), output_name.length() + 1);
    argv[3] = new char[name_filter.length() + 1];
    std::strncpy(argv[3], name_filter.data(), name_filter.length() + 1);
    argv[4] = new char[par_of_width.length() + 1];
    std::strncpy(argv[4], par_of_width.data(), par_of_width.length() + 1);
    argv[constants::P_T_NUM_PAR] = new char[par_of_height.length() + 1];
    std::strncpy(argv[constants::P_T_NUM_PAR], par_of_height.data(), par_of_height.length() + 1);

    parse_arguments::ParserComStr parser;
    parser.Parse(argc, argv);

    std::vector<parse_arguments::FilterParameters> check_vec{{"-crop", {"5", "5"}}};

    REQUIRE(input_name == parser.GetInputPath());
    REQUIRE(output_name == parser.GetOutputPath());
    std::vector<parse_arguments::FilterParameters> parse_vec = parser.GetFilters();
    try {
        for (size_t i = 0; i < check_vec.size(); ++i) {
            if (check_vec[i].name != parse_vec[i].name || check_vec[i].parameters[0] != parse_vec[i].parameters[0] ||
                check_vec[i].parameters[1] != parse_vec[i].parameters[1]) {
                throw std::invalid_argument("Parser packs elements incorrectly");
            }
        }
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    delete[] argv;
}

TEST_CASE("IncorrectNameOfFilter") {
    const std::string binary_name = "./image_processor\0";
    const std::string input_name = "input_path\0";
    const std::string output_name = "output_path\0";
    const std::string_view name_filter = "-hgcut\0";
    const std::string_view par_of_width = "5\0";
    const std::string_view par_of_height = "5\0";

    int argc = constants::P_T_NUM_ARGC;
    char** argv = new char*[argc];
    argv[0] = new char[binary_name.length() + 1];
    std::strncpy(argv[0], binary_name.data(), binary_name.length() + 1);
    argv[1] = new char[input_name.length() + 1];
    std::strncpy(argv[1], input_name.data(), input_name.length() + 1);
    argv[2] = new char[output_name.length() + 1];
    std::strncpy(argv[2], output_name.data(), output_name.length() + 1);
    argv[3] = new char[name_filter.length() + 1];
    std::strncpy(argv[3], name_filter.data(), name_filter.length() + 1);
    argv[4] = new char[par_of_width.length() + 1];
    std::strncpy(argv[4], par_of_width.data(), par_of_width.length() + 1);
    argv[constants::P_T_NUM_PAR] = new char[par_of_height.length() + 1];
    std::strncpy(argv[constants::P_T_NUM_PAR], par_of_height.data(), par_of_height.length() + 1);

    try {
        parse_arguments::ParserComStr parser;
        parser.Parse(argc, argv);
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    delete[] argv;
}

TEST_CASE("CropWrongNumberOfParameters") {
    const std::string binary_name = "./image_processor\0";
    const std::string input_name = "input_path\0";
    const std::string output_name = "output_path\0";
    const std::string_view name_filter = "-crop\0";
    const std::string_view par_of_width = "5\0";

    int argc = constants::P_T_NUM_ARGC_FIVE;
    char** argv = new char*[argc];
    argv[0] = new char[binary_name.length() + 1];
    std::strncpy(argv[0], binary_name.data(), binary_name.length() + 1);
    argv[1] = new char[input_name.length() + 1];
    std::strncpy(argv[1], input_name.data(), input_name.length() + 1);
    argv[2] = new char[output_name.length() + 1];
    std::strncpy(argv[2], output_name.data(), output_name.length() + 1);
    argv[3] = new char[name_filter.length() + 1];
    std::strncpy(argv[3], name_filter.data(), name_filter.length() + 1);
    argv[4] = new char[par_of_width.length() + 1];
    std::strncpy(argv[4], par_of_width.data(), par_of_width.length() + 1);

    try {
        parse_arguments::ParserComStr parser;
        parser.Parse(argc, argv);
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    delete[] argv;
}

TEST_CASE("GrayscaleWrongNumberOfParameters") {
    const std::string binary_name = "./image_processor\0";
    const std::string input_name = "input_path\0";
    const std::string output_name = "output_path\0";
    const std::string_view name_filter = "-gs\0";
    const std::string_view par_of_width = "5\0";

    int argc = constants::P_T_NUM_ARGC_FIVE;
    char** argv = new char*[argc];
    argv[0] = new char[binary_name.length() + 1];
    std::strncpy(argv[0], binary_name.data(), binary_name.length() + 1);
    argv[1] = new char[input_name.length() + 1];
    std::strncpy(argv[1], input_name.data(), input_name.length() + 1);
    argv[2] = new char[output_name.length() + 1];
    std::strncpy(argv[2], output_name.data(), output_name.length() + 1);
    argv[3] = new char[name_filter.length() + 1];
    std::strncpy(argv[3], name_filter.data(), name_filter.length() + 1);
    argv[4] = new char[par_of_width.length() + 1];
    std::strncpy(argv[4], par_of_width.data(), par_of_width.length() + 1);

    try {
        parse_arguments::ParserComStr parser;
        parser.Parse(argc, argv);
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    delete[] argv;
}

TEST_CASE("NegativeWrongNumberOfParameters") {
    const std::string binary_name = "./image_processor\0";
    const std::string input_name = "input_path\0";
    const std::string output_name = "output_path\0";
    const std::string_view name_filter = "-neg\0";
    const std::string_view par_of_width = "5\0";

    int argc = constants::P_T_NUM_ARGC_FIVE;
    char** argv = new char*[argc];
    argv[0] = new char[binary_name.length() + 1];
    std::strncpy(argv[0], binary_name.data(), binary_name.length() + 1);
    argv[1] = new char[input_name.length() + 1];
    std::strncpy(argv[1], input_name.data(), input_name.length() + 1);
    argv[2] = new char[output_name.length() + 1];
    std::strncpy(argv[2], output_name.data(), output_name.length() + 1);
    argv[3] = new char[name_filter.length() + 1];
    std::strncpy(argv[3], name_filter.data(), name_filter.length() + 1);
    argv[4] = new char[par_of_width.length() + 1];
    std::strncpy(argv[4], par_of_width.data(), par_of_width.length() + 1);

    try {
        parse_arguments::ParserComStr parser;
        parser.Parse(argc, argv);
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    delete[] argv;
}

TEST_CASE("SharpWrongNumberOfParameters") {
    const std::string binary_name = "./image_processor\0";
    const std::string input_name = "input_path\0";
    const std::string output_name = "output_path\0";
    const std::string_view name_filter = "-sharp\0";
    const std::string_view par_of_width = "5\0";

    int argc = constants::P_T_NUM_ARGC_FIVE;
    char** argv = new char*[argc];
    argv[0] = new char[binary_name.length() + 1];
    std::strncpy(argv[0], binary_name.data(), binary_name.length() + 1);
    argv[1] = new char[input_name.length() + 1];
    std::strncpy(argv[1], input_name.data(), input_name.length() + 1);
    argv[2] = new char[output_name.length() + 1];
    std::strncpy(argv[2], output_name.data(), output_name.length() + 1);
    argv[3] = new char[name_filter.length() + 1];
    std::strncpy(argv[3], name_filter.data(), name_filter.length() + 1);
    argv[4] = new char[par_of_width.length() + 1];
    std::strncpy(argv[4], par_of_width.data(), par_of_width.length() + 1);

    try {
        parse_arguments::ParserComStr parser;
        parser.Parse(argc, argv);
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    delete[] argv;
}

TEST_CASE("EdgeWrongNumberOfParameters") {
    const std::string binary_name = "./image_processor\0";
    const std::string input_name = "input_path\0";
    const std::string output_name = "output_path\0";
    const std::string_view name_filter = "-edge\0";

    int argc = 4;
    char** argv = new char*[argc];
    argv[0] = new char[binary_name.length() + 1];
    std::strncpy(argv[0], binary_name.data(), binary_name.length() + 1);
    argv[1] = new char[input_name.length() + 1];
    std::strncpy(argv[1], input_name.data(), input_name.length() + 1);
    argv[2] = new char[output_name.length() + 1];
    std::strncpy(argv[2], output_name.data(), output_name.length() + 1);
    argv[3] = new char[name_filter.length() + 1];
    std::strncpy(argv[3], name_filter.data(), name_filter.length() + 1);

    try {
        parse_arguments::ParserComStr parser;
        parser.Parse(argc, argv);
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    delete[] argv;
}

TEST_CASE("ShiftWrongNumberOfParameters") {
    const std::string binary_name = "./image_processor\0";
    const std::string input_name = "input_path\0";
    const std::string output_name = "output_path\0";
    const std::string_view name_filter = "-shift\0";
    const std::string_view par_of_width = "5\0";

    int argc = constants::P_T_NUM_ARGC_FIVE;
    char** argv = new char*[argc];
    argv[0] = new char[binary_name.length() + 1];
    std::strncpy(argv[0], binary_name.data(), binary_name.length() + 1);
    argv[1] = new char[input_name.length() + 1];
    std::strncpy(argv[1], input_name.data(), input_name.length() + 1);
    argv[2] = new char[output_name.length() + 1];
    std::strncpy(argv[2], output_name.data(), output_name.length() + 1);
    argv[3] = new char[name_filter.length() + 1];
    std::strncpy(argv[3], name_filter.data(), name_filter.length() + 1);
    argv[4] = new char[par_of_width.length() + 1];
    std::strncpy(argv[4], par_of_width.data(), par_of_width.length() + 1);

    try {
        parse_arguments::ParserComStr parser;
        parser.Parse(argc, argv);
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    delete[] argv;
}

}  // namespace parser_tests
