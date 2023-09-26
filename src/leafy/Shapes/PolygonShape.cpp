//
//  PolygonShape.cpp
//  leafy
//
//  Copyright © 2023 Austin Horn. All rights reserved.
//

#include <leafy/Shapes/PolygonShape.hpp>

#include <cmath>

#ifndef _PI
#define _PI 3.14159265358979323846
#endif

namespace sf
{
    PolygonShape::PolygonShape(const sf::Vector2f& radius, float pointCount)
        : m_radius(radius)
        , m_pointCount(pointCount)
    {
        Shape::update();
    }
    void PolygonShape::setRadius(const sf::Vector2f& radius)
    {
        m_radius = radius;
        Shape::update();
    }
    void PolygonShape::setPointCount(float pointCount)
    {
        m_pointCount = pointCount;
        Shape::update();
    }
    const sf::Vector2f& PolygonShape::getRadius() const
    {
        return m_radius;
    }
    std::size_t PolygonShape::getPointCount() const
    {
        return m_pointCount;
    }
    sf::Vector2f PolygonShape::getPoint(std::size_t index) const
    {
        float angle = index * 2 * _PI / getPointCount() - _PI / 2;
        float x = std::cos(angle) * m_radius.x;
        float y = std::sin(angle) * m_radius.y;
        return sf::Vector2f(m_radius.x + x, m_radius.y + y);
    }
}
