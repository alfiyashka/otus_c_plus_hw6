#ifndef _MATRIX_VALUE_TYPE_HPP
#define _MATRIX_VALUE_TYPE_HPP

#include "Point.hpp"

#include <tuple>

template <typename U>
struct MatrixValueType: std::tuple<const int&, const int&, const U&>
{
    Point m_point;
    U m_value;
    MatrixValueType(const Point& point, const U& value):
        m_point(point),
        m_value(value),
        std::tuple<const int&, const int&, const U&>{std::tie(m_point.m_x, m_point.m_y, m_value)}
    {}
        
    MatrixValueType(const MatrixValueType& r):m_point(r.m_point),
        m_value(r.m_value),
        std::tuple<const int&, const int&, const U&>{std::tie(m_point.m_x, m_point.m_y, m_value)}
    {}

    MatrixValueType &operator=(const MatrixValueType &r)
    {
        if (this = &r)
        {
            return *this;
        }
        this->m_value = r.m_value;
        this->m_point = r.m_point;
        return *this;
    }
};

#endif