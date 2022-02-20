#include "stdafx.h"
#include "Circle.h"
#include "SolidShape.h"
#include "Point.h"
#include "const.h"

CCircle::CCircle(Point const& center, float radius, Color const& outlineColor, Color const& fillColor)
    :ISolidShape("Circle"),
    m_center(center),
    m_radius(radius),
    m_outlineColor(outlineColor),
    m_fillColor(fillColor)
{
}

Point const& CCircle::GetCenter() const
{
    return m_center;
}

float CCircle::GetRadius() const
{
    return m_radius;
}

Color CCircle::GetOutlineColor() const
{
    return m_outlineColor;
};

Color CCircle::GetFillColor() const
{
    return m_fillColor;
};

float CCircle::GetArea() const
{
    return PI * std::pow(m_radius, 2);
};

float CCircle::GetPerimeter() const
{
    return 2 * PI * m_radius;
};

void CCircle::AppendProperties(std::ostream & strm) const
{
    strm << "  Radius = " << m_radius;
}

void CCircle::Draw(ICanvas & canvas) const
{
    canvas.FillCircle(m_center, m_radius, m_fillColor);
    canvas.DrawCircle(m_center, m_radius, m_outlineColor);
}