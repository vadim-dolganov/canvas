#pragma once
#include "Point.h"
#include "SolidShape.h"
#include "Color.h"

class CTrapezoid : public ISolidShape
{
public:
	CTrapezoid(Point const& center, float topWidth, float bottomWidth, float height, Color const& outlineColor, Color const& fillColor, float rotationAngle);
	~CTrapezoid() = default;
	float GetArea() const override;
	float GetPerimeter() const override;
	Color GetOutlineColor() const override;
	Color GetFillColor() const override;
	float GetHeight() const;

	void Draw(ICanvas & canvas) const override;
protected:
	void AppendProperties(std::ostream & strm) const override;
private:
	float m_topWidth;
	float m_bottomWidth;
	float m_height;
	Color m_outlineColor;
	Color m_fillColor;
	Vertices m_vertices;
	float m_rotationAngle;
};