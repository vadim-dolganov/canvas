#include "stdafx.h"
#include "IShape.h"

IShape::IShape(std::string const& type)
    :m_type(type)
{
}

std::string IShape::ToString() const
{
    std::ostringstream strm;
    strm << m_type + ": "
        << "  S = " << GetArea()
        << "  P = " << GetPerimeter();
    AppendProperties(strm);
    return strm.str();
}