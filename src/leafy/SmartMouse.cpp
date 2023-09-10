//
//  SmartMouse.cpp
//  Textbox
//
//  Created by Austin Horn on 1/29/23.
//  Copyright © 2023 Austin Horn. All rights reserved.
//

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <leafy/SmartMouse.hpp>

#include <leafy/Engine/Resources.hpp>

const void SmartMouse::init()
{
    sf::Image image;

    assert( image.loadFromFile( "examples/data/pointers/arrow.png" ) );
    assert( Arrow.loadFromPixels(image.getPixelsPtr(), image.getSize(), {0, 0}) );
    // Text
    assert( image.loadFromFile( "examples/data/pointers/text.png" ) );
    assert( Text.loadFromPixels(image.getPixelsPtr(), image.getSize(), {image.getSize().x/2, image.getSize().y/2}) );
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
        case Pointer::Arrow:      m_window->setMouseCursor(Arrow);      break;
        case Pointer::Text:       m_window->setMouseCursor(Text);       break;
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
