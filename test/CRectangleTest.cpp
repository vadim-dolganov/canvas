#include "stdafx.h"
#include "PointTest.h"
#include "../shape/Rectangle.h"

struct RectangleFixture_
{
    CRectangle rectangle;
    RectangleFixture_()
        :rectangle({ 10, 10 }, 100, 10, { 10, 100, 20 }, { 100, 10, 2 })
    {}
};

BOOST_FIXTURE_TEST_SUITE(Rectangle, RectangleFixture_)

    BOOST_AUTO_TEST_CASE(has_a_perimeter)
    {
        BOOST_CHECK(rectangle.GetPerimeter() == 220);
    }

    BOOST_AUTO_TEST_CASE(has_a_area)
    {
        BOOST_CHECK(rectangle.GetArea() == 1000);
    }

    BOOST_AUTO_TEST_CASE(to_string)
    {
        BOOST_CHECK(rectangle.ToString() == "Rectangle:   S = 1000  P = 220  Width = 100  Height = 10");
    }

BOOST_AUTO_TEST_SUITE_END()