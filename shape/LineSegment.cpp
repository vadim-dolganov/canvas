#include "stdafx.h"
#include "LineSegment.h"
#include "Point.h"

CLineSegment::CLineSegment(Point const& startPoint, Point const& endPoint, Color const& outlineColor)
    :IShape("Line"),
    m_startPoint(startPoint),
    m_endPoint(endPoint),
    m_outlineColor(outlineColor)
{
}

float CLineSegment::GetArea() const
{
    return 0;
};

Color CLineSegment::GetOutlineColor() const
{
    return m_outlineColor;
};

Point const& CLineSegment::GetStartPoint() const
{
    return m_startPoint;
}

Point const& CLineSegment::GetEndPoint() const
{
    return m_endPoint;
}

float CLineSegment::GetPerimeter() const
{
    float dx = m_startPoint.x - m_endPoint.x;
    float dy = m_startPoint.y - m_endPoint.y;
    return std::hypot(dx, dy);
};

void CLineSegment::AppendProperties(std::ostream & strm) const
{
}

void CLineSegment::Draw(ICanvas & canvas) const
{
    canvas.DrawLine(m_startPoint, m_endPoint, m_outlineColor);
}