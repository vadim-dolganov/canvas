#pragma once
#include "SolidShape.h"
#include "Point.h"
#include "Color.h"

class CCircle : public ISolidShape
{
public:
    CCircle(Point const& center, float radius, Color const& outlineColor, Color const& fillColor);
    ~CCircle() = default;
    float GetArea() const override;
    float GetPerimeter() const override;
    Color GetOutlineColor() const override;
    Color GetFillColor() const override;
    float GetRadius() const;
    Point const& GetCenter() const;

    void Draw(ICanvas & canvas) const override;
protected:
    void AppendProperties(std::ostream & strm) const override;
private:
    Point m_center;
    float m_radius;
    Color m_outlineColor;
    Color m_fillColor;
};