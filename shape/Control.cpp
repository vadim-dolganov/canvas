#include "stdafx.h"
#include "Control.h"
#include "IShape.h"
#include "ShapeFactory.h"
#include "IShapeFactory.h"

using namespace std;

CRemoteControl::CRemoteControl(std::ifstream & input, std::ostream & output, std::vector<std::shared_ptr<IShape>> & shapes)
    :m_shapes(shapes)
    , m_input(input)
    , m_output(output)
	, m_factory(ShapeFactory())
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
	try
	{
		auto shape = m_factory.CreateShape(commandLine);
		m_shapes.push_back(shape);
		return true;
	}
	catch (const std::exception& e)
	{
		m_output << e.what() << std::endl;
		return false;
	}
}

