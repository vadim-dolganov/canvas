#pragma once
#include <boost/noncopyable.hpp>
#include "ShapeFactory.h"

class IShape;

class CRemoteControl : boost::noncopyable
{
public:
    CRemoteControl(std::ifstream & input, std::ostream & output, std::vector<std::shared_ptr<IShape>> & shapes);
    bool HandleCommand();
    void PrintInfo() const;
private:
    std::vector<std::shared_ptr<IShape>> & m_shapes;
    std::ifstream & m_input;
    std::ostream & m_output;
	ShapeFactory m_factory;
};