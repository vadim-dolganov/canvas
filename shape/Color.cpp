#include "stdafx.h"
#include "Color.h"

bool ConvertHexInRGBColor(std::string const& hexColor, Color & rgbColor)
{
    bool isConverted = true;
    if (hexColor[0] != '#')
    {
        std::cout << "ERROR: not found the special symbol '#'\n";
        isConverted = false;
    }
    else
    {
        try
        {
            rgbColor.red = (1.f / 255) * std::stoi(hexColor.substr(1, 2), 0, 16);
            rgbColor.green = (1.f / 255) * std::stoi(hexColor.substr(3, 2), 0, 16);
            rgbColor.blue = (1.f / 255) * std::stoi(hexColor.substr(5, 2), 0, 16);
        }
        catch (std::exception const& e)
        {
            std::cout << e.what() << std::endl;
            isConverted = false;
        }
    }
    return isConverted;
}