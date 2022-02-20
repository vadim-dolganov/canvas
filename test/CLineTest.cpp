#include "stdafx.h"
#include "PointTest.h"
#include "../shape/LineSegment.h"

struct LineFixture_
{
    CLineSegment line;
    LineFixture_()
        :line({ 10, 20 }, { 15, 20 }, { 100, 100, 20 })
    {}
};

BOOST_FIXTURE_TEST_SUITE(Line, LineFixture_)
    BOOST_AUTO_TEST_CASE(has_zero_area)
    {
        BOOST_CHECK(line.GetArea() == 0);
    }

    BOOST_AUTO_TEST_CASE(has_a_perimeter)
    {
        BOOST_CHECK(line.GetPerimeter() == 5);
    }

    BOOST_AUTO_TEST_CASE(get_start_point)
    {
        IsPointsEqual(line.GetStartPoint(), { 10, 20 });
    }

    BOOST_AUTO_TEST_CASE(get_end_point)
    {
        IsPointsEqual(line.GetEndPoint(), { 15, 20 });
    }

    BOOST_AUTO_TEST_CASE(to_string)
    {
        BOOST_CHECK(line.ToString() == "Line:   S = 0  P = 5");
    }
BOOST_AUTO_TEST_SUITE_END()

