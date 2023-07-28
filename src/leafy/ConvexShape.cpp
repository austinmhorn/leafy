//
//  ConvexShape.cpp
//  Leafly
//
//  Created by Austin Horn on 1/29/23.
//  Copyright © 2023 Austin Horn. All rights reserved.
//

#include <leafy/ConvexShape.hpp>

#include <cmath>

#ifndef _PI
#define _PI 3.14159265358979323846
#endif

namespace sf
{
    ConvexShape::ConvexShape(const sf::Vector2f& radius, float pointCount)
        : m_radius(radius)
        , m_pointCount(pointCount)
    {
        Shape::update();
    }
    void ConvexShape::setRadius(const sf::Vector2f& radius)
    {
        m_radius = radius;
        Shape::update();
    }
    void ConvexShape::setPointCount(float pointCount)
    {
        m_pointCount = pointCount;
        Shape::update();
    }
    const sf::Vector2f& ConvexShape::getRadius() const
    {
        return m_radius;
    }
    std::size_t ConvexShape::getPointCount() const
    {
        return m_pointCount;
    }
    sf::Vector2f ConvexShape::getPoint(std::size_t index) const
    {
        float angle = index * 2 * _PI / getPointCount() - _PI / 2;
        float x = std::cos(angle) * m_radius.x;
        float y = std::sin(angle) * m_radius.y;
        return sf::Vector2f(m_radius.x + x, m_radius.y + y);
    }
}
