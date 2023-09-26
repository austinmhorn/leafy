//
//  UIElement.cpp
//  leafy
//
//  Created by Austin Horn on 1/29/23.
//  Copyright © 2023 Austin Horn. All rights reserved.
//

#include <leafy/UIElement.hpp>

void UIElement::update(sf::Time delta_time)
{
}

void UIElement::refreshBase(sf::RenderWindow& window, sf::Event event)
{
    const sf::Vector2f mouse_move = window.mapPixelToCoords({event.mouseMove.x, event.mouseMove.y});
    const sf::Vector2f mouse_btn = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});

    if ( event.type == sf::Event::EventType::MouseMoved )
        handleMouseMoveEvent(mouse_move);
    else if ( event.type == sf::Event::EventType::MouseButtonPressed )
        handleMouseButtonPressedEvent(mouse_btn);
    else if ( event.type == sf::Event::EventType::MouseButtonReleased )
        handleMouseButtonReleasedEvent(mouse_btn);
}

void UIElement::setPosition(const sf::Vector2f& position)
{
    m_position = position;
}
const sf::Vector2f& UIElement::getPosition() const
{
    return m_position;
}
void UIElement::setSize(const sf::Vector2f& size)
{
    m_size = size;
}
const sf::Vector2f& UIElement::getSize() const
{
    return m_size;
}

void UIElement::setRadius(float radius)
{
    m_size = sf::Vector2f(radius, radius);
}
void UIElement::setPolygonRadius(const sf::Vector2f& radius)
{   
    m_size = radius;
}
float UIElement::getRadius() const
{
    return m_size.x;
}
const sf::Vector2f& UIElement::getPolygonRadius() const
{
    return m_size;
}
bool UIElement::clicked() const
{
    return m_clicked;
}
void UIElement::reset()
{
    m_clicked = false;
}
void UIElement::handleMouseMoveEvent(const sf::Vector2f& mousePosition)
{
    if ( contains( mousePosition ) )
    {
        if ( !m_mouseOver )
        {
            m_mouseOver = true;
            m_needsUpdate = true;
        }
    }
    else
    {
        if ( m_mouseOver )
        {
            m_mouseOver = false;
            m_needsUpdate = true;
        }
    }

    if ( m_needsUpdate )
    {
        m_needsUpdate = false;
        (m_mouseOver) ?  mouseEnter() : mouseLeave();
    }
}

void UIElement::handleMouseButtonPressedEvent(const sf::Vector2f& mouseButtonPressedPosition)
{
    m_clickPressInBounds = contains(mouseButtonPressedPosition);
}

void UIElement::handleMouseButtonReleasedEvent(const sf::Vector2f& mouseButtonReleasedPosition)
{
    if ( m_mouseOver && m_clickPressInBounds && contains(mouseButtonReleasedPosition) ) 
        m_clicked = !m_clicked;
    else
        m_clicked = false;

    // Allows for only processing a click event if the press originated within bounds of the button
    if ( m_clickPressInBounds && m_mouseOver )
        mouseClick();
}