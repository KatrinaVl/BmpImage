#include "constants.h"
#include "filters.h"
#include "image.h"
#include <algorithm>
#include <random>
#include <sstream>

filters::Crop::Crop(std::string_view width, std::string_view height) {
    width_ = static_cast<int32_t>(std::stoul(static_cast<std::string>(width)));
    height_ = static_cast<int32_t>(std::stoul(static_cast<std::string>(height)));
}

image::Image filters::Crop::App(image::Image& image) const {  ////Unit Test
    int32_t new_width = std::min(width_, image.GetWidth());
    int32_t new_height = std::min(height_, image.GetHeight());
    image.ChangeHeight(new_height);
    image.ChangeWidth(new_width);
    return image;
}

image::Image filters::Grayscale::App(image::Image& image) const {  ////Unit Test
    int32_t width = image.GetWidth();
    int32_t height = image.GetHeight();
    for (int32_t i = 0; i < height; ++i) {
        for (int32_t j = 0; j < width; ++j) {
            color::Color& my_color = image.GetColor(i, j);
            double new_color = constants::GS_FOR_RED * static_cast<double>(my_color.red) +
                               constants::GS_FOR_GREEN * static_cast<double>(my_color.green) +
                               constants::GS_FOR_BLUE * static_cast<double>(my_color.blue);
            my_color.red = static_cast<uint8_t>(new_color);
            my_color.green = static_cast<uint8_t>(new_color);
            my_color.blue = static_cast<uint8_t>(new_color);
        }
    }
    return image;
}

image::Image filters::Negative::App(image::Image& image) const {  ////Unit Test
    int32_t width = image.GetWidth();
    int32_t height = image.GetHeight();
    for (int32_t i = 0; i < height; ++i) {
        for (int32_t j = 0; j < width; ++j) {
            color::Color& my_color = image.GetColor(i, j);
            my_color.red = constants::MAX_NUM_PIX - my_color.red;
            my_color.green = constants::MAX_NUM_PIX - my_color.green;
            my_color.blue = constants::MAX_NUM_PIX - my_color.blue;
        }
    }
    return image;
}

color::Color filters::Filter::AppMatrix(int32_t i, int32_t j, image::Image& image,
                                        const std::vector<std::vector<int32_t>>& matrix) const {
    color::Color new_color;
    int32_t width = image.GetWidth();
    int32_t height = image.GetHeight();
    const std::vector<std::vector<color::Color>>& pixels = image.GetImage();
    int32_t new_red = 0;
    int32_t new_blue = 0;
    int32_t new_green = 0;
    for (int32_t z = -1; z < 2; ++z) {
        for (int32_t k = -1; k < 2; ++k) {
            if (i + z < 0 || j + k < 0 || i + z > height - 1 || j + k > width - 1) {
                new_red += matrix[1 + z][1 + k] * pixels[i][j].red;
                new_blue += matrix[1 + z][1 + k] * pixels[i][j].blue;
                new_green += matrix[1 + z][1 + k] * pixels[i][j].green;
            } else {
                new_red += matrix[1 + z][1 + k] * pixels[i + z][j + k].red;
                new_blue += matrix[1 + z][1 + k] * pixels[i + z][j + k].blue;
                new_green += matrix[1 + z][1 + k] * pixels[i + z][j + k].green;
            }
        }
    }
    new_color.red = std::min(constants::MAX_NUM_PIX, std::max(0, new_red));
    new_color.blue = std::min(constants::MAX_NUM_PIX, std::max(0, new_blue));
    new_color.green = std::min(constants::MAX_NUM_PIX, std::max(0, new_green));
    return new_color;
}

image::Image filters::Sharpening::App(image::Image& image) const {  ////Unit Test
    image::Image copy_image(image);
    int32_t width = image.GetWidth();
    int32_t height = image.GetHeight();
    for (int32_t i = 0; i < height; ++i) {
        for (int32_t j = 0; j < width; ++j) {
            color::Color new_color = AppMatrix(i, j, image, matrix_);
            copy_image.SetColor(i, j, new_color);
        }
    }
    return copy_image;
}

image::Image filters::EdgeDetection::App(image::Image& image) const {  ////Unit Test
    image::Image origin_copy_image(image);
    image::Image gr_copy_image(image);
    Grayscale gr_image;
    gr_copy_image = gr_image.App(image);
    int32_t width = image.GetWidth();
    int32_t height = image.GetHeight();
    for (int32_t i = 0; i < height; ++i) {
        for (int32_t j = 0; j < width; ++j) {
            color::Color new_color = AppMatrix(i, j, gr_copy_image, matrix_);
            if ((static_cast<double>(new_color.red) / constants::MAX_NUM_PIX) > treshold_) {
                new_color.red = constants::MAX_NUM_PIX;
                new_color.blue = constants::MAX_NUM_PIX;
                new_color.green = constants::MAX_NUM_PIX;
            } else {
                new_color.red = 0;
                new_color.blue = 0;
                new_color.green = 0;
            }
            origin_copy_image.SetColor(i, j, new_color);
        }
    }
    return origin_copy_image;
}

filters::EdgeDetection::EdgeDetection(std::string_view treshold) {
    treshold_ = std::stod(static_cast<std::string>(treshold));
}

image::Image filters::Shift::App(image::Image& image) const {
    image::Image copy_image(image);
    std::mt19937 rnd{std::random_device{}()};
    std::uniform_int_distribution<std::int32_t> dist_width(
        0, static_cast<int32_t>(constants::PIX_OFFSET_RANGE_WID * image.GetWidth() - 1));
    std::uniform_int_distribution<std::int32_t> dist_height(
        0, static_cast<int32_t>(constants::PIX_OFFSET_RANGE_HEI * image.GetHeight() - 1));

    int32_t width = image.GetWidth();
    int32_t height = image.GetHeight();
    for (int32_t i = 0; i < height; ++i) {
        int32_t index_w = dist_width(rnd);
        int32_t index_h = dist_height(rnd);
        for (int32_t j = 0; j < width; ++j) {
            color::Color new_color = image.GetColor((i + index_h) % height, (j + index_w) % width);
            copy_image.SetColor(i, j, new_color);
        }
    }

    return copy_image;
}
