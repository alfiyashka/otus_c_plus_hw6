#include "Point.hpp"

bool Point::operator == (const Point& point) const
{
    return m_x == point.m_x && m_y == point.m_y;
}

bool Point::operator < (const Point& point) const
{
    if (m_x < point.m_x)
    {
        return true;
    }
    else if (m_x == point.m_x && m_y < point.m_y)
    {
        return true;
    }
    return false;
}