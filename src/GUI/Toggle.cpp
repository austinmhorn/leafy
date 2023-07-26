//
//  Toggle.cpp
//  War
//
//  Created by Austin Horn on 12/2/22.
//  Copyright © 2022 Austin Horn. All rights reserved.
//

#include "Toggle.hpp"
#include "../Core/Resources.hpp"

#include <iostream>

Toggle::Toggle(bool on, sf::Vector2f size)
    : m_shape(size.y/2.f)
    , m_slider{ (size.y-5.f)/2.f, 30 }
    , m_status{ (on)?"ON":"OFF", Resources::Sansation, 12}
    , m_text{"- \"Description\"", Resources::Sansation, 12}
    , m_side(Right)
    , m_on(on)
    , m_size(size)
    , m_clicked(false)
{
    init();
}

Toggle::Toggle(Toggle& toggle)
{
    m_shape = toggle.m_shape;
    m_slider = toggle.m_slider;
    m_status = toggle.m_status;
    m_on = toggle.m_on;
    m_text = toggle.m_text;
    m_side = toggle.m_side;
}

Toggle::Toggle(const Toggle& toggle)
{
    m_shape = toggle.m_shape;
    m_slider = toggle.m_slider;
    m_status = toggle.m_status;
    m_on = toggle.m_on;
    m_text = toggle.m_text;
    m_side = toggle.m_side;
}

Toggle& Toggle::operator=(const Toggle &toggle)
{
    if (this != &toggle) {
        m_shape = toggle.m_shape;
        m_slider = toggle.m_slider;
        m_status = toggle.m_status;
        m_on = toggle.m_on;
        m_text = toggle.m_text;
        m_side = toggle.m_side;
    }
    return *this;
}

void Toggle::init()
{
    if (m_on) {
        m_slider.setPosition(m_shape.getPosition().x+m_size.x-2.5f,m_shape.getPosition().y+2.5f);
        m_status.setPosition(2.5f, 2.5f);
        m_shape.setFillColor(Resources::LightGreen);
    }
    else {
        m_slider.setPosition(2.5f, 2.5f);
        m_status.setPosition((m_size.x/2.f)+3.f, (m_size.y/2.f)-(m_status.getGlobalBounds().height/2.f)-3.f);
        m_shape.setFillColor(Resources::Gray);
    }
    
    m_shape.setSize(m_size);
    m_shape.setOutlineColor(sf::Color::White);
    m_shape.setOutlineThickness(2.f);
    m_shape.setPosition(0.f, 0.f);
    
    m_slider.setFillColor(sf::Color::White);
    
    m_status.setFillColor(sf::Color::White);

    setPosition(0.0f, 0.0f);
}

void Toggle::setPosition(const sf::Vector2f& pos)
{
    m_shape.setPosition(pos);
    
    adjustSliderPosition();
    
    adjustStatusPosition();
    
    setTextSide(m_side);
}

void Toggle::setPosition(float x, float y)
{
    m_shape.setPosition(x, y);
    
    (m_on) ? m_slider.setPosition(x+m_size.x-(m_slider.getRadius()*2)-2.5f, y+2.5f)
           : m_slider.setPosition(x+2.5f, y+2.5f);
    
    (m_on) ? m_status.setPosition(x+(m_status.getGlobalBounds().height/2.f)+8.f, y+(m_status.getGlobalBounds().height/2.f)+8.f)
           : m_status.setPosition(x+(m_size.x/2.f)+3.f, y+(m_size.y/2.f)-(m_status.getGlobalBounds().height/2.f)-3.f);
    
    setTextSide(m_side);
}

void Toggle::setDescription(const std::string& string)
{
    m_text.setString(string);
}

void Toggle::setTextSide(Side side)
{
    sf::Vector2f center = {m_shape.getPosition().x + (getExactSize().x/2.f), m_shape.getPosition().y + (getExactSize().y/2.f)};
        
    switch (side) {
        case Top: break;
        case Bottom: break;
        case Left: break;
        case Right:
            m_text.setPosition({center.x+(getExactSize().x/2.f)+5.0f, m_status.getPosition().y});
            break;
        case TopLeft: break;
        case TopRight: break;
        case BottomLeft: break;
        case BottomRight: break;
    }
    
}

sf::Vector2f Toggle::getApproxSize() const
{
    return {std::round(getTransform().transformRect(m_shape.getGlobalBounds()).width - (m_shape.getOutlineThickness()*2.f)),
            std::round(getTransform().transformRect(m_shape.getGlobalBounds()).height - (m_shape.getOutlineThickness()*2.f))};
}

sf::Vector2f Toggle::getExactSize() const
{
    return {getTransform().transformRect(m_shape.getGlobalBounds()).width,
            getTransform().transformRect(m_shape.getGlobalBounds()).height};
}

const bool& Toggle::isOn() const
{
    return m_on;
}

const bool Toggle::contains(const sf::Vector2f& point) const
{
    return getTransform().transformRect(m_shape.getGlobalBounds()).contains(point);
}

void Toggle::mouseOver()
{
    m_slider.setFillColor({m_slider.getFillColor().r, m_slider.getFillColor().g, m_slider.getFillColor().b, 150});
}

void Toggle::mouseLeave()
{
    m_slider.setFillColor({m_slider.getFillColor().r, m_slider.getFillColor().g, m_slider.getFillColor().b, 255});
}

void Toggle::handleMouseButtonPressedEvent(sf::RenderWindow& window, sf::Event event)
{
    sf::Time delta_time;
    animate(delta_time);
    setClicked(!getClicked());
}
void Toggle::handleMouseButtonReleasedEvent(sf::RenderWindow& window, sf::Event event)
{
    sf::Vector2f mouse_pos = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
    
    if (contains(mouse_pos))
    {
        switch (event.mouseButton.button)
        {
            case sf::Mouse::Left:
                handleMouseButtonPressedEvent(window, event);
                break;
                
            case sf::Mouse::Right:
                break;
                
            default:
                break;
        }
    }
}
void Toggle::handleMouseMoveEvent(sf::RenderWindow& window, sf::Event event)
{
    sf::Vector2f mouse_pos = window.mapPixelToCoords({event.mouseMove.x, event.mouseMove.y});
    
    (contains(mouse_pos)) ? mouseOver() : mouseLeave();
}
void Toggle::handleEvent(sf::RenderWindow& window, sf::Event event)
{
    switch (event.type)
    {
        case sf::Event::MouseButtonPressed:
            handleMouseButtonPressedEvent(window, event);
            break;
            
        case sf::Event::MouseButtonReleased:
            handleMouseButtonReleasedEvent(window, event);
            break;
            
        case sf::Event::MouseMoved:
            handleMouseMoveEvent(window, event);
            break;
            
        default:
            break;
    }
}

void Toggle::update(sf::Time delta_time)
{
    
}



void Toggle::animate(sf::Time& delta_time)
{
    sf::Time curr_time = sf::seconds(0.f);
    sf::Time total_time = sf::seconds(0.f);
    float x_start = m_shape.getPosition().x + 2.5f;
    float x_final = m_shape.getPosition().x + m_size.x - (m_slider.getRadius()*2) - 2.5f;
    float delta_x = (x_final-x_start)/10.f;
    
    sf::Clock clock;
    clock.restart();
    
    while (total_time < sf::seconds(1.f))
    {
        curr_time += clock.getElapsedTime();
        
        if (curr_time.asSeconds() >= 0.1f) {
            
            (m_on) ? animateOff(delta_x) : animateOn(delta_x);
            
            total_time += curr_time;
            curr_time = clock.restart();
        }
    }
    
    m_on = !m_on;
    
    // Recolor background stadium shape in correspondence with current status
    (m_on) ? m_shape.setFillColor(Resources::LightGreen) : m_shape.setFillColor(Resources::Gray);
    (m_on) ? m_status.setString("ON") : m_status.setString("OFF");
    
    adjustStatusPosition();
}

void Toggle::setClicked(bool clicked)
{
    m_clicked = clicked;
}
const bool& Toggle::getClicked() const
{
    return m_clicked;
}

void Toggle::adjustSliderPosition()
{
    auto pos = m_shape.getPosition();
    float padding = 2.5f;
    
    (m_on) ? m_slider.setPosition(pos.x+m_size.x-(m_slider.getRadius()*2)-padding, pos.y+padding)
           : m_slider.setPosition(pos.x+padding, pos.y+padding);
}

void Toggle::adjustStatusPosition()
{
    auto pos = m_shape.getPosition();
    float padding = 3.0f;
    
    (m_on) ? m_status.setPosition(pos.x+(m_status.getGlobalBounds().height/2.f)+8.f, pos.y+(m_status.getGlobalBounds().height/2.f)+8.f)
           : m_status.setPosition(pos.x+(m_size.x/2.f)+padding, pos.y+(m_size.y/2.f)-(m_status.getGlobalBounds().height/2.f)-padding);
}

void Toggle::animateOn(float delta_x) {
    m_slider.move(delta_x, 0.f);
}

void Toggle::animateOff(float delta_x) {
    m_slider.move(-delta_x, 0.f);
}

void Toggle::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(m_shape, states);
    target.draw(m_status, states);
    target.draw(m_slider, states);
    target.draw(m_text, states);
}
