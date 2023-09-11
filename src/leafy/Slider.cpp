#include <leafy/Slider.hpp>
#include <leafy/Engine/Resources.hpp>

#include <cmath>
#include <iostream>

Slider::Slider(sf::Vector2f size, unsigned int value)
    : m_rect(size)
    , m_slider(2.f*size.y)
    , m_value(value)
    , m_valueText({std::to_string(value), Resources::Sansation, static_cast<unsigned int>(std::floor(size.y*2.f))})
    , m_description({"", Resources::Sansation, static_cast<unsigned int>(std::floor(size.y*3.f))})
    , m_clicked(false)
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
    m_rect.setPosition(position);
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
void Slider::mouseOver()
{
    m_slider.setFillColor({32, 32, 32});
}
void Slider::mouseLeave()
{
    m_slider.setFillColor(sf::Color::Blue);
}
bool Slider::clicked() const
{
    return m_clicked;
}
bool Slider::contains(sf::Vector2f point) const
{
    return m_slider.getGlobalBounds().contains(point);
}

void Slider::handleMouseButtonPressedEvent(sf::RenderWindow& window, sf::Event event) 
{
    sf::Vector2f click_pos = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
    if ( contains(click_pos) )
    {
        switch (event.mouseButton.button)
        {
            case sf::Mouse::Left:
                m_clicked = true;

                break;
                    
            case sf::Mouse::Right:
                break;
                    
            default:
                break;
        }
    }
}

void Slider::handleMouseButtonReleasedEvent(sf::RenderWindow& window, sf::Event event)
{
    sf::Vector2f click_pos = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});

    switch (event.mouseButton.button)
    {
        case sf::Mouse::Left:
            m_clicked = false;
            break;
                
        case sf::Mouse::Right:
            break;
                
        default:
            break;
    }
}

void Slider::handleMouseMoveEvent(sf::RenderWindow& window, sf::Event event)
{
    sf::Vector2f mouse_pos = window.mapPixelToCoords({event.mouseMove.x, event.mouseMove.y});

    (contains(mouse_pos) || m_clicked) ? mouseOver() : mouseLeave();

    if (m_clicked) 
        moveSlider(mouse_pos);
}

void Slider::handleEvent(sf::RenderWindow& window, sf::Event event)
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
        
        case sf::Event::TextEntered:
            break;

        default:
            break;
    }
}
void Slider::update(sf::Time delta_time)
{
    if (m_clicked)
    {
        sf::Vector2f rpos = {m_rect.getGlobalBounds().left, m_rect.getGlobalBounds().top};
        sf::Vector2f size = {m_rect.getGlobalBounds().width, m_rect.getGlobalBounds().height};
        sf::Vector2f spos = {m_slider.getGlobalBounds().left, m_slider.getGlobalBounds().top};

        unsigned int value = std::round(std::ceil(spos.x - rpos.x + m_slider.getRadius())) / (size.x/100.f);
        m_value = value;
        m_valueText.setString(std::to_string(value));

    }
}
void Slider::moveSlider(const sf::Vector2f& position)
{
    sf::Vector2f pos = {m_rect.getGlobalBounds().left, m_rect.getGlobalBounds().top};

    if ( position.x < (m_rect.getGlobalBounds().left - m_slider.getRadius()) )
    {
        m_slider.setPosition( { pos.x - m_slider.getRadius(), (pos.y - (m_slider.getRadius())) + (m_rect.getSize().y/2.f) } );
    }
    else if ( position.x > (m_rect.getGlobalBounds().left- m_slider.getRadius()) + (100 * (m_rect.getGlobalBounds().width/100.f)) )
    {
        m_slider.setPosition( { (pos.x - m_slider.getRadius()) + (100 * (m_rect.getGlobalBounds().width/100.f)), (pos.y - (m_slider.getRadius())) + (m_rect.getSize().y/2.f) } );
    }
    else
    {
        m_slider.setPosition( { position.x, (pos.y - (m_slider.getRadius())) + (m_rect.getSize().y/2.f) } );
    }
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