#pragma once
#include "IShape.h"

class IShapeFactory
{
public:
	virtual std::shared_ptr<IShape> CreateShape(std::string const& description) = 0;
	virtual ~IShapeFactory() = default;
};

