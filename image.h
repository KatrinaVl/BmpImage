#pragma once

#include "color.h"
#include <cstddef>
#include <cstdint>
#include <vector>

namespace image {

class Image {
public:
    Image() = default;
    explicit Image(int32_t height, int32_t width);
    explicit Image(const std::vector<std::vector<color::Color>>& image);
    Image(const Image& image);
    ~Image() = default;

    int32_t GetHeight() const;
    int32_t GetWidth() const;
    const std::vector<std::vector<color::Color>>& GetImage() const;
    color::Color& GetColor(int32_t height, int32_t width);
    const color::Color& GetColor(int32_t height, int32_t width) const;
    void SetColor(int32_t height, int32_t width, color::Color& clr);
    void ChangeWidth(int32_t width);
    void ChangeHeight(int32_t height);
    void GetVecOfColors(const std::vector<std::vector<color::Color>>& image);

private:
    int32_t im_height_;
    int32_t im_width_;
    std::vector<std::vector<color::Color>> image_;
};

}  // namespace image
