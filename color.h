#pragma once
#include <cstdint>
struct RGBColor {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

extern RGBColor BLACK;
extern RGBColor WHITE;
extern RGBColor SEA;
extern RGBColor cNULL;
extern RGBColor BEIGE;

bool operator==(const RGBColor& lhs, const RGBColor& rhs);
bool operator!=(const RGBColor& lhs, const RGBColor& rhs);
RGBColor shiftColor(RGBColor color, RGBColor shifter, int weight);