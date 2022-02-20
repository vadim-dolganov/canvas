#pragma once
#include "SolidShape.h"
#include "Point.h"
#include "Color.h"

class CEllipse : public ISolidShape
{
public:
	CEllipse(Point const& center, float xRadius, float yRadius, Color const& fillColor);
	~CEllipse() = default;
	float GetArea() const override;
	float GetPerimeter() const override;
	Color GetOutlineColor() const override;
	Color GetFillColor() const override;
	float GetXRadius() const;
	float GetYRadius() const;
	Point const& GetCenter() const;

	void Draw(ICanvas & canvas) const override;
protected:
	void AppendProperties(std::ostream & strm) const override;
private:
	Point m_center;
	float m_radius_x;
	float m_radius_y;
	Color m_fillColor;
};