#pragma once
#include "Point.h"
#include "Color.h"

class ICanvas
{
public:
    virtual ~ICanvas() = default;

    virtual void DrawLine(Point const& startPoint, Point const& endPoint, Color const& outlineColor) = 0;

    virtual void FillPolygon(Vertices const& vertices, Color const& fillColor) = 0;

    virtual void DrawCircle(Point const& center, float radius, Color const& outlineColor) = 0;
	virtual void FillCircle(Point const& center, float radius, Color const& fillColor) = 0;
	virtual void DrawEllipse(Point const& center, float xRadius, float yRadius, Color const& fillColor, float rotationAngle) = 0;
};