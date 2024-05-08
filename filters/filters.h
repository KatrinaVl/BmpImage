#pragma once

#include "constants.h"
#include "image.h"
#include <string_view>

namespace filters {

class Filter {
public:
    Filter() = default;
    virtual ~Filter() = default;
    virtual image::Image App(image::Image& img) const = 0;

protected:
    color::Color AppMatrix(int32_t i, int32_t j, image::Image& image,
                           const std::vector<std::vector<int32_t>>& matrix) const;
};

class Crop : public Filter {
public:
    Crop(std::string_view width, std::string_view height);
    image::Image App(image::Image& image) const override;

private:
    int32_t width_;
    int32_t height_;
};

class Grayscale : public Filter {
public:
    Grayscale() = default;
    image::Image App(image::Image& image) const override;
};

class Negative : public Filter {
public:
    Negative() = default;
    image::Image App(image::Image& image) const override;
};

class Sharpening : public Filter {
public:
    Sharpening() = default;
    image::Image App(image::Image& image) const override;

private:
    const std::vector<std::vector<int32_t>> matrix_{{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};
};

class EdgeDetection : public Filter {
public:
    explicit EdgeDetection(std::string_view treshold);
    image::Image App(image::Image& image) const override;

private:
    const std::vector<std::vector<int32_t>> matrix_{{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}};
    double treshold_ = 0;
};

class Shift : public Filter {
public:
    Shift() = default;
    image::Image App(image::Image& image) const override;
};

}  // namespace filters
