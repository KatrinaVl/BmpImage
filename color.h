#pragma once

#include <cstdint>

namespace color {

class Color {
public:
    Color() = default;
    Color(uint8_t b, uint8_t g, uint8_t r);

    uint8_t red = 0;
    uint8_t green = 0;
    uint8_t blue = 0;

    void SetColor(uint8_t b, uint8_t g, uint8_t r);
};

}  // namespace color
