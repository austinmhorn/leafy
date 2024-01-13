//
//  Textbox.cpp
//  leafy
//
//  Created by Austin Horn on 12/2/22.
//  Copyright © 2022 Austin Horn. All rights reserved.
//

#include <leafy/Textbox.hpp>
#include <leafy/Engine/Resources.hpp>

namespace leafy
{

Textbox::Textbox(sf::RenderWindow& window)
    : m_rect()
    , m_input()
    , m_text()
    , m_font()
    , m_focus( false )
    , m_timer( sf::seconds(0.f) )
    , m_cursor( '|' )
{
    m_font = Resources::Sansation;

    UIElement::setSize({300.f, 45.f});
    UIElement::setPosition(m_position);

    m_rect.setSize(m_size);
    m_rect.setPosition(m_position);
    m_rect.setFillColor(sf::Color::White);
    m_rect.setOutlineColor(sf::Color::Green);
    m_rect.setOutlineThickness(1.f);
        
    m_text.setFont(m_font);
    m_text.setCharacterSize(20.f);
    m_text.setOrigin(m_text.getGlobalBounds().width/2.f, m_text.getGlobalBounds().height/2.f);
    m_text.setFillColor({32, 32, 32});
    
    positionText();
    
    m_description.text.setFont(m_font);
    m_description.text.setCharacterSize(30);

    this->m_mouse = &Resources::smartmouse;
    this->m_mouse->create(&window, SmartMouse::Pointer::Arrow);
};

void Textbox::setSize(const sf::Vector2f& size)
{
    UIElement::setSize(size);
    m_rect.setSize(m_size);
}
void Textbox::setPosition(const sf::Vector2f& position)
{
    UIElement::setPosition(position);
    m_rect.setPosition(m_position);
    positionText();
}
void Textbox::setFocus(bool focus)
{
    m_focus = focus;
}
bool Textbox::getFocus() const
{
    return m_focus;
}
void Textbox::setFillColor(sf::Color color)
{
    m_rect.setFillColor(color);
}
void Textbox::setOutlineColor(sf::Color color)
{
    m_rect.setOutlineColor(color);
}
void Textbox::setTextFillColor(sf::Color color)
{
    m_text.setFillColor(color);
}
void Textbox::setDescriptionString(const std::string& string)
{
    m_description.text.setString(string);
    positionDescription();
}
void Textbox::setDescriptionSide(Textbox::Side side)
{
    m_description.side = side;
    positionDescription();
}
void Textbox::setDescriptionCharacterSize(unsigned int size)
{
    m_description.text.setCharacterSize(size);
    positionDescription();
}
void Textbox::setDescriptionFillColor(sf::Color color)
{
    m_description.text.setFillColor(color);
}
const sf::Vector2f& Textbox::getSize() const
{
    return m_rect.getSize();
}
const sf::Vector2f& Textbox::getPosition() const
{
    return m_rect.getPosition();
}
const sf::Color& Textbox::getFillColor() const
{
    return m_rect.getFillColor();
}
const sf::Color& Textbox::getOutlineColor() const
{
    return m_rect.getOutlineColor();
}
const std::string& Textbox::getInputString() const
{
    return m_input;
}
bool Textbox::contains(const sf::Vector2f& point) const
{
    return m_rect.getGlobalBounds().contains(point);
}
void Textbox::processKey(sf::Uint32 unicode)
{
    if (unicode <= 128)
    {
        if (unicode == 8 && m_input.size()) // Backspace
        {
            m_input.pop_back();
        }
        else if ( std::isprint(unicode) )
        {
            ///< Keeps text within bounds
            if ( (m_text.getGlobalBounds().width+m_text.getCharacterSize()) < m_rect.getGlobalBounds().width )
            {
                m_input += static_cast<char>(unicode);
            }
        }
    }
}
void Textbox::mouseEnter()
{
    this->m_mouse->setPointer(SmartMouse::Pointer::Text);
}
void Textbox::mouseLeave()
{
    this->m_mouse->setPointer(SmartMouse::Pointer::Arrow);
}
void Textbox::pressed() 
{

}
void Textbox::clicked()
{
    
}

void Textbox::handleEvent(sf::RenderWindow& window, sf::Event event)
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

            if ( event.mouseButton.button == sf::Mouse::Button::Left )
            {
                if ( contains(mouse_btn) )
                    setFocus( !getFocus() );
                else
                    setFocus( false );
            }
            break;
        
        case sf::Event::TextEntered:
            if ( getFocus() )
            {
                if (event.key.code == 10) // New Line
                    std::cout << clear() << std::endl;
                else
                    processKey(event.key.code);
            }
            break;

        default:
            break;
    }
}



void Textbox::update(sf::Time elapsed)
{
    updateText(elapsed);
    positionText();
}
std::string Textbox::clear()
{
    return std::move(m_input);
}
void Textbox::updateText(sf::Time elapsed)
{
    ///< Remove underscore from end of string if lost focus
    if (!m_focus)
    {
        std::string str = m_text.getString().toAnsiString();
        if ( str.size() )
        {
            if (str.at(str.size()-1) == m_cursor)
            {
                str.pop_back();
                m_text.setString(str);
            }
        }
        
        return;
    }
    
    static bool show_cursor;
    m_timer += elapsed;
    
    /// Show and hide vertical bar every 0.5 seconds to mimic a cursor
    if (m_timer >= sf::seconds(0.5f))
    {
        show_cursor = !show_cursor;
        m_timer = sf::Time::Zero;
    }
    
    m_text.setString(m_input + (show_cursor ? m_cursor : ' '));
}
void Textbox::positionText()
{
    sf::Vector2f center_point = {m_rect.getGlobalBounds().left + m_rect.getGlobalBounds().width/2.f,
                                 m_rect.getGlobalBounds().top + m_rect.getGlobalBounds().height/2.f};

    sf::Vector2f text_bounds = {m_text.getGlobalBounds().width,
                                m_text.getGlobalBounds().height};
    
    m_text.setPosition(center_point.x - (text_bounds.x/2.f),
                       center_point.y - (m_text.getCharacterSize()/2.f));
}
void Textbox::positionDescription()
{
    const sf::FloatRect textRect = m_description.text.getGlobalBounds();
    const sf::Vector2f boundsCenter = {m_rect.getGlobalBounds().left + m_rect.getGlobalBounds().width/2.f,
                                       m_rect.getGlobalBounds().top  + m_rect.getGlobalBounds().height/2.f};
    
    switch ( m_description.side )
    {
        default:
        case Side::Top:
            m_description.text.setPosition({ boundsCenter.x - textRect.width/2.f, boundsCenter.y - m_rect.getGlobalBounds().height - textRect.height });
            break;
        case Side::Right:
            
            break;
        case Side::Bottom:
            
            break;
        case Side::Left:
            
            break;
    }
}
void Textbox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_description.text);
    target.draw(m_rect);
    target.draw(m_text);
}

}