#include "stdafx.h"
#include "ShapeFactory.h"

using namespace std;
using namespace std::placeholders;

ShapeFactory::ShapeFactory()
	: m_shapeCreationMap({
		{ "line", bind(&ShapeFactory::CreateLine, this, _1) },
		{ "circle", bind(&ShapeFactory::CreateCircle, this, _1) },
		{ "rectangle", bind(&ShapeFactory::CreateRectangle, this, _1) },
		{ "triangle", bind(&ShapeFactory::CreateTriangle, this, _1) },
		{ "ellipse", bind(&ShapeFactory::CreateEllipse, this, _1) },
		{ "rhombus", bind(&ShapeFactory::CreateRhombus, this, _1) },
		{ "trapezoid", bind(&ShapeFactory::CreateTrapezoid, this, _1) },
})
{
}

std::vector<std::string> ShapeFactory::GetTokens(std::string const& shapeSpecification)
{
	std::vector<std::string> tokens;
	const boost::char_separator<char> delimiters(", ");
	boost::tokenizer<boost::char_separator<char>> tokenizer(shapeSpecification, delimiters);
	std::copy(tokenizer.begin(), tokenizer.end(), std::back_inserter(tokens));
	return tokens;
}

std::shared_ptr<IShape> ShapeFactory::CreateShape(std::string const & description)
{
	std::shared_ptr<IShape> result;

	std::string shapeType;
	std::istringstream stream(description);

	stream >> shapeType;

	auto it = m_shapeCreationMap.find(shapeType);
	if (it != m_shapeCreationMap.end())
	{
		result = it->second(stream);
	}
	else
	{
		throw std::invalid_argument("Invalid shape type!");
	}

	return result;
}

std::shared_ptr<IShape> ShapeFactory::CreateLine(std::istream & args)
{
	std::string shapeSpecification;
	getline(args, shapeSpecification);
	std::vector<std::string> tokens = GetTokens(shapeSpecification);
	if (tokens.size() != 7)
	{
		throw std::invalid_argument("Invalid number of parameters! Usage: <x1> <y1> <x2> <y2> <colorOutline> <move_x> <move_y>");
	}
	Point startPoint, endPoint;
	try
	{
		startPoint.x = boost::lexical_cast<float>(tokens[0]);
		startPoint.y = boost::lexical_cast<float>(tokens[1]);
		endPoint.x = boost::lexical_cast<float>(tokens[2]);
		endPoint.y = boost::lexical_cast<float>(tokens[3]);
	}
	catch (boost::bad_lexical_cast const& error)
	{
		throw std::runtime_error(error.what());
	}
	Color outlineColor;
	if (ConvertHexInRGBColor(tokens[4], outlineColor))
	{
		return std::make_shared<CLineSegment>(CLineSegment(startPoint, endPoint, outlineColor));
	}
	throw std::invalid_argument("Invalid hex value");
}

std::shared_ptr<IShape> ShapeFactory::CreateCircle(std::istream & args)
{
	std::string shapeSpecification;
	getline(args, shapeSpecification);
	std::vector<std::string> tokens = GetTokens(shapeSpecification);
	if (tokens.size() != 7)
	{
		throw std::invalid_argument("Invalid number of parameters! Usage: <x1> <y1> <radius> <colorOutline> <fillColor> <move_x> <move_y>");
	}
	Point position;
	float radius;
	try
	{
		float move_x = boost::lexical_cast<float>(tokens[5]);
		float move_y = boost::lexical_cast<float>(tokens[6]);
		position.x = boost::lexical_cast<float>(tokens[0]) + move_x;
		position.y = boost::lexical_cast<float>(tokens[1]) + move_y;
		radius = boost::lexical_cast<float>(tokens[2]);
	}
	catch (boost::bad_lexical_cast const& error)
	{
		throw std::runtime_error(error.what());
	}
	Color outlineColor;
	Color fillColor;
	if (ConvertHexInRGBColor(tokens[3], outlineColor) && ConvertHexInRGBColor(tokens[4], fillColor))
	{
		return std::make_shared<CCircle>(CCircle(position, radius, outlineColor, fillColor));
	}
	throw std::invalid_argument("Invalid hex value");
}

std::shared_ptr<IShape> ShapeFactory::CreateEllipse(std::istream & args)
{
	std::string shapeSpecification;
	getline(args, shapeSpecification);
	std::vector<std::string> tokens = GetTokens(shapeSpecification);
	if (tokens.size() != 8)
	{
		throw std::invalid_argument("Invalid number of parameters! Usage: <center_x> <center_y> <radius_x> <radius_y> <fillColor> <move_x> <move_y> <rotation_angle>");
	}
	Point position;
	float radius_x;
	float radius_y;
	float rotationAngle;
	try
	{
		float move_x = boost::lexical_cast<float>(tokens[5]);
		float move_y = boost::lexical_cast<float>(tokens[6]);
		position.x = boost::lexical_cast<float>(tokens[0]) + move_x;
		position.y = boost::lexical_cast<float>(tokens[1]) + move_y;
		radius_x = boost::lexical_cast<float>(tokens[2]);
		radius_y = boost::lexical_cast<float>(tokens[3]);
		rotationAngle = boost::lexical_cast<float>(tokens[7]);
	}
	catch (boost::bad_lexical_cast const& error)
	{
		throw std::runtime_error(error.what());
	}
	Color fillColor;
	if (ConvertHexInRGBColor(tokens[4], fillColor))
	{
		return std::make_shared<CEllipse>(CEllipse(position, radius_x, radius_y, fillColor, rotationAngle));
	}
	throw std::invalid_argument("Invalid hex value");
}

std::shared_ptr<IShape> ShapeFactory::CreateRectangle(std::istream & args)
{
	std::string shapeSpecification;
	getline(args, shapeSpecification);
	std::vector<std::string> tokens = GetTokens(shapeSpecification);
	if (tokens.size() != 9)
	{
		throw std::invalid_argument("Invalid number of parameters! Usage: <x1> <y1> <width> <height> <colorOutline> <fillColor> <move_x> <move_y> <rotation_angle>");
	}
	Point position;
	float width;
	float height;
	float rotationAngle;
	try
	{
		float move_x = boost::lexical_cast<float>(tokens[6]);
		float move_y = boost::lexical_cast<float>(tokens[7]);
		position.x = boost::lexical_cast<float>(tokens[0]) + move_x;
		position.y = boost::lexical_cast<float>(tokens[1]) + move_y;
		width = boost::lexical_cast<float>(tokens[2]);
		height = boost::lexical_cast<float>(tokens[3]);
		rotationAngle = boost::lexical_cast<float>(tokens[8]);
	}
	catch (boost::bad_lexical_cast const& error)
	{
		throw std::runtime_error(error.what());
	}

	Color outlineColor;
	Color fillColor;
	if (ConvertHexInRGBColor(tokens[4], outlineColor) && ConvertHexInRGBColor(tokens[5], fillColor))
	{
		return std::make_shared<CRectangle>(CRectangle(position, width, height, outlineColor, fillColor, rotationAngle));
	}
	throw std::invalid_argument("Invalid hex value");
}

std::shared_ptr<IShape> ShapeFactory::CreateRhombus(std::istream & args)
{
	std::string shapeSpecification;
	getline(args, shapeSpecification);
	std::vector<std::string> tokens = GetTokens(shapeSpecification);
	if (tokens.size() != 9)
	{
		throw std::invalid_argument("Invalid number of parameters! Usage: <x1> <y1> <width> <height> <colorOutline> <fillColor> <move_x> <move_y> <rotation_angle>");
	}
	Point position;
	float width;
	float height;
	float rotationAngle;
	try
	{
		float move_x = boost::lexical_cast<float>(tokens[6]);
		float move_y = boost::lexical_cast<float>(tokens[7]);
		position.x = boost::lexical_cast<float>(tokens[0]) + move_x;
		position.y = boost::lexical_cast<float>(tokens[1]) + move_y;
		width = boost::lexical_cast<float>(tokens[2]);
		height = boost::lexical_cast<float>(tokens[3]);
		rotationAngle = boost::lexical_cast<float>(tokens[8]);
	}
	catch (boost::bad_lexical_cast const& error)
	{
		throw std::runtime_error(error.what());
	}

	Color outlineColor;
	Color fillColor;
	if (ConvertHexInRGBColor(tokens[4], outlineColor) && ConvertHexInRGBColor(tokens[5], fillColor))
	{
		return std::make_shared<CRhombus>(CRhombus(position, width, height, outlineColor, fillColor, rotationAngle));
	}
	throw std::invalid_argument("Invalid hex value");
}

std::shared_ptr<IShape> ShapeFactory::CreateTrapezoid(std::istream & args)
{
	std::string shapeSpecification;
	getline(args, shapeSpecification);
	std::vector<std::string> tokens = GetTokens(shapeSpecification);
	if (tokens.size() != 10)
	{
		throw std::invalid_argument("Invalid number of parameters! Usage: <x1> <y1> <topy_width> <bottom_width> <height> <colorOutline> <fillColor> <move_x> <move_y> <rotation_angle>");
	}
	Point position;
	float topWidth;
	float bottomWidth;
	float height;
	float rotationAngle;
	try
	{
		float move_x = boost::lexical_cast<float>(tokens[7]);
		float move_y = boost::lexical_cast<float>(tokens[8]);
		position.x = boost::lexical_cast<float>(tokens[0]) + move_x;
		position.y = boost::lexical_cast<float>(tokens[1]) + move_y;
		topWidth = boost::lexical_cast<float>(tokens[2]);
		bottomWidth = boost::lexical_cast<float>(tokens[3]);
		height = boost::lexical_cast<float>(tokens[4]);
		rotationAngle = boost::lexical_cast<float>(tokens[9]);
	}
	catch (boost::bad_lexical_cast const& error)
	{
		throw std::runtime_error(error.what());
	}

	Color outlineColor;
	Color fillColor;
	if (ConvertHexInRGBColor(tokens[5], outlineColor) && ConvertHexInRGBColor(tokens[6], fillColor))
	{
		return std::make_shared<CTrapezoid>(CTrapezoid(position, topWidth, bottomWidth, height, outlineColor, fillColor, rotationAngle));
	}
	throw std::invalid_argument("Invalid hex value");
}

std::shared_ptr<IShape> ShapeFactory::CreateTriangle(std::istream & args)
{
	std::string shapeSpecification;
	getline(args, shapeSpecification);
	std::vector<std::string> tokens = GetTokens(shapeSpecification);
	if (tokens.size() != 11)
	{
		throw std::invalid_argument("Invalid number of parameters! Usage: <x1> <y1> <x2> <y2> <x3> <y3> <colorOutline> <fillColor> <move_x> <move_y> <rotation_angle>");
	}
	Point vertex1;
	Point vertex2;
	Point vertex3;
	float rotationAngle;
	try
	{
		float move_x = boost::lexical_cast<float>(tokens[8]);
		float move_y = boost::lexical_cast<float>(tokens[9]);
		vertex1.x = boost::lexical_cast<float>(tokens[0]) + move_x;
		vertex1.y = boost::lexical_cast<float>(tokens[1]) + move_y;
		vertex2.x = boost::lexical_cast<float>(tokens[2]) + move_x;
		vertex2.y = boost::lexical_cast<float>(tokens[3]) + move_y;
		vertex3.x = boost::lexical_cast<float>(tokens[4]) + move_x;
		vertex3.y = boost::lexical_cast<float>(tokens[5]) + move_y;
		rotationAngle = boost::lexical_cast<float>(tokens[10]);
	}
	catch (boost::bad_lexical_cast const& error)
	{
		throw std::runtime_error(error.what());
	}
	Color outlineColor;
	Color fillColor;
	if (ConvertHexInRGBColor(tokens[6], outlineColor) && ConvertHexInRGBColor(tokens[7], fillColor))
	{
		return std::make_shared<CTriangle>(CTriangle(vertex1, vertex2, vertex3, outlineColor, fillColor, rotationAngle));
	}
	throw std::invalid_argument("Invalid hex value");
}