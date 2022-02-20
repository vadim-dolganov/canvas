
#include "stdafx.h"
#include "Trapezoid.h"
#include "SolidShape.h"
#include "Point.h"
CTrapezoid::CTrapezoid(Point const& center, float width, float height, Color const& outlineColor, Color const& fillColor, float rotationAngle)
	:ISolidShape("Trapezoid"),
	m_height(height),
	m_width(width),
	m_fillColor(fillColor),
	m_outlineColor(outlineColor),
	m_rotationAngle(rotationAngle)
{
	float c = std::cos(m_rotationAngle * M_PI / 180);
	float s = std::sin(m_rotationAngle * M_PI / 180);
	Point fisrt = { center.x , center.y - height / 2 };
	Point second = { center.x + width / 2, center.y };
	Point third = { center.x , center.y + height / 2 };
	Point fourth = { center.x - width / 2, center.y };
	m_vertices.push_back({ center.x + (fisrt.x - center.x) * c - (fisrt.y - center.y) * s, center.y + (fisrt.x - center.x) * s + (fisrt.y - center.y) * c });
	m_vertices.push_back({ center.x + (second.x - center.x) * c - (second.y - center.y) * s, center.y + (second.x - center.x) * s + (second.y - center.y) * c });
	m_vertices.push_back({ center.x + (third.x - center.x) * c - (third.y - center.y) * s, center.y + (third.x - center.x) * s + (third.y - center.y) * c });
	m_vertices.push_back({ center.x + (fourth.x - center.x) * c - (fourth.y - center.y) * s, center.y + (fourth.x - center.x) * s + (fourth.y - center.y) * c });
}

float CTrapezoid::GetWidth() const
{
	return m_width;
};

float CTrapezoid::GetHeight() const
{
	return m_height;
};

Color CTrapezoid::GetOutlineColor() const
{
	return m_outlineColor;
};

Color CTrapezoid::GetFillColor() const
{
	return m_fillColor;
};

float CTrapezoid::GetArea() const
{
	return m_width * m_height;
};

float CTrapezoid::GetPerimeter() const
{
	return 2 * (m_width + m_height);
};

void CTrapezoid::AppendProperties(std::ostream & strm) const
{
	strm << "  Width = " << m_width
		<< "  Height = " << m_height
		<< "  LeftTop Coordinate  = " << m_vertices[0].x << " : " << m_vertices[0].y;
}

void CTrapezoid::Draw(ICanvas & canvas) const
{
	canvas.DrawLine(m_vertices[0], m_vertices[1], m_outlineColor);
	canvas.DrawLine(m_vertices[1], m_vertices[2], m_outlineColor);
	canvas.DrawLine(m_vertices[2], m_vertices[3], m_outlineColor);
	canvas.DrawLine(m_vertices[3], m_vertices[0], m_outlineColor);
	canvas.FillPolygon(m_vertices, m_fillColor);




















}