#pragma once
#include "ICanvasDrawable.h"

class IShape : public ICanvasDrawable
{
public:
    IShape(std::string const& type);
    virtual ~IShape() = default;
    virtual float GetArea() const = 0;
    virtual float GetPerimeter() const = 0;
    virtual Color GetOutlineColor() const = 0;

    std::string ToString() const;
protected:
    virtual void AppendProperties(std::ostream & strm) const = 0;
private:
    std::string m_type;
};