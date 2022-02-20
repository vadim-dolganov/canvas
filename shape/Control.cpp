#include "stdafx.h"
#include "Control.h"
#include "IShape.h"

using namespace std;
using namespace std::placeholders;

CRemoteControl::CRemoteControl(std::ifstream & input, std::ostream & output, std::vector<std::shared_ptr<IShape>> & shapes)
    :m_shapes(shapes)
    , m_input(input)
    , m_output(output)
    , m_actionMap({
        { "line", bind(&CRemoteControl::CreateLine, this, _1) },
        { "circle", bind(&CRemoteControl::CreateCircle, this, _1) },
        { "rectangle", bind(&CRemoteControl::CreateRectangle, this, _1) },
		{ "triangle", bind(&CRemoteControl::CreateTriangle, this, _1) },
		{ "ellipse", bind(&CRemoteControl::CreateEllipse, this, _1) },
		{ "trapezoid", bind(&CRemoteControl::CreateTrapezoid, this, _1) },
})
{
}

void CRemoteControl::PrintInfo() const
{
    if (!m_shapes.empty())
    {
        auto shapeWithMinPerimeter = std::min_element(m_shapes.begin(), m_shapes.end(), [&]
        (std::shared_ptr<IShape> const& firstShape, std::shared_ptr<IShape> const& secondShape)
        {
            return firstShape->GetPerimeter() < secondShape->GetPerimeter();
        });
        m_output << "Shape with minimum perimeter:\n";
        m_output << (*shapeWithMinPerimeter)->ToString() << "\n";

        auto shapeWithMaxArea = std::max_element(m_shapes.begin(), m_shapes.end(), [&]
        (std::shared_ptr<IShape> const& firstShape, std::shared_ptr<IShape> const& secondShape)
        {
            return firstShape->GetArea() < secondShape->GetArea();
        });
        m_output << "The shape with the largest area:\n";
        m_output << (*shapeWithMaxArea)->ToString() << "\n";

        m_output << "|SHAPES|\n";
        for (auto const& shape : m_shapes)
        {
            m_output << ">" << shape->ToString() << "\n";

        }
    }
}

bool CRemoteControl::HandleCommand()
{
    string commandLine;
    getline(m_input, commandLine);
    istringstream strm(commandLine);
    string action;
    strm >> action;
    if (strm.eof() && action.empty())
    {
        return true;
    }
    auto it = m_actionMap.find(action);
    if (it != m_actionMap.end())
    {
        it->second(strm);
        return true;
    }
    return false;
}

std::vector<std::string> CRemoteControl::GetTokens(std::string const& shapeSpecification) const
{
    std::vector<std::string> tokens;
    const boost::char_separator<char> delimiters(", ");
    boost::tokenizer<boost::char_separator<char>> tokenizer(shapeSpecification, delimiters);
    std::copy(tokenizer.begin(), tokenizer.end(), std::back_inserter(tokens));
    return tokens;
}

bool CRemoteControl::CreateLine(std::istream & args)
{
    std::string shapeSpecification;
    getline(args, shapeSpecification);
    std::vector<std::string> tokens = GetTokens(shapeSpecification);
    if (tokens.size() != 7)
    {
        m_output << "Invalid number of parameters!!!\n"
            << "Usage: <x1> <y1> <x2> <y2> <colorOutline> <move_x> <move_y>\n";
        return false;
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
        m_output << error.what() << "\n";
        return false;
    }
    Color outlineColor;
    if (ConvertHexInRGBColor(tokens[4], outlineColor))
    {
        m_shapes.push_back(std::make_shared<CLineSegment>(CLineSegment(startPoint, endPoint, outlineColor)));
        return true;
    }
    return false;
}

bool CRemoteControl::CreateCircle(std::istream & args)
{
	std::string shapeSpecification;
	getline(args, shapeSpecification);
	std::vector<std::string> tokens = GetTokens(shapeSpecification);
	if (tokens.size() != 7)
	{
		m_output << "Invalid number of parameters!!!\n"
			<< "Usage: <x1> <y1> <radius> <colorOutline> <fillColor> <move_x> <move_y>\n";
		return false;
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
		m_output << error.what() << "\n";
		return false;
	}
	Color outlineColor;
	Color fillColor;
	if (ConvertHexInRGBColor(tokens[3], outlineColor) && ConvertHexInRGBColor(tokens[4], fillColor))
	{
		m_shapes.push_back(std::make_shared<CCircle>(CCircle(position, radius, outlineColor, fillColor)));
		return true;
	}
	return false;
}

bool CRemoteControl::CreateEllipse(std::istream & args)
{
	std::string shapeSpecification;
	getline(args, shapeSpecification);
	std::vector<std::string> tokens = GetTokens(shapeSpecification);
	if (tokens.size() != 8)
	{
		m_output << "Invalid number of parameters!!!\n"
			<< "Usage: <center_x> <center_y> <radius_x> <radius_y> <fillColor> <move_x> <move_y> <rotation_angle>\n";
		return false;
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
		m_output << error.what() << "\n";
		return false;
	}
	Color fillColor;
	if (ConvertHexInRGBColor(tokens[4], fillColor))
	{
		m_shapes.push_back(std::make_shared<CEllipse>(CEllipse(position, radius_x, radius_y, fillColor, rotationAngle)));
		return true;
	}
	return false;
}

bool CRemoteControl::CreateRectangle(std::istream & args)
{
	std::string shapeSpecification;
	getline(args, shapeSpecification);
	std::vector<std::string> tokens = GetTokens(shapeSpecification);
	if (tokens.size() != 9)
	{
		m_output << "Invalid number of parameters!!!\n"
			<< "Usage: <x1> <y1> <width> <height> <colorOutline> <fillColor> <move_x> <move_y> <rotation_angle>\n";
		return false;
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
		m_output << error.what() << "\n";
		return false;
	}

	Color outlineColor;
	Color fillColor;
	if (ConvertHexInRGBColor(tokens[4], outlineColor) && ConvertHexInRGBColor(tokens[5], fillColor))
	{
		m_shapes.push_back(std::make_shared<CRectangle>(CRectangle(position, width, height, outlineColor, fillColor, rotationAngle)));
		return true;
	}
	return false;
}

bool CRemoteControl::CreateTrapezoid(std::istream & args)
{
	std::string shapeSpecification;
	getline(args, shapeSpecification);
	std::vector<std::string> tokens = GetTokens(shapeSpecification);
	if (tokens.size() != 9)
	{
		m_output << "Invalid number of parameters!!!\n"
			<< "Usage: <x1> <y1> <width> <height> <colorOutline> <fillColor> <move_x> <move_y> <rotation_angle>\n";
		return false;
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
		m_output << error.what() << "\n";
		return false;
	}

	Color outlineColor;
	Color fillColor;
	if (ConvertHexInRGBColor(tokens[4], outlineColor) && ConvertHexInRGBColor(tokens[5], fillColor))
	{
		m_shapes.push_back(std::make_shared<CTrapezoid>(CTrapezoid(position, width, height, outlineColor, fillColor, rotationAngle)));
		return true;
	}
	return false;
}

bool CRemoteControl::CreateTriangle(std::istream & args)
{
    std::string shapeSpecification;
    getline(args, shapeSpecification);
    std::vector<std::string> tokens = GetTokens(shapeSpecification);
    if (tokens.size() != 11)
    {
        m_output << "Invalid number of parameters!!!\n"
            << "Usage: <x1> <y1> <x2> <y2> <x3> <y3> <colorOutline> <fillColor> <move_x> <move_y> <rotation_angle>\n";
        return false;
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
        m_output << error.what() << "\n";
        return false;
    }
    Color outlineColor;
    Color fillColor;
    if (ConvertHexInRGBColor(tokens[6], outlineColor) && ConvertHexInRGBColor(tokens[7], fillColor))
    {
        m_shapes.push_back(std::make_shared<CTriangle>(CTriangle(vertex1, vertex2, vertex3, outlineColor, fillColor, rotationAngle)));
        return true;
    }
    return false;
}