//
//  UIElement.cpp
//  leafy
//
//  Created by Austin Horn on 1/29/23.
//  Copyright © 2023 Austin Horn. All rights reserved.
//

#include <leafy/UIElement.hpp>

namespace leafy
{

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
float UIElement::getRadius() const
{
    return m_size.x;
}
void UIElement::setPolygonRadius(const sf::Vector2f& radius)
{   
    m_size = radius;
}
const sf::Vector2f& UIElement::getPolygonRadius() const
{
    return m_size;
}

void UIElement::refreshBase(sf::RenderWindow& window, sf::Event event)
{
    const sf::Vector2f mouse_move = window.mapPixelToCoords({event.mouseMove.x, event.mouseMove.y});
    const sf::Vector2f mouse_btn = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
    m_mouseButton = event.mouseButton.button;

    switch (event.type)
    {
        case sf::Event::EventType::MouseMoved:
            handleMouseMoveEvent(mouse_move);
            break;
        case sf::Event::EventType::MouseButtonPressed:
            handleMouseButtonPressedEvent(mouse_btn);
            break;
        case sf::Event::EventType::MouseButtonReleased:
            handleMouseButtonReleasedEvent(mouse_btn);
            break;
        default:
            break;
    }   
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
        else return;
    }
    else
    {
        if ( m_mouseOver )
        {
            m_mouseOver = false;
            m_needsUpdate = true;
        }
        else return;
    }

    if ( m_needsUpdate )
    {
        m_needsUpdate = false;
        (m_mouseOver) ? mouseEnter() : mouseLeave();
    }
}

void UIElement::handleMouseButtonPressedEvent(const sf::Vector2f& mouseButtonPressedPosition)
{
    m_mouseButtonPressed = contains(mouseButtonPressedPosition);

    if ( m_mouseButtonPressed )
        pressed();
}

void UIElement::handleMouseButtonReleasedEvent(const sf::Vector2f& mouseButtonReleasedPosition)
{
    m_mouseButtonReleased = ( m_mouseOver  &&  m_mouseButtonPressed  &&  contains(mouseButtonReleasedPosition) );
    // Allows for only processing a click event if the press originated within bounds of the button
    if ( m_mouseButtonReleased )
    {
        clicked();
        m_active = !m_active;
    }     
}

}