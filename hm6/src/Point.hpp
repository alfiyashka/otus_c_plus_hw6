#ifndef _POINT_HPP
#define _POINT_HPP

#include <stddef.h>

struct Point
{
    int m_x;
    int m_y;
    Point(const int x, const int y): m_x(x), m_y(y) 
    {
    }
    Point(): m_x(0), m_y(0) 
    {
    }
    Point(const Point& p): m_x(p.m_x), m_y(p.m_y) 
    {
    }
    bool operator == (const Point& point) const;
    bool operator < (const Point& point) const;
};


struct PointHash 
{
    size_t operator()(const Point& p) const noexcept
    {
        return static_cast<size_t>(p.m_x + p.m_y);
    }    
};


#endif