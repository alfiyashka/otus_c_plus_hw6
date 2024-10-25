#ifndef __MATRIX_ELEMENT_HPP__
#define __MATRIX_ELEMENT_HPP__

#include <unordered_map>
#include <tuple>

#include "Point.hpp"
#include "MatrixValueType.hpp"
#include "memory"


template <typename T, T defaultValue = 0>
class Matrix
{
public:
    using elementsMap_t = std::unordered_map<Point, MatrixValueType<T>, PointHash>;
    
    template <typename U>
    class MatrixRow
    {
    private:
        friend class Matrix;
        const int m_row;
        Matrix* m_parent;
    public:
        MatrixRow(Matrix* matrix, const int row): m_parent(matrix), m_row(row)
        {
        }

        U& operator[](int y)
        {
            const Point point(m_row, y);
            return m_parent->getValue(point);
        }
    };

    Matrix():m_map(new elementsMap_t()), m_row(0), m_lastElementIter(m_map->end())
    {
    }

    MatrixRow<T> operator[](int x)
    {
        return MatrixRow<T>(this, x);
    }

    Matrix& operator=(const T& x)
    {
        return *this;
    }

    T& insertDefault(const Point& point)
    {
        m_map->insert(typename elementsMap_t::value_type(point, MatrixValueType<T>(point, defaultValue)));
        m_lastElementIter = m_map->find(point);
        return m_lastElementIter->second.m_value;
    }

    bool lastValueIsDefault() const 
    {
        return m_lastElementIter != m_map->end() 
           && m_lastElementIter->second.m_value == defaultValue;
    }

    int size() const
    {
        if (lastValueIsDefault())
        {
            return m_map->size() - 1;
        }
        return m_map->size();
    }


    void clearUnusedDefaultInsertedBefore()
    {
        if (lastValueIsDefault())
        {
            m_map->erase(m_lastElementIter->first);
            m_lastElementIter = m_map->end();
        }
    }

    T& getValue(const Point& point)
    {
        clearUnusedDefaultInsertedBefore();
        auto findIter = m_map->find(point);
        if (findIter == m_map->end())
        {
            return insertDefault(point);
        }
        return findIter->second.m_value;
    }

    struct MatrixIterator
    {
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = elementsMap_t::value_type::second_type;
        using pointer = elementsMap_t::value_type::second_type *;
        using reference = elementsMap_t::value_type::second_type &;

        MatrixIterator(elementsMap_t* map) :
           m_map(map),
           m_mapIterator(m_map->begin()),
           m_defaultValue(defaultValue)
        {
            if (m_mapIterator == m_map->end())
            {
                m_ptr = nullptr;
                return;
            }
            else
            {
                while (m_mapIterator->second.m_value == m_defaultValue)
                {
                    m_mapIterator++;
                    if (m_mapIterator == m_map->end())
                    {
                        m_ptr = nullptr;
                        return;
                    }
                }
                m_ptr = &(m_mapIterator->second);
                return;
            }
        }
        MatrixIterator(): m_ptr(nullptr) {}

        reference operator*() const { return *m_ptr; }
        pointer operator->() { return m_ptr; }

        MatrixIterator &operator++(int ) = delete;

        MatrixIterator &operator++()
        {
            if (m_mapIterator == m_map->end())
            {
                m_ptr = nullptr;
                return *this;
            }
            else
            { 
                do
                {
                    m_mapIterator++;
                    if (m_mapIterator == m_map->end())
                    {
                        break;
                    }
                } while (m_mapIterator->second.m_value == m_defaultValue);
                
                if (m_mapIterator != m_map->end())
                {
                    m_ptr = &(m_mapIterator->second);
                    return *this;
                }                
                m_ptr = nullptr;
                return *this;
            }
        }

        friend bool operator==(const MatrixIterator &a, const MatrixIterator &b) 
        { 
            return a.m_ptr == b.m_ptr;
        }

        friend bool operator!=(const MatrixIterator &a, const MatrixIterator &b)
        { 
            auto res = a.m_ptr != b.m_ptr; 
            return res;
        }
    private:
        elementsMap_t* m_map;
        elementsMap_t::iterator m_mapIterator;

        elementsMap_t::value_type::second_type* m_ptr;

        int m_defaultValue;
    };

    using Iterator = MatrixIterator;


    Iterator begin() const
	{
		if (this->m_map->empty())
        {
            return Iterator();
        }
		return Iterator(m_map.get());
	}
 
	Iterator end() const
	{
		return Iterator();
    }

    void printMatrix(const Point& start, const Point& end) const
    {
        if (start.m_x > end.m_x || start.m_y > end.m_y)
        {
            throw std::runtime_error("incorrect interval");
        }
        std::cout << "Y"<< "    ";
        for (int y = start.m_y; y <= end.m_y; y++)
        {
            std::cout << y << " ";
        }
        std::cout<<std::endl;
        for (int x = start.m_x; x <= end.m_x; x++)
        {
            std::cout << "X-" << x << "  ";
            for (int y = start.m_y; y <= end.m_y; y++)
            {
                const Point point(x,y);
                auto find = m_map->find(point);
                if (find == m_map->end())
                {
                    std::cout<<defaultValue << " ";
                }
                else
                {
                    std::cout<<find->second.m_value << " ";
                }
            }
            std::cout<<std::endl;
        }

    }

    void printOnlyUsed() const
    {
        for (auto element : *this)
        {
            int x,y,z;
            std::tie(x,y,z) = element;
            std::cout<< "[" << x << ", "<< y << "]" << " = "<< z <<std::endl;
        }
    }
private:
    std::shared_ptr<elementsMap_t> m_map;
    elementsMap_t::iterator m_lastElementIter;
   
    int m_row;
};




#endif