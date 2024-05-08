#include "color.h"
#include "image.h"
#include "read_file.h"
#include <catch.hpp>
#include <iostream>

namespace read_tests {

TEST_CASE("NotBMP") {
    const std::string_view check_path =
        "/home/katrin/lovecpp/pmi-229-1-Ekaterina-Vladimirova-KatrinVl/tasks/image_processor/test_script/data/"
        "hse_logo.jpg";
    try {
        reading_file::ReadFile check(check_path);
        image::Image my_image = check.GetImg();
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

TEST_CASE("WrongInputPath") {
    const std::string_view check_path =
        "/home/katrin/lovecpp/pmi-229-1-Ekaterina-Vladimirova-KatrinVl/tasks/image_processor/test_script/data/"
        "ftrdes.bmp";
    try {
        reading_file::ReadFile check(check_path);
        image::Image my_image = check.GetImg();
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}
}  // namespace read_tests
