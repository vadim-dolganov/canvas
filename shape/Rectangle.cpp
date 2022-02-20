#include "stdafx.h"
#include "Rectangle.h"
#include "SolidShape.h"
#include "Point.h"
CRectangle::CRectangle(Point const& leftTop, float width, float height, Color const& outlineColor, Color const& fillColor, float rotationAngle)
    :ISolidShape("Rectangle"), 
    m_height(height),
    m_width(width),
    m_fillColor(fillColor),
    m_outlineColor(outlineColor),
	m_rotationAngle(rotationAngle)
{
	Point center = { leftTop.x + m_width / 2, leftTop.y + m_height / 2 };
	float c = std::cos(m_rotationAngle * M_PI / 180);
	float s = std::sin(m_rotationAngle * M_PI / 180);
	m_vertices.push_back({ center.x + (leftTop.x - center.x) * c - (leftTop.y - center.y) * s, center.y + (leftTop.x - center.x) * s + (leftTop.y - center.y) * c });
	m_vertices.push_back({ center.x + (leftTop.x + m_width - center.x) * c - (leftTop.y - center.y) * s, center.y + (leftTop.x + m_width - center.x) * s + (leftTop.y - center.y) * c });
	m_vertices.push_back({ center.x + (leftTop.x + m_width - center.x) * c - (leftTop.y + m_height - center.y) * s, center.y + (leftTop.x + m_width - center.x) * s + (leftTop.y + m_height - center.y) * c });
	m_vertices.push_back({ center.x + (leftTop.x - center.x) * c - (leftTop.y + m_height - center.y) * s, center.y + (leftTop.x - center.x) * s + (leftTop.y + m_height - center.y) * c });
}

float CRectangle::GetWidth() const
{
    return m_width;
};

float CRectangle::GetHeight() const
{
    return m_height;
};

Color CRectangle::GetOutlineColor() const
{
    return m_outlineColor;
};

Color CRectangle::GetFillColor() const
{
    return m_fillColor;
};

float CRectangle::GetArea() const
{
    return m_width * m_height;
};

float CRectangle::GetPerimeter() const
{
    return 2 * (m_width + m_height);
};

void CRectangle::AppendProperties(std::ostream & strm) const
{
    strm << "  Width = " << m_width
		<< "  Height = " << m_height
		<< "  Perimeter = " << GetPerimeter()
		<< "  Area = " << GetArea()
		<< "  Coordinate 1 point  = " << m_vertices[0].x << " : " << m_vertices[0].y
		<< "  Coordinate 2 point  = " << m_vertices[1].x << " : " << m_vertices[1].y
		<< "  Coordinate 3 point  = " << m_vertices[2].x << " : " << m_vertices[2].y
		<< "  Coordinate 4 point  = " << m_vertices[3].x << " : " << m_vertices[3].y;
}

void CRectangle::Draw(ICanvas & canvas) const
{
    canvas.DrawLine(m_vertices[0], m_vertices[1], m_outlineColor);
    canvas.DrawLine(m_vertices[1], m_vertices[2], m_outlineColor);
    canvas.DrawLine(m_vertices[2], m_vertices[3], m_outlineColor);
    canvas.DrawLine(m_vertices[3], m_vertices[0], m_outlineColor);
    canvas.FillPolygon(m_vertices, m_fillColor);




















}