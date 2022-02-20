#include "stdafx.h"
#include "Triangle.h"
#include "SolidShape.h"
#include "Point.h"

CTriangle::CTriangle(Point const& firstVertex, Point const& secondVertex, Point const& thirdVertex, Color const& outlineColor, Color const& fillColor, float rotationAngle)
    :ISolidShape("Triangle"),
    m_fillColor(fillColor),
    m_outlineColor(outlineColor)
{
	Point center = { (firstVertex.x + secondVertex.x + thirdVertex.x) / 3, (firstVertex.y + secondVertex.y + thirdVertex.y) / 3 };
	float c = std::cos(rotationAngle * M_PI / 180);
	float s = std::sin(rotationAngle * M_PI / 180);
	m_vertices.push_back({ center.x + (firstVertex.x - center.x) * c - (firstVertex.y - center.y) * s, center.y + (firstVertex.x - center.x) * s + (firstVertex.y - center.y) * c });
    m_vertices.push_back({ center.x + (secondVertex.x - center.x) * c - (secondVertex.y - center.y) * s, center.y + (secondVertex.x - center.x) * s + (secondVertex.y - center.y) * c });
    m_vertices.push_back({ center.x + (thirdVertex.x - center.x) * c - (thirdVertex.y - center.y) * s, center.y + (thirdVertex.x - center.x) * s + (thirdVertex.y - center.y) * c });
}

Color CTriangle::GetOutlineColor() const
{
    return m_outlineColor;
};

Color CTriangle::GetFillColor() const
{
    return m_fillColor;
};

Point const& CTriangle::GetVertex1() const
{
    return m_vertices[0];
}

Point const& CTriangle::GetVertex2() const
{
    return m_vertices[1];
}

Point const& CTriangle::GetVertex3() const
{
    return m_vertices[2];
}

float CTriangle::GetArea() const
{
    float semiperimeter = GetPerimeter() * 0.5f;
    return std::sqrt(semiperimeter*(semiperimeter - GetSideLength(m_vertices[0], m_vertices[1]))*
        (semiperimeter - GetSideLength(m_vertices[1], m_vertices[2]))*
        (semiperimeter - GetSideLength(m_vertices[2], m_vertices[0]))
    );
};

float CTriangle::GetSideLength(Point const& firstVertex, Point const& secondVertex) const
{
    float dx = firstVertex.x - secondVertex.x;
    float dy = firstVertex.y - secondVertex.y;
    return std::hypot(dx, dy);
};

float CTriangle::GetPerimeter() const
{
    return GetSideLength(m_vertices[0], m_vertices[1]) +
        GetSideLength(m_vertices[1], m_vertices[2]) +
        GetSideLength(m_vertices[2], m_vertices[0]);
};

void CTriangle::AppendProperties(std::ostream & strm) const
{
	strm << "  Perimeter = " << GetPerimeter()
		<< "  Area = " << GetArea()
		<< "  Coordinate 1 point  = " << m_vertices[0].x << " : " << m_vertices[0].y
		<< "  Coordinate 2 point  = " << m_vertices[1].x << " : " << m_vertices[1].y
		<< "  Coordinate 3 point  = " << m_vertices[2].x << " : " << m_vertices[2].y;
}

void CTriangle::Draw(ICanvas & canvas) const
{
    canvas.DrawLine(m_vertices[0], m_vertices[1], m_outlineColor);
    canvas.DrawLine(m_vertices[1], m_vertices[2], m_outlineColor);
    canvas.DrawLine(m_vertices[2], m_vertices[0], m_outlineColor);
    canvas.FillPolygon(m_vertices, m_fillColor);
}