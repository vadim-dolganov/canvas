#pragma once
#include "IShapeFactory.h"
#include "Point.h"
#include "LineSegment.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Ellipse.h"
#include "Rhombus.h"
#include "Triangle.h"
#include "Trapezoid.h"
#include "Color.h"

typedef std::map<std::string, std::function<std::shared_ptr<IShape>(std::istream & args)>> ShapeCreationMap;
class ShapeFactory : public IShapeFactory
{
public:
	ShapeFactory();
	std::shared_ptr<IShape> CreateShape(std::string const& description) override;
private:
	const ShapeCreationMap m_shapeCreationMap;

	std::shared_ptr<IShape> CreateLine(std::istream & args);
	std::shared_ptr<IShape> CreateCircle(std::istream & args);
	std::shared_ptr<IShape> CreateRectangle(std::istream & args);
	std::shared_ptr<IShape> CreateRhombus(std::istream & args);
	std::shared_ptr<IShape> CreateTriangle(std::istream & args);
	std::shared_ptr<IShape> CreateEllipse(std::istream & args);
	std::shared_ptr<IShape> CreateTrapezoid(std::istream & args);

	std::vector<std::string> GetTokens(std::string const& shapeSpecification);
};

