#pragma once
struct Color
{
    float red;
    float green;
    float blue;
};
bool ConvertHexInRGBColor(std::string const& hexColor, Color & rgbColor);
