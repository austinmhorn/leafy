//
//  SmartMouse.cpp
//  leafy
//
//  Created by Austin Horn on 1/29/23.
//  Copyright © 2023 Austin Horn. All rights reserved.
//

#include <leafy/SmartMouse.hpp>
#include <leafy/Engine/Resources.hpp>

namespace leafy
{

const void SmartMouse::init()
{
    // Only cross-platform cursor types are loaded & defined by default
    Arrow.loadFromSystem(sf::Cursor::Type::Arrow);
    Text.loadFromSystem(sf::Cursor::Type::Text);
    Hand.loadFromSystem(sf::Cursor::Type::Hand);
    Cross.loadFromSystem(sf::Cursor::Type::Cross);
    NotAllowed.loadFromSystem(sf::Cursor::Type::NotAllowed);
}

SmartMouse::SmartMouse()
    : m_window(nullptr)
    , m_held(nullptr)
    , m_position()
    , m_lmb_released(false)
    , m_rmb_released(false)
{
    init();
}
SmartMouse::~SmartMouse()
{
    m_window = nullptr;
    m_held = nullptr;
}
void SmartMouse::create(sf::RenderWindow* window, Pointer pointer)
{
    setPointer(pointer);
    assignWindow(window);
    assignCursorToWindow();
}
void SmartMouse::setPointer(Pointer pointer)
{
    m_pointer = pointer;
    
    if (m_window)
        assignCursorToWindow();
}
void SmartMouse::assignWindow(sf::RenderWindow* window)
{
    m_window = window;
}
void SmartMouse::assignCursorToWindow()
{
    switch (m_pointer)
    {
        case Pointer::Arrow:      
            Arrow.loadFromSystem(sf::Cursor::Type::Arrow);
            m_window->setMouseCursor(Arrow);      
            break;
        case Pointer::Text:       
            Text.loadFromSystem(sf::Cursor::Type::Text);
            m_window->setMouseCursor(Text);       
            break;
        case Pointer::Hand:      
            Hand.loadFromSystem(sf::Cursor::Type::Hand);
            m_window->setMouseCursor(Hand);      
            break;
        case Pointer::Cross:       
            Cross.loadFromSystem(sf::Cursor::Type::Cross);
            m_window->setMouseCursor(Cross);       
            break;
        case Pointer::NotAllowed:       
            NotAllowed.loadFromSystem(sf::Cursor::Type::NotAllowed);
            m_window->setMouseCursor(NotAllowed);       
            break;
        default:
            break;
    }
}
const bool& SmartMouse::getLmbReleased() const
{
    return m_lmb_released;
}
const bool& SmartMouse::getRmbReleased() const
{
    return m_rmb_released;
}
void SmartMouse::reset()
{
    m_lmb_released = false;
    m_rmb_released = false;
}
void SmartMouse::handleEvent(sf::Event event)
{
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Button::Left)
    {
        m_lmb_released = false;
    }
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Button::Right)
    {
        m_rmb_released = false;
    }
    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Button::Left)
    {
        m_lmb_released = true;
    }
    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Button::Right)
    {
        m_rmb_released = true;
    }
}

}