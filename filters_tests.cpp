#include <catch.hpp>

#include "color.h"
#include "constants.h"
#include "filter_control.h"
#include "image.h"
#include "parser_com_str.h"
#include "read_file.h"
#include <iostream>

namespace tests_image {

const std::string INPUT_PATH =
    "/home/katrin/lovecpp/pmi-229-1-Ekaterina-Vladimirova-KatrinVl/tasks/image_processor/test_script/data/flag.bmp\0";

bool ImageComparison(image::Image& test, image::Image& check) {
    int32_t width = test.GetWidth();
    int32_t height = test.GetHeight();

    for (int32_t i = 0; i < height; ++i) {
        for (int32_t j = 0; j < width; ++j) {
            color::Color test_color = test.GetColor(i, j);
            color::Color check_color = check.GetColor(i, j);
            if (test_color.red != check_color.red || test_color.blue != check_color.blue ||
                test_color.green != check_color.green) {
                return false;
            }
        }
    }

    return true;
}

TEST_CASE("CheckCropFilter") {
    const std::string binary_name = "./image_processor\0";
    const std::string input_name = INPUT_PATH;
    const std::string output_name = "output_path\0";
    const std::string_view name_filter = "-crop\0";

    const std::string_view par_of_width = "5\0";
    const std::string_view par_of_height = "7\0";

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

    reading_file::ReadFile test(parser.GetInputPath());
    image::Image test_image = test.GetImg();

    filter_control::FilterControl change_image(parser);
    test_image = change_image.FixedImage(test_image);

    const int32_t new_width = 5;
    const int32_t new_height = 7;

    const std::string_view check_path =
        "/home/katrin/lovecpp/pmi-229-1-Ekaterina-Vladimirova-KatrinVl/tasks/image_processor/test_script/data/"
        "flag_crop.bmp";
    reading_file::ReadFile check(check_path);
    image::Image check_image = check.GetImg();
    try {
        if (test_image.GetWidth() != new_width || test_image.GetHeight() != new_height ||
            ImageComparison(test_image, check_image) == false) {
            throw std::invalid_argument("Crop isn't working properly");
        }
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    delete[] argv;
}

TEST_CASE("CheckCropWithBigSize") {
    const std::string binary_name = "./image_processor\0";
    const std::string input_name = INPUT_PATH;
    const std::string output_name = "output_path\0";
    const std::string_view name_filter = "-crop\0";

    const std::string_view par_of_width = "50\0";
    const std::string_view par_of_height = "70\0";

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

    reading_file::ReadFile test(parser.GetInputPath());
    image::Image test_image = test.GetImg();

    int32_t old_width = test_image.GetWidth();
    int32_t old_height = test_image.GetHeight();

    filter_control::FilterControl change_image(parser);
    test_image = change_image.FixedImage(test_image);

    const std::string_view check_path =
        "/home/katrin/lovecpp/pmi-229-1-Ekaterina-Vladimirova-KatrinVl/tasks/image_processor/test_script/data/"
        "flag_crop.bmp";
    reading_file::ReadFile check(check_path);
    image::Image check_image = check.GetImg();
    try {
        if (test_image.GetWidth() != old_width || test_image.GetHeight() != old_height ||
            ImageComparison(test_image, check_image) == false) {
            throw std::invalid_argument("Crop filter does not work correctly with sizes larger than the original ones");
        }
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    delete[] argv;
}

TEST_CASE("CropWithDoubleParameters") {
    const std::string binary_name = "./image_processor\0";
    const std::string input_name = INPUT_PATH;
    const std::string output_name = "output_path\0";
    const std::string_view name_filter = "-crop\0";

    const std::string_view par_of_width = "5.8\0";
    const std::string_view par_of_height = "7\0";

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

    reading_file::ReadFile test(parser.GetInputPath());
    image::Image test_image = test.GetImg();

    try {
        filter_control::FilterControl change_image(parser);
        test_image = change_image.FixedImage(test_image);
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    delete[] argv;
}

TEST_CASE("CheckGrayscaleFilter") {
    const std::string binary_name = "./image_processor\0";
    const std::string input_name = INPUT_PATH;
    const std::string output_name = "output_path\0";
    const std::string_view name_filter = "-gs\0";

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

    parse_arguments::ParserComStr parser;
    parser.Parse(argc, argv);

    reading_file::ReadFile test(parser.GetInputPath());
    image::Image test_image = test.GetImg();

    filter_control::FilterControl change_image(parser);
    test_image = change_image.FixedImage(test_image);

    const std::string_view check_path =
        "/home/katrin/lovecpp/pmi-229-1-Ekaterina-Vladimirova-KatrinVl/tasks/image_processor/test_script/data/"
        "flag_gs.bmp";
    reading_file::ReadFile check(check_path);
    image::Image check_image = check.GetImg();
    try {
        if (ImageComparison(test_image, check_image) == false) {
            throw std::invalid_argument("Grayscale isn't working properly");
        }
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    delete[] argv;
}

TEST_CASE("CheckNegativeFilter") {
    const std::string binary_name = "./image_processor\0";
    const std::string input_name = INPUT_PATH;
    const std::string output_name = "output_path\0";
    const std::string_view name_filter = "-neg\0";

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

    parse_arguments::ParserComStr parser;
    parser.Parse(argc, argv);

    reading_file::ReadFile test(parser.GetInputPath());
    image::Image test_image = test.GetImg();

    filter_control::FilterControl change_image(parser);
    test_image = change_image.FixedImage(test_image);

    const std::string_view check_path =
        "/home/katrin/lovecpp/pmi-229-1-Ekaterina-Vladimirova-KatrinVl/tasks/image_processor/test_script/data/"
        "flag_neg.bmp";
    reading_file::ReadFile check(check_path);
    image::Image check_image = check.GetImg();
    try {
        if (ImageComparison(test_image, check_image) == false) {
            throw std::invalid_argument("Negative isn't working properly");
        }
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    delete[] argv;
}

TEST_CASE("CheckSharpeningFilter") {
    const std::string binary_name = "./image_processor\0";
    const std::string input_name = INPUT_PATH;
    const std::string output_name = "output_path\0";
    const std::string_view name_filter = "-sharp\0";

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

    parse_arguments::ParserComStr parser;
    parser.Parse(argc, argv);

    reading_file::ReadFile test(parser.GetInputPath());
    image::Image test_image = test.GetImg();

    filter_control::FilterControl change_image(parser);
    test_image = change_image.FixedImage(test_image);

    const std::string_view check_path =
        "/home/katrin/lovecpp/pmi-229-1-Ekaterina-Vladimirova-KatrinVl/tasks/image_processor/test_script/data/"
        "flag_sharp.bmp";
    reading_file::ReadFile check(check_path);
    image::Image check_image = check.GetImg();
    try {
        if (ImageComparison(test_image, check_image) == false) {
            throw std::invalid_argument("Sharpening isn't working properly");
        }
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    delete[] argv;
}

TEST_CASE("CheckEdgeFilter") {
    const std::string binary_name = "./image_processor\0";
    const std::string input_name = INPUT_PATH;
    const std::string output_name = "output_path\0";
    const std::string name_filter = "-edge\0";
    const std::string sigma = "0.1\0";

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
    argv[4] = new char[sigma.length() + 1];
    std::strncpy(argv[4], sigma.data(), sigma.length() + 1);

    parse_arguments::ParserComStr parser;
    parser.Parse(argc, argv);

    reading_file::ReadFile test(parser.GetInputPath());
    image::Image test_image = test.GetImg();

    filter_control::FilterControl change_image(parser);
    test_image = change_image.FixedImage(test_image);

    const std::string_view check_path =
        "/home/katrin/lovecpp/pmi-229-1-Ekaterina-Vladimirova-KatrinVl/tasks/image_processor/test_script/data/"
        "flag_edge.bmp";
    reading_file::ReadFile check(check_path);
    image::Image check_image = check.GetImg();
    try {
        if (ImageComparison(test_image, check_image) == false) {
            throw std::invalid_argument("Edge Detection isn't working properly");
        }
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    delete[] argv;
}

TEST_CASE("EdgeWithIntParameters") {
    const std::string binary_name = "./image_processor\0";
    const std::string input_name = INPUT_PATH;
    const std::string output_name = "output_path\0";
    const std::string name_filter = "-edge\0";
    const std::string sigma = "7\0";

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
    argv[4] = new char[sigma.length() + 1];
    std::strncpy(argv[4], sigma.data(), sigma.length() + 1);

    parse_arguments::ParserComStr parser;
    parser.Parse(argc, argv);

    reading_file::ReadFile test(parser.GetInputPath());
    image::Image test_image = test.GetImg();

    try {
        filter_control::FilterControl change_image(parser);
        test_image = change_image.FixedImage(test_image);
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    delete[] argv;
}

}  // namespace tests_image
