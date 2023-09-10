//
//  Toggle.cpp
//  Leafly
//
//  Created by Austin Horn on 12/2/22.
//  Copyright © 2022 Austin Horn. All rights reserved.
//

#include <leafy/Toggle.hpp>
#include <leafy/Engine/Resources.hpp>

#include <iostream>
#include <cmath>

Toggle::Toggle(bool on, sf::Vector2f size)
    : m_shape(size.y/2.f)
    , m_slider{ (size.y-5.f)/2.f, 30 }
    , m_status{ (on)?"ON":"OFF", Resources::Sansation, static_cast<unsigned int>(std::floor(size.y/3.f))}
    , m_text{"- \"Description\"", Resources::Sansation, static_cast<unsigned int>(std::floor(size.y/3.f))}
    , m_side(Toggle::Top)
    , m_on(on)
    , m_size(size)
    , m_clicked(false)
    , m_velocity(0.f, 0.f)
    , m_velocityXMax(3.f*size.x)
    , m_acceleration(3.f*(size.x/80.f))
{
    init();
}

void Toggle::init()
{
    if (m_on) 
    {
        m_slider.setPosition(m_shape.getPosition().x+m_size.x-2.5f,m_shape.getPosition().y+2.5f);
        m_status.setPosition(2.5f, 2.5f);
        m_shape.setFillColor(Resources::LightGreen);
    }
    else 
    {
        m_slider.setPosition(2.5f, 2.5f);
        m_status.setPosition((m_size.x/2.f)+3.f, (m_size.y/2.f)-(m_status.getGlobalBounds().height/2.f)-3.f);
        m_shape.setFillColor(Resources::Gray);
    }
    
    m_shape.setOutlineColor(sf::Color::White);
    m_shape.setOutlineThickness(2.f);
    m_shape.setPosition(0.f, 0.f);
    
    m_slider.setFillColor(sf::Color::White);
    m_status.setFillColor(sf::Color::White);

    updateGeometry();
    updatePhysics();
    setPosition(0.0f, 0.0f);
}

void Toggle::setPosition(const sf::Vector2f& pos)
{
    m_shape.setPosition(pos);
    
    adjustSliderPosition();
    adjustStatusPosition();
    updateTextPosition();
}

void Toggle::setPosition(float x, float y)
{
    m_shape.setPosition(x, y);
    
    adjustSliderPosition();
    adjustStatusPosition();
    updateTextPosition();
}

void Toggle::setDescription(const std::string& string) {
    m_text.setString(string);
    updateTextPosition();
}

void Toggle::setTextSide(Side side) {
    m_side = side;
    updateTextPosition();
}

void Toggle::setSize(const sf::Vector2f& size) {
    m_size = size;

    updateGeometry();
    updatePhysics();
    updateTextPosition();
}
void Toggle::setClicked(bool clicked) {
    m_clicked = clicked;
}
const sf::Vector2f& Toggle::getPosition() const {
    return m_shape.getPosition();
}
sf::Text& Toggle::getDescription() {
    return m_text;
}
const sf::Vector2f& Toggle::getSize() const {
    return m_size;
}
const bool Toggle::isOn() const {
    return m_on;
}
bool Toggle::clicked() const {
    return m_clicked;
}

bool Toggle::contains(sf::Vector2f point) const {
    return getTransform().transformRect(m_shape.getGlobalBounds()).contains(point);
}

void Toggle::mouseOver() {
    m_slider.setFillColor({m_slider.getFillColor().r, m_slider.getFillColor().g, m_slider.getFillColor().b, 150});
}

void Toggle::mouseLeave() {
    m_slider.setFillColor({m_slider.getFillColor().r, m_slider.getFillColor().g, m_slider.getFillColor().b, 255});
}

void Toggle::handleMouseButtonPressedEvent(sf::RenderWindow& window, sf::Event event) {
}

void Toggle::handleMouseButtonReleasedEvent(sf::RenderWindow& window, sf::Event event)
{
    sf::Vector2f mouse_btn = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});

    if (contains(mouse_btn))
    {
        switch (event.mouseButton.button)
        {
            case sf::Mouse::Left:
                setClicked(true);
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
    sf::Vector2f mouse_move = window.mapPixelToCoords({event.mouseMove.x, event.mouseMove.y});

    switch (event.type)
    {            
        case sf::Event::MouseMoved:
            handleMouseMoveEvent(window, event);
            break;

        case sf::Event::MouseButtonPressed:
            handleMouseButtonPressedEvent(window, event);
            break;
            
        case sf::Event::MouseButtonReleased:
            handleMouseButtonReleasedEvent(window, event);
            break;
            
        default:
            break;
    }
}

void Toggle::update(sf::Time delta_time) {
    if ( clicked() )
        animate(delta_time);  
}

void Toggle::animate(sf::Time& delta_time)
{
    float r_dest = m_shape.getPosition().x + m_size.x - (m_slider.getRadius()*2) - 2.5f;
    float l_dest = m_shape.getPosition().x + 2.5f;

    if ( isOn() )
    {
        m_velocity.x += -1.f * m_acceleration;

        animateOff(m_velocity.x);

        if ( m_slider.getPosition().x <= l_dest )
            stopSlider(l_dest);
    }
    else  
    {
        m_velocity.x += 1.f * m_acceleration;

        animateOn(m_velocity.x);

        if ( m_slider.getPosition().x >= r_dest )
            stopSlider(r_dest);
    }

    limitVelocity(delta_time);
}

void Toggle::animateOn(float x_velocity)  {
    m_slider.move(x_velocity, 0.f);
}

void Toggle::animateOff(float x_velocity)  {
    m_slider.move(x_velocity, 0.f);
}

void Toggle::adjustSliderPosition() {
    auto pos = m_shape.getPosition();
    float padding = 2.5f;
    
    (m_on) ? m_slider.setPosition(pos.x+m_size.x-(m_slider.getRadius()*2)-padding, pos.y+padding)
           : m_slider.setPosition(pos.x+padding, pos.y+padding);
}

void Toggle::adjustStatusPosition() {
    sf::Vector2f center = {m_shape.getGlobalBounds().left + m_shape.getGlobalBounds().width/2.f, 
                           m_shape.getGlobalBounds().top + m_shape.getGlobalBounds().height/2.f};
float padding = 2.0f;

    (m_on) ? m_status.setPosition( { (center.x - (m_shape.getGlobalBounds().width/2.f)) + (4*padding), center.y - (m_status.getCharacterSize()/2.f) } )
           : m_status.setPosition({(center.x + m_shape.getGlobalBounds().width/2.f) - ((m_status.getGlobalBounds().width) + (5*padding)), center.y - (m_status.getCharacterSize()/2.f) - padding });
}

void Toggle::limitVelocity(sf::Time delta_time) {
    if ( std::abs(m_velocity.x) > m_velocityXMax )
        m_velocity.x = m_velocityXMax * ((m_velocity.x < 0) ? -1.f : 1.f);
}

void Toggle::stopSlider(float dest_x) {
    // Halt slider velocity
    m_velocity.x = 0.f;
    // Correct misalignment of slider to the exact destination pixel
    m_slider.setPosition(dest_x, m_slider.getPosition().y);
    // Set click boolean as false
    setClicked(false);
    // Invert status state
    m_on = !m_on;
    // Recolor background stadium shape in correspondence with current status
    (m_on) ? m_shape.setFillColor(Resources::LightGreen) : m_shape.setFillColor(Resources::Gray);
    (m_on) ? m_status.setString("ON") : m_status.setString("OFF");
    // Adjust status text position
    adjustStatusPosition();
}

void Toggle::updateGeometry() {
    m_shape.setSize(m_size);
    m_slider.setRadius((m_size.y-5.f)/2.f);
    m_status.setCharacterSize(static_cast<unsigned int>(std::floor(m_size.y/3.f)));
    m_text.setCharacterSize(static_cast<unsigned int>(std::floor(m_size.y/3.f)));
}

void Toggle::updatePhysics() {
    m_acceleration = 3.f * (m_size.x/80.f);
}

void Toggle::updateTextPosition()
{
    sf::Vector2f center = {m_shape.getGlobalBounds().left + m_shape.getGlobalBounds().width/2.f, 
                           m_shape.getGlobalBounds().top + m_shape.getGlobalBounds().height/2.f};
    
    switch (m_side) 
    {
        default:
        case Right:
            m_text.setPosition({center.x+(m_shape.getGlobalBounds().width/2.f)+5.0f, m_status.getPosition().y});
            break;
        case Left: 
            m_text.setPosition({m_shape.getGlobalBounds().left-m_text.getGlobalBounds().width-10.f, m_status.getPosition().y});
            break;
        case Top: 
            m_text.setPosition({center.x-(m_text.getGlobalBounds().width/2.f), m_shape.getGlobalBounds().top-(2.f*m_text.getGlobalBounds().height)});
            break;
        case Bottom: 
            m_text.setPosition({center.x-(m_text.getGlobalBounds().width/2.f), m_shape.getGlobalBounds().top+m_shape.getGlobalBounds().height});
            break;
    }
}

void Toggle::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_shape, states);
    target.draw(m_status, states);
    target.draw(m_slider, states);
    target.draw(m_text, states);
}
