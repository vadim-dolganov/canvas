#include "stdafx.h"
#include "PointTest.h"

void IsPointsEqual(const Point &point1, const Point &point2)
{
    BOOST_CHECK(point1.x == point2.x);
    BOOST_CHECK(point1.y == point2.y);
}

struct PointFixture_
{
    Point point;
    PointFixture_()
        :point({ 10.2f, 23.4f })
    {}
};

BOOST_FIXTURE_TEST_SUITE(PointFixture, PointFixture_)
    BOOST_AUTO_TEST_CASE(can_return_point)
    {
        Point referencePoint = { 10.2f, 23.4f };
        IsPointsEqual(point, referencePoint);
    }
BOOST_AUTO_TEST_SUITE_END()