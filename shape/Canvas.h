#pragma once
#include "ICanvas.h"
#include "Point.h"
#include "IShape.h"
#include "Color.h"

class CCanvas : public ICanvas
{
public:
    CCanvas() = default;
    ~CCanvas() = default;
    
    void DrawShapes(std::vector<std::shared_ptr<IShape>> const& shapes);

    void DrawLine(Point const& startPoint, Point const& endPoint, Color const& outlineColor) override;

    void FillPolygon(Vertices const& vertices, Color const& fillColor) override;

	void DrawCircle(Point const& center, float radius, Color const& outlineColor) override;
	void DrawEllipse(Point const& center, float xRadius, float yRadius, Color const& fillColor, float rotationAngle) override;
	void FillCircle(Point const& center, float radius, Color const& fillColor) override;
};