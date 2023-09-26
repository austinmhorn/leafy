//
//  StadiumShape.cpp
//  leafy
//
//  Created by Austin Horn on 12/1/22.
//  Copyright © 2022 Austin Horn. All rights reserved.
//

#include <leafy/Shapes/StadiumShape.hpp>

#include <cmath>

#ifndef _PI
#define _PI 3.14159265358979323846
#endif

sf::StadiumShape::StadiumShape(const sf::Vector2f& size, float cornerRadius) 
    : m_size( size )
    , m_cornerRadius( cornerRadius )
    , m_antialiasing( 8 )
{
    update();
}

void sf::StadiumShape::update()
{
    Shape::update();
}

void sf::StadiumShape::setSize(const sf::Vector2f& size)
{
    m_size = size;
    m_cornerRadius = size.y/2.f;
    update();
}

void sf::StadiumShape::setCornersRadius(float cornerRadius)
{
    m_cornerRadius = cornerRadius;
    update();
}

void sf::StadiumShape::setAntialiasing(unsigned int antialiasing)
{
    m_antialiasing = antialiasing;
    update();
}

const sf::Vector2f& sf::StadiumShape::getSize() const
{
    return m_size;
}

float sf::StadiumShape::getCornersRadius() const
{
    return m_cornerRadius;
}

unsigned int sf::StadiumShape::getAntialiasing() const
{
    return m_antialiasing;
}

std::size_t sf::StadiumShape::getPointCount() const
{
    return m_antialiasing * 4;
}

sf::Vector2f sf::StadiumShape::getPoint(std::size_t index) const
{
    if(index >= m_antialiasing*4)
        return sf::Vector2f(0,0);

    float delta_angle = 90.f / (m_antialiasing-1);
    sf::Vector2f center;
    unsigned int center_index = static_cast<unsigned int>(index)/m_antialiasing;
    
    switch(center_index) 
    {
        case 0: center.x = m_size.x - m_cornerRadius;
                center.y = m_cornerRadius;
            break;
        case 1: center.x = m_cornerRadius;
                center.y = m_cornerRadius;
            break;
        case 2: center.x = m_cornerRadius;
                center.y = m_size.y - m_cornerRadius;
            break;
        case 3: center.x = m_size.x - m_cornerRadius;
                center.y = m_size.y - m_cornerRadius;
            break;
    }

    return sf::Vector2f(m_cornerRadius * std::cos(delta_angle * (index - center_index) * _PI / 180.0f) + center.x,
                       -m_cornerRadius * std::sin(delta_angle * (index - center_index) * _PI / 180.0f) + center.y);
}

