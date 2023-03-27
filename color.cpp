#include "color.h"

color::Color::Color(uint8_t b, uint8_t g, uint8_t r) {
    red = r;
    blue = b;
    green = g;
}

void color::Color::SetColor(uint8_t b, uint8_t g, uint8_t r) {
    red = r;
    blue = b;
    green = g;
}
