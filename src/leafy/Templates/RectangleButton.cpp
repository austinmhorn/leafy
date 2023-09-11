#include <leafy/Button.hpp>

#include <iostream>

template <> /// Explicit Button sf::RectangleShape Button() Instantiation
Button<sf::RectangleShape>::Button(const sf::RectangleShape& shape)
    : m_shape(nullptr)
    , m_clicked(false)
{
    m_shape = new sf::RectangleShape(shape);
}
template <> /// Explicit Button sf::RectangleShape ~Button() Instantiation
Button<sf::RectangleShape>::~Button()
{
    if (m_shape)
        delete m_shape;
}
template <>
bool Button<sf::RectangleShape>::clicked() const
{
    return m_clicked;
}
template <>
bool Button<sf::RectangleShape>::contains(sf::Vector2f point) const
{
    return m_shape->getGlobalBounds().contains(point);
}
template <>
void Button<sf::RectangleShape>::mouseOver()
{
    m_shape->setFillColor({m_shape->getFillColor().r, m_shape->getFillColor().g, m_shape->getFillColor().b, 100});
}
template <>
void Button<sf::RectangleShape>::mouseLeave()
{
    m_shape->setFillColor({m_shape->getFillColor().r, m_shape->getFillColor().g, m_shape->getFillColor().b, 255});
}
template <>
void Button<sf::RectangleShape>::handleEvent(sf::RenderWindow &window, sf::Event event)
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
template <>
void Button<sf::RectangleShape>::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    
    states.texture = m_shape->getTexture();
    
    target.draw(*m_shape, states);
}
