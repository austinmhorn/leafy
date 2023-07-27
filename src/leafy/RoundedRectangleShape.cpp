//
//  RoundedRectangleShape.cpp
//  Leafly
//
//  Created by Austin Horn on 12/2/22.
//  Copyright © 2022 Austin Horn. All rights reserved.
//

#include <leafy/RoundedRectangleShape.hpp>

////////////////////////////////////////////////////////////
RoundedRectangleShape::RoundedRectangleShape(const sf::Vector2f& size, float radius, unsigned int cornerPointCount)
{
    m_size = size;
    m_radius = radius;
    m_cornerPointCount = cornerPointCount;
    Shape::update();
}

////////////////////////////////////////////////////////////
void RoundedRectangleShape::setSize(const sf::Vector2f& size)
{
    m_size = size;
    Shape::update();
}

////////////////////////////////////////////////////////////
void RoundedRectangleShape::setRadius(float radius)
{
    m_radius = radius;
    Shape::update();
}

////////////////////////////////////////////////////////////
void RoundedRectangleShape::setCornerPointCount(unsigned int count)
{
    m_cornerPointCount = count;
    Shape::update();
}

////////////////////////////////////////////////////////////
const sf::Vector2f& RoundedRectangleShape::getSize() const
{
    return m_size;
}

////////////////////////////////////////////////////////////
float RoundedRectangleShape::getRadius() const
{
    return m_radius;
}
unsigned int RoundedRectangleShape::getCornerPointCount()
{
    return m_cornerPointCount;
}

////////////////////////////////////////////////////////////
std::size_t RoundedRectangleShape::getPointCount() const
{
    return m_cornerPointCount*4;
}

////////////////////////////////////////////////////////////
sf::Vector2f RoundedRectangleShape::getPoint(std::size_t index) const
{
    if(index >= m_cornerPointCount*4)
        return sf::Vector2f(0,0);

    float deltaAngle = 90.0f/(m_cornerPointCount-1);
    sf::Vector2f center;
    unsigned int centerIndex = index/std::round(m_cornerPointCount);
    static const float pi = 3.141592654f;

    switch(centerIndex)
    {
        case 0: center.x = m_size.x - m_radius; center.y = m_radius; break;
        case 1: center.x = m_radius; center.y = m_radius; break;
        case 2: center.x = m_radius; center.y = m_size.y - m_radius; break;
        case 3: center.x = m_size.x - m_radius; center.y = m_size.y - m_radius; break;
    }

    return sf::Vector2f(m_radius*std::cos(deltaAngle*(index-centerIndex)*pi/180)+center.x,
                        -m_radius*std::sin(deltaAngle*(index-centerIndex)*pi/180)+center.y);
}
