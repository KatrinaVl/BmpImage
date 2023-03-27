#include "image.h"

image::Image::Image(int32_t height, int32_t width) {
    im_height_ = height;
    im_width_ = width;
}

image::Image::Image(const std::vector<std::vector<color::Color>>& image) {
    image_ = image;
    im_height_ = static_cast<int32_t>(image.size());
    im_width_ = static_cast<int32_t>(image[0].size());
}

image::Image::Image(const Image& image) {
    image_ = image.image_;
    im_height_ = image.im_height_;
    im_width_ = image.im_width_;
}

int32_t image::Image::GetHeight() const {
    return im_height_;
}

int32_t image::Image::GetWidth() const {
    return im_width_;
}

const std::vector<std::vector<color::Color>>& image::Image::GetImage() const {
    return image_;
}

color::Color& image::Image::GetColor(int32_t height, int32_t width) {
    return this->image_[height][width];
}

const color::Color& image::Image::GetColor(int32_t height, int32_t width) const {
    return image_[height][width];
}

void image::Image::SetColor(int32_t height, int32_t width, color::Color& clr) {
    image_[height][width] = clr;
}

void image::Image::ChangeWidth(int32_t width) {
    im_width_ = width;
}

void image::Image::ChangeHeight(int32_t height) {
    im_height_ = height;
}

void image::Image::GetVecOfColors(const std::vector<std::vector<color::Color>>& image) {
    this->image_ = image;
}
