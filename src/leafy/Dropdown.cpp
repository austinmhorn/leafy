//
//  Dropdown.cpp
//  leafy
//
//  Created by Austin Horn on 12/2/22.
//  Copyright © 2022 Austin Horn. All rights reserved.
//

#include <leafy/Dropdown.hpp>
#include <leafy/Engine/Resources.hpp>

#include <iostream>
#include <cmath>

Dropdown::Dropdown(const sf::Vector2f &size)
    : m_rect(size)
    , m_open(false)
{
    init();
}
void Dropdown::init()
{
    m_rect.setFillColor({72, 72, 72});
    m_rect.setOutlineColor(sf::Color::White);
    m_rect.setOutlineThickness(1.f);

    m_triangle = sf::VertexArray(sf::Triangles, 3);

    m_triangle[0].color = sf::Color::White;
    m_triangle[1].color = sf::Color::White;
    m_triangle[2].color = sf::Color::White;

    updateGeometry();
}
void Dropdown::updateGeometry()
{
    flipTriangle();
}
void Dropdown::flipTriangle()
{
    auto rpos = m_rect.getPosition();
    auto rsz = m_rect.getSize();

    if (m_open)
    {
        m_triangle[0].position = {rpos.x + rsz.x - rsz.y, rpos.y + rsz.y - 5.f};
        m_triangle[1].position = {rpos.x + rsz.x - 5.f, rpos.y + rsz.y - 5.f};

        float dist = m_triangle[1].position.x - m_triangle[0].position.x;

        m_triangle[2].position = {rpos.x + rsz.x - dist/2.f - 5.f, rpos.y + 5.f};
    }
    else
    {
        m_triangle[0].position = {rpos.x + rsz.x - rsz.y, rpos.y + 5.f};
        m_triangle[1].position = {rpos.x + rsz.x - 5.f, rpos.y + 5.f};

        float dist = m_triangle[1].position.x - m_triangle[0].position.x;

        m_triangle[2].position = {rpos.x + rsz.x - dist/2.f - 5.f, rpos.y + rsz.y - 5.f};
    }
    
}
void Dropdown::setSize(const sf::Vector2f &size)
{
    m_rect.setSize(size);
    updateGeometry();
}
void  Dropdown::setPosition(const sf::Vector2f &position)
{
    m_rect.setPosition(position);
    updateGeometry();
}
const sf::Vector2f& Dropdown::getSize() const
{
    return m_rect.getSize();
}
const sf::Vector2f& Dropdown::getPosition() const
{
    return m_rect.getPosition();
}

bool Dropdown::contains(const sf::Vector2f& point) const 
{
    return m_rect.getGlobalBounds().contains(point);
}

void Dropdown::mouseEnter() 
{
    auto color = sf::Color(m_triangle[0].color.r, m_triangle[0].color.g, m_triangle[0].color.b, 150);

    m_triangle[0].color = color;
    m_triangle[1].color = color;
    m_triangle[2].color = color;
}

void Dropdown::mouseLeave() 
{
    auto color = sf::Color(m_triangle[0].color.r, m_triangle[0].color.g, m_triangle[0].color.b, 255);

    m_triangle[0].color = color;
    m_triangle[1].color = color;
    m_triangle[2].color = color;
}
void Dropdown::mouseClick() 
{
    
}

void Dropdown::handleMouseButtonReleasedEvent(const sf::Vector2f& mouseButtonReleasedPosition)
{
    if ( contains(mouseButtonReleasedPosition) )
    {
        m_open = !m_open;
        flipTriangle();
    }
    else
    {
        if ( m_open )
        {
            m_open = false;
            flipTriangle();     
        }
    }
}

void Dropdown::handleEvent(sf::RenderWindow& window, sf::Event event)
{
    const sf::Vector2f mouse_move = window.mapPixelToCoords({event.mouseMove.x, event.mouseMove.y});
    const sf::Vector2f mouse_btn = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});

    switch (event.type)
    {            
        case sf::Event::MouseMoved:
            refreshBase(window, event);
            break;

        case sf::Event::MouseButtonPressed:
            refreshBase(window, event);
            break;
            
        case sf::Event::MouseButtonReleased:
            refreshBase(window, event);
            break;
            
        default:
            break;
    }
}

void Dropdown::update(sf::Time delta_time) {

}

void Dropdown::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_rect);
    target.draw(m_triangle);
}
