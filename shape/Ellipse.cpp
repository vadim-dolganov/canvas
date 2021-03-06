#include "stdafx.h"
#include "Ellipse.h"
#include "SolidShape.h"
#include "Point.h"
#include "const.h"

CEllipse::CEllipse(Point const& center, float xRadius, float yRadius, Color const& fillColor, float rotationAngle)
	:ISolidShape("Ellipse"),
	m_center(center),
	m_radius_x(xRadius),
	m_radius_y(yRadius),
	m_fillColor(fillColor),
	m_rotationAngle(rotationAngle)
{
}

Point const& CEllipse::GetCenter() const
{
	return m_center;
}

float CEllipse::GetXRadius() const
{
	return m_radius_x;
}

float CEllipse::GetYRadius() const
{
	return m_radius_y;
}

Color CEllipse::GetFillColor() const
{
	return m_fillColor;
};

Color CEllipse::GetOutlineColor() const
{
    return m_fillColor;
};

float CEllipse::GetArea() const
{
	return PI * m_radius_x * m_radius_y;
};

float CEllipse::GetPerimeter() const
{
	return 2 * PI * std::sqrt((std::pow(m_radius_x, 2) + std::pow(m_radius_x, 2)) / 2);
};

void CEllipse::AppendProperties(std::ostream & strm) const
{
	strm << "  x_RADIUS = " << m_radius_x
		<< "  Y_RADIUS  = " << m_radius_y
		<< "  Center  = " << m_center.x << " : " << m_center.y;
}

void CEllipse::Draw(ICanvas & canvas) const
{
	canvas.DrawEllipse(m_center, m_radius_x, m_radius_y, m_fillColor, m_rotationAngle);
}