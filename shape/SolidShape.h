#pragma once
#include "IShape.h"

class ISolidShape : public IShape
{
public:
    ISolidShape(std::string const& type);
    virtual ~ISolidShape() = default;
    virtual Color GetFillColor() const = 0;
};