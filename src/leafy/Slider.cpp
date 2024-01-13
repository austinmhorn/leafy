//
//  Slider.cpp
//  leafy
//
//  Created by Austin Horn on 12/2/22.
//  Copyright © 2022 Austin Horn. All rights reserved.
//

#include <leafy/Slider.hpp>
#include <leafy/Engine/Resources.hpp>

#include <cmath>
#include <iostream>

namespace leafy
{

Slider::Slider(sf::Vector2f size, unsigned int value)
    : m_rect(size)
    , m_slider(2.f*size.y)
    , m_value( (value > 100) ? 100 : value )
    , m_valueText({std::to_string(m_value), Resources::Sansation, static_cast<unsigned int>(std::floor(size.y*2.f))})
    , m_description({"", Resources::Sansation, static_cast<unsigned int>(std::floor(size.y*3.f))})
{
    m_rect.setFillColor(sf::Color::White);

    m_slider.setFillColor(sf::Color::Blue);
    m_slider.setOutlineColor(sf::Color::White);
    m_slider.setOutlineThickness(1.f);

    m_valueText.setStyle(sf::Text::Bold);

    updateGeometry();
}

Slider::~Slider() 
{

}
void Slider::setPosition(const sf::Vector2f &position)
{
    UIElement::setPosition( position );
    m_rect.setPosition( m_position );
    updateGeometry();
}
void Slider::setDescription(const std::string &info)
{
    m_description.setString(info);
    updateGeometry();
}
const sf::Vector2f &Slider::getSize() const
{
    return m_rect.getSize();
}
void Slider::mouseEnter()
{
    m_slider.setFillColor({32, 32, 32});
}
void Slider::mouseLeave()
{
    m_slider.setFillColor(sf::Color::Blue);
}
void Slider::pressed() 
{
}
void Slider::clicked()
{
}

bool Slider::contains(const sf::Vector2f& point) const
{
    return m_slider.getGlobalBounds().contains(point);
}

void Slider::handleMouseMoveEvent(const sf::Vector2f& mousePosition)
{
    (contains(mousePosition) || m_mouseButtonPressed) ? mouseEnter() : mouseLeave();

    if ( m_mouseButtonPressed )
        moveSlider(mousePosition);
}
void Slider::handleMouseButtonPressedEvent(const sf::Vector2f& mouseButtonPressedPosition)
{
    if ( contains(mouseButtonPressedPosition)  &&  sf::Mouse::isButtonPressed(sf::Mouse::Left) )
        m_mouseButtonPressed = true;
}
void Slider::handleMouseButtonReleasedEvent(const sf::Vector2f& mouseButtonReleasedPosition)
{
    m_mouseButtonPressed = false;
}

void Slider::handleEvent(sf::RenderWindow& window, sf::Event event)
{
    sf::Vector2f mouse_move = window.mapPixelToCoords({event.mouseMove.x, event.mouseMove.y});
    sf::Vector2f click_pos = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});

    switch (event.type)
    {            
        case sf::Event::MouseMoved:
            handleMouseMoveEvent(mouse_move);
            break;
        case sf::Event::MouseButtonPressed:
            handleMouseButtonPressedEvent(click_pos);
            break;
        case sf::Event::MouseButtonReleased:
            handleMouseButtonReleasedEvent(click_pos);
            break;
        default:
            break;
    }
}
void Slider::update(sf::Time delta_time)
{
    if ( m_mouseButtonPressed )
    {
        sf::Vector2f rpos = {m_rect.getGlobalBounds().left, m_rect.getGlobalBounds().top}; // Horizontal bar position
        sf::Vector2f size = {m_rect.getGlobalBounds().width, m_rect.getGlobalBounds().height}; // Horizontal bar size
        sf::Vector2f spos = {m_slider.getGlobalBounds().left, m_slider.getGlobalBounds().top}; // Slider knob position

        unsigned int value = std::ceil(spos.x - rpos.x + m_slider.getRadius()) / (size.x/100.f); // Approximate value
        m_value = value; 
        m_valueText.setString(std::to_string(value));
    }
}
void Slider::moveSlider(const sf::Vector2f& position)
{
    sf::Vector2f rpos = {m_rect.getGlobalBounds().left, m_rect.getGlobalBounds().top};

    //std::cout << "Mouse pos: " << position.x << ", " << position.y << std::endl;
    //std::cout << "Slider pos: " << m_slider.getPosition().x << ", " << m_slider.getPosition().y << std::endl;
    //std::cout << "offset: " << position.x - m_slider.getPosition().x << std::endl;

    if ( position.x < (m_rect.getGlobalBounds().left - m_slider.getRadius()) )
        m_slider.setPosition( { rpos.x - m_slider.getRadius(), (rpos.y - (m_slider.getRadius())) + (m_rect.getSize().y/2.f) } );
    else if ( position.x > (m_rect.getGlobalBounds().left- m_slider.getRadius()) + (100 * (m_rect.getGlobalBounds().width/100.f)) )
        m_slider.setPosition( { (rpos.x - m_slider.getRadius()) + (100 * (m_rect.getGlobalBounds().width/100.f)), (rpos.y - (m_slider.getRadius())) + (m_rect.getSize().y/2.f) } );
    else
        m_slider.setPosition( { position.x, (rpos.y - (m_slider.getRadius())) + (m_rect.getSize().y/2.f) } );
}
void Slider::updateGeometry()
{
    sf::Vector2f pos = {m_rect.getGlobalBounds().left, m_rect.getGlobalBounds().top};

    m_slider.setPosition( { (pos.x - m_slider.getRadius()) + (m_value * (m_rect.getGlobalBounds().width/100.f)), (pos.y - (m_slider.getRadius())) + (m_rect.getSize().y/2.f) } );
    m_valueText.setPosition( { pos.x + m_rect.getGlobalBounds().width/2.f - (m_valueText.getGlobalBounds().width/2.f), pos.y + m_rect.getGlobalBounds().height + m_slider.getRadius() + 5.f } );
    m_description.setPosition( { pos.x + m_rect.getGlobalBounds().width/2.f - (m_description.getGlobalBounds().width/2.f), pos.y - m_slider.getRadius() - m_description.getGlobalBounds().height- 5.f } );
}
void Slider::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_rect);
    target.draw(m_slider);
    target.draw(m_valueText);
    target.draw(m_description);
}

}