#include "stdafx.h"
#include "Triangle.h"
#include "SolidShape.h"
#include "Point.h"

CTriangle::CTriangle(Point const& firstVertex, Point const& secondVertex, Point const& thirdVertex, Color const& outlineColor, Color const& fillColor)
    :ISolidShape("Triangle"),
    m_fillColor(fillColor),
    m_outlineColor(outlineColor)
{
    m_vertices.push_back(firstVertex);
    m_vertices.push_back(secondVertex);
    m_vertices.push_back(thirdVertex);
}

Color CTriangle::GetOutlineColor() const
{
    return m_outlineColor;
};

Color CTriangle::GetFillColor() const
{
    return m_fillColor;
};

Point const& CTriangle::GetVertex1() const
{
    return m_vertices[0];
}

Point const& CTriangle::GetVertex2() const
{
    return m_vertices[1];
}

Point const& CTriangle::GetVertex3() const
{
    return m_vertices[2];
}

float CTriangle::GetArea() const
{
    float semiperimeter = GetPerimeter() * 0.5f;
    return std::sqrt(semiperimeter*(semiperimeter - GetSideLength(m_vertices[0], m_vertices[1]))*
        (semiperimeter - GetSideLength(m_vertices[1], m_vertices[2]))*
        (semiperimeter - GetSideLength(m_vertices[2], m_vertices[0]))
    );
};

float CTriangle::GetSideLength(Point const& firstVertex, Point const& secondVertex) const
{
    float dx = firstVertex.x - secondVertex.x;
    float dy = firstVertex.y - secondVertex.y;
    return std::hypot(dx, dy);
};

float CTriangle::GetPerimeter() const
{
    return GetSideLength(m_vertices[0], m_vertices[1]) +
        GetSideLength(m_vertices[1], m_vertices[2]) +
        GetSideLength(m_vertices[2], m_vertices[0]);
};

void CTriangle::AppendProperties(std::ostream & strm) const
{
}

void CTriangle::Draw(ICanvas & canvas) const
{
    canvas.DrawLine(m_vertices[0], m_vertices[1], m_outlineColor);
    canvas.DrawLine(m_vertices[1], m_vertices[2], m_outlineColor);
    canvas.DrawLine(m_vertices[2], m_vertices[0], m_outlineColor);
    canvas.FillPolygon(m_vertices, m_fillColor);
}