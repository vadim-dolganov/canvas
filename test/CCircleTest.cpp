#include "stdafx.h"
#include "PointTest.h"
#include "../shape/const.h"
#include "../shape/Circle.h"

struct CircleFixture_
{
    CCircle circle;
    CircleFixture_()
        :circle({ 10, 20 }, 100, {100, 100, 20}, { 100, 120, 20 })
    {}
};

BOOST_FIXTURE_TEST_SUITE(Circle, CircleFixture_)
    BOOST_AUTO_TEST_CASE(has_a_area)
    {
        BOOST_CHECK(circle.GetArea() == 100 * 100 * PI);
    }

    BOOST_AUTO_TEST_CASE(has_a_perimeter)
    {
        BOOST_CHECK(circle.GetPerimeter() == 2 * 100 * PI);
    }

    BOOST_AUTO_TEST_CASE(get_center_point)
    {
        IsPointsEqual(circle.GetCenter(), { 10, 20 });
    }

    BOOST_AUTO_TEST_CASE(get_radius)
    {
        BOOST_CHECK(circle.GetRadius() == 100);
    }

    BOOST_AUTO_TEST_CASE(to_string)
    {
        BOOST_CHECK(circle.ToString() == "Circle:   S = 31415.9  P = 628.318  Radius = 100");
    }
BOOST_AUTO_TEST_SUITE_END()
