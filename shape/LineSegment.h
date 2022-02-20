#pragma once
#include "IShape.h"
#include "Point.h"
#include "Color.h"

class CLineSegment : public IShape
{
public:
    CLineSegment(Point const& startPosition, Point const& endPosition, Color const& outlineColor);
    ~CLineSegment() = default;
    float GetArea() const override;
    float GetPerimeter() const override;
    Color GetOutlineColor() const override;

    Point const& GetStartPoint() const;
    Point const& GetEndPoint() const;

    void Draw(ICanvas & canvas) const override;
protected:
    void AppendProperties(std::ostream & strm) const override;
private:
    Point m_startPoint;
    Point m_endPoint;
    Color m_outlineColor;
};