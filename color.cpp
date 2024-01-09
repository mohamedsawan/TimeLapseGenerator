#include "color.h"
#include <math.h>

RGBColor BLACK = { 0, 0, 0 };
RGBColor WHITE = { 255, 255, 255 };
RGBColor SEA = { 41, 140, 233 };
RGBColor cNULL = { 160, 154, 154 };
RGBColor BEIGE = { 223, 194, 159 };

bool operator==(const RGBColor& lhs, const RGBColor& rhs)
{
    return (lhs.red == rhs.red) && (lhs.green == rhs.green) && (lhs.blue == rhs.blue);
}

bool operator!=(const RGBColor& lhs, const RGBColor& rhs)
{
    return (lhs.red != rhs.red) || (lhs.green != rhs.green) || (lhs.blue != rhs.blue);
}

RGBColor shiftColor(RGBColor color, RGBColor shifter, int weight) //dilution weight (higher weight, less whitening)
{
    if (weight < 0)
    {
        color.red = (abs(weight) * color.red + shifter.red) / (abs(weight) + 1);
        color.green = (abs(weight) * color.green + shifter.green) / (abs(weight) + 1);
        color.blue = (abs(weight) * color.blue + shifter.blue) / (abs(weight) + 1);
    }
    else
    {
        color.red = (color.red + weight * shifter.red) / (weight + 1);
        color.green = (color.green + weight * shifter.green) / (weight + 1);
        color.blue = (color.blue + weight * shifter.blue) / (weight + 1);
    }

    return color;
}