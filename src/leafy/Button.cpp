//
//  Button.cpp
//  Leafly
//
//  Created by Austin Horn on 1/29/23.
//  Copyright © 2023 Austin Horn. All rights reserved.
//

#include <leafy/Button.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <cassert>

#ifndef _PI
#define _PI 3.14159265358979323846
#endif
#include <iostream>

template <> /// Explicit Button sf::StadiumShape Button() Instantioation
Button<sf::StadiumShape>::Button(const sf::StadiumShape& shape)
    : m_shape(nullptr)
    , m_clicked(false)
{
    m_shape = new sf::StadiumShape(shape);
}
template <> /// Explicit Button sf::StadiumShape ~Button() Instantiation
Button<sf::StadiumShape>::~Button()
{
    if (m_shape)
        delete m_shape;
}
template <>
void Button<sf::StadiumShape>::handleEvent(sf::RenderWindow &window, sf::Event event)
{
    sf::Vector2f mouse_move = window.mapPixelToCoords({event.mouseMove.x, event.mouseMove.y});;
    sf::Vector2f mouse_btn = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});;
    
    switch (event.type)
    {
        case sf::Event::MouseMoved:
            
            contains(mouse_move) ? mouseOver() : mouseLeave();
            
            break;
        case sf::Event::MouseButtonReleased:
                        
            if (contains(mouse_btn))
            {
                std::cout << "clicked" << std::endl;
                m_clicked = !m_clicked;
            }
            
            break;
            
        default:
            break;
    }
}
template <typename T>
Button<T>::Button(const T& shape)
    : m_shape(new T(shape))
    , m_clicked(false)
{
}
template <typename T>
Button<T>::~Button()
{
    if (m_shape)
        delete m_shape;
}
template <typename T>
bool Button<T>::clicked() const
{
    return m_clicked;
}
template <typename T>
bool Button<T>::contains(sf::Vector2f point) const
{
    return m_shape->getGlobalBounds().contains(point);
}
template <typename T>
void Button<T>::mouseOver()
{
    m_shape->setFillColor({m_shape->getFillColor().r, m_shape->getFillColor().g, m_shape->getFillColor().b, 100});
}
template <typename T>
void Button<T>::mouseLeave()
{
    m_shape->setFillColor({m_shape->getFillColor().r, m_shape->getFillColor().g, m_shape->getFillColor().b, 255});
}
template <typename T>
void Button<T>::handleEvent(sf::RenderWindow &window, sf::Event event)
{
    sf::Vector2f mouse_move = window.mapPixelToCoords({event.mouseMove.x, event.mouseMove.y});
    sf::Vector2f mouse_btn = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
    
    switch (event.type)
    {
        case sf::Event::MouseMoved:
            
            contains(mouse_move) ? mouseOver() : mouseLeave();
            
            break;
        case sf::Event::MouseButtonReleased:
                        
            if (contains(mouse_btn))
            {
                std::cout << "clicked" << std::endl;
                m_clicked = !m_clicked;
            }
            
            break;
            
        default:
            break;
    }
}
template <typename T>
void Button<T>::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    
    states.texture = m_shape->getTexture();
    
    target.draw(*m_shape, states);
}
