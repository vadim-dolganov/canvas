#include "stdafx.h"
#include "Canvas.h"
#include "IShape.h"
#include "const.h"

void CCanvas::DrawShapes(std::vector<std::shared_ptr<IShape>> const& shapes)
{
    for (auto shape : shapes)
    {
        shape->Draw(*this);
    }
}

void CCanvas::DrawLine(Point const& startPoint, Point const& endPoint, Color const& outlineColor)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glColor3f(outlineColor.red, outlineColor.green, outlineColor.blue);
    glLineWidth(2);
    glBegin(GL_LINES);
        glVertex2f(startPoint.x, startPoint.y);
        glVertex2f(endPoint.x, endPoint.y);
    glEnd();
    glDisable(GL_LINE_SMOOTH);
}

void CCanvas::FillPolygon(Vertices const& vertices, Color const& fillColor)
{
    glBegin(GL_POLYGON);
    for (size_t i = 0; i < vertices.size(); i++)
    {
        glColor3f(fillColor.red, fillColor.green, fillColor.blue);
        glVertex2f(vertices[i].x, vertices[i].y);
    }
    glEnd();
}

void CCanvas::DrawCircle(Point const& center, float radius, Color const& outlineColor)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glBegin(GL_LINE_LOOP);
    glColor3f(outlineColor.red, outlineColor.green, outlineColor.blue);
    for (float angle = 0; angle <= MAX_ANGLE; angle += STEP)
    {
        glVertex2f(
            center.x + (radius * cos(angle * DEGREE_TO_RAD)),
            center.y + (radius* sin(angle * DEGREE_TO_RAD))
        );
    }
    glEnd();
    glDisable(GL_LINE_SMOOTH);
}

void CCanvas::FillCircle(Point const& center, float radius, Color const& fillColor)
{
	glBegin(GL_TRIANGLE_FAN);
	for (float angle = 0; angle <= MAX_ANGLE; angle += STEP)
	{
		glColor3f(fillColor.red, fillColor.green, fillColor.blue);
		glVertex2f(
			center.x + (radius * cos(angle * DEGREE_TO_RAD)),
			center.y + (radius* sin(angle * DEGREE_TO_RAD))
		);
	}
	glEnd();
}

void CCanvas::DrawEllipse(Point const& center, float xRadius, float yRadius, Color const& fillColor, float rotationAngle)
{
	const float step = float(1 * M_PI / MAX_ANGLE);
	const float c = std::cos(rotationAngle * M_PI / 180);
	const float s = std::sin(rotationAngle * M_PI / 180);
	glBegin(GL_LINE_STRIP);
	for (float angle = 0; angle < float(2 * M_PI); angle += step)
	{
		const float dx = xRadius * cosf(angle);
		const float dy = yRadius * sinf(angle);
		const float rotate_x = dx *  c - dy * s;
		const float rotate_y = dy *  c + dx * s;
		glVertex2f(rotate_x + center.x, rotate_y + center.y);
	}
	glEnd();
}