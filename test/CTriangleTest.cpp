#include "stdafx.h"
#include "PointTest.h"
#include "../shape/Triangle.h"


struct TriangleFixture_
{
    CTriangle triangle;
    TriangleFixture_()
        :triangle({ 0, 0 }, { 0, 3 }, { 4, 3 }, {100, 100, 20}, {20, 30, 29})
    {}
};

BOOST_FIXTURE_TEST_SUITE(Triangle, TriangleFixture_)

    BOOST_AUTO_TEST_CASE(has_a_perimeter)
    {
        BOOST_CHECK(triangle.GetPerimeter() == 12);
    }

    BOOST_AUTO_TEST_CASE(has_a_area)
    {
        BOOST_CHECK(triangle.GetArea() == 3 * 4 *0.5);
    }


    BOOST_AUTO_TEST_CASE(get_vertex)
    {
        IsPointsEqual(triangle.GetVertex1(), { 0, 0 });
        IsPointsEqual(triangle.GetVertex2(), { 0, 3 });
        IsPointsEqual(triangle.GetVertex3(), { 4, 3 });
    }


    BOOST_AUTO_TEST_CASE(to_string)
    {
        BOOST_CHECK(triangle.ToString() == "Triangle:   S = 6  P = 12");
    }

BOOST_AUTO_TEST_SUITE_END()

