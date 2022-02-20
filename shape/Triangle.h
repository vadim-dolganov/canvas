#pragma once
#include "Point.h"
#include "SolidShape.h"
#include "Color.h"

class CTriangle : public ISolidShape
{
public:
    CTriangle(Point const& firstVertex, Point const& secondVertex, Point const& thirdVertex, Color const& outlineColor, Color const& fillColor, float rotationAngle);
    ~CTriangle() = default;
    float GetArea() const override;
    float GetPerimeter() const override;
    float GetSideLength(Point const& firstVertex, Point const& secondVertex) const;
    Color GetOutlineColor() const override;

    Color GetFillColor() const override;

    Point const& GetVertex1() const;
    Point const& GetVertex2() const;
    Point const& GetVertex3() const;

    void Draw(ICanvas & canvas) const override;
protected:
    void AppendProperties(std::ostream & strm) const override;
private:
    Vertices m_vertices;
    Color m_outlineColor;
    Color m_fillColor;
};