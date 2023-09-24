//
//  Button.hpp
//  leafy
//
//  Created by Austin Horn on 1/29/23.
//  Copyright © 2023 Austin Horn. All rights reserved.
//

#ifndef Button_hpp
#define Button_hpp

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>

#include <leafy/Interactable.hpp>
#include <leafy/Engine/Resources.hpp>
#include <leafy/Shapes/RoundedRectangleShape.hpp>
#include <leafy/Shapes/StadiumShape.hpp>

#include <iostream>
#include <exception>
#include <map>
#include <type_traits>

/* 
    // Method 1
    // Simple method; Declare a button using a derived sf::Shape 
        Button stadiumButton = Button(sf::StadiumShape()); 

    // Method 2
    // Ok; But needs parenthesis around arguement to declare a variable
        Button stadiumButton( (sf::StadiumShape()) );       

    // Method 3
    // Pass a previously created shape to be copied
        sf::StadiumShape stadiumShape;        
        Button stadiumButton(stadiumShape);                 
*/

template <typename T>
class LEAFY_API Button : public Interactable
{
    public:

        // Verify T is a derived sf::Shape object; required [even if not drawing shape] to deduce T
        static_assert(std::is_base_of<sf::Shape, T>::value, "T must be a derived class of sf::Shape.");

        enum class Function : unsigned int
        {
            MouseOver  = 0,
            MouseLeave = 1,
            ClickedOn  = 2,
            ClickedOff = 3,
        };

        enum class TextAlignment : unsigned int
        {
            Centered = 0,
            Top      = 1,
            Right    = 2,
            Bottom   = 2,
            Left     = 4,
        };

        typedef std::map<Function, std::function<void()>> FunctionMap;
        
        Button(const T& shape = T());

        void setPosition(const sf::Vector2f& position);
        void setSize(const sf::Vector2f& size);
        void setShapeFillColor(const sf::Color& color);
        void setShapeOutlineColor(const sf::Color& color);
        void setShapeOutlineThickness(float thickness);
        void setWillDrawShape(bool willDraw);
        void setTextString(const std::string& string);
        void setTextFillColor(const sf::Color& color);
        void setMouseOverFunction(std::function<void()> function);
        void setMouseLeaveFunction(std::function<void()> function);
        void setMouseClickOnFunction(std::function<void()> function);
        void setMouseClickOffFunction(std::function<void()> function);

        const sf::Vector2f& getSize() const;

        bool clicked() const override;
        bool contains(sf::Vector2f point) const override;
        void handleEvent(sf::RenderWindow& window, sf::Event event) override;
        void mouseOver() override final;

    protected:

        void update();
        void updateShapePosition();
        void updateShapeSize();
        void updateTextPosition();
        void updateAlignment();

        void mouseClick() override final;
        void mouseLeave() override final;
        void handleMouseMoveEvent(const sf::Vector2f& mousePosition);
        void handleMouseButtonPressedEvent(const sf::Vector2f& mouseButtonPressedPosition);
        void handleMouseButtonReleasedEvent(const sf::Vector2f& mouseButtonReleasedPosition);
        
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        T             m_shape;
        sf::Text      m_text;
        sf::Vector2f  m_position;
        sf::Vector2f  m_size;
        bool          m_mouseOver;
        bool          m_clicked;
        bool          m_needsUpdate;
        bool          m_drawShape;
        bool          m_clickPressInBounds;
        bool          m_translucentHover;
        FunctionMap   m_funcs;
        TextAlignment m_alignment;

        sf::Texture m_texture;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief Constructor
///
/// \param shape Derived sf::Shape object; required [even if shape is disabled] to deduce T
///////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
Button<T>::Button(const T& shape)
    : m_shape( shape )
    , m_text( "", Resources::Sansation, 30 )
    , m_position( shape.getPosition() )
    , m_size( shape.getSize() )
    , m_mouseOver( false )
    , m_clicked( false )
    , m_needsUpdate( false )
    , m_drawShape( true )
    , m_clickPressInBounds( false ) 
    , m_translucentHover( true )
    , m_alignment( TextAlignment::Centered )
{
    m_funcs.clear();
}

template <typename T>
bool Button<T>::clicked() const
{
    return m_clicked;
}

template <typename T>
bool Button<T>::contains(sf::Vector2f point) const
{
    return ( m_drawShape ) ? m_shape.getGlobalBounds().contains(point) : m_text.getGlobalBounds().contains(point);
}

template <typename T>
void Button<T>::mouseClick() 
{
    // Only call if assigned
    if ( m_clicked && m_funcs[Function::ClickedOn] )
        m_funcs[Function::ClickedOn]();
    else if ( !m_clicked && m_funcs[Function::ClickedOff] )
        m_funcs[Function::ClickedOff]();
}

template <typename T>
void Button<T>::mouseOver()
{
    // Only call if assigned
    if ( m_funcs[Function::MouseOver] ) 
         m_funcs[Function::MouseOver]();
    if ( m_translucentHover )
    {
        const sf::Color shapeColor = m_shape.getFillColor();
        const sf::Color textColor = m_text.getFillColor();

        if ( m_drawShape )
        {
            m_shape.setFillColor({shapeColor.r, shapeColor.g, shapeColor.b, static_cast<sf::Uint8>(shapeColor.a/2)});
            m_text.setFillColor({textColor.r, textColor.g, textColor.b, static_cast<sf::Uint8>(textColor.a/2)});
        }
        else
        {
            m_text.setFillColor({textColor.r, textColor.g, textColor.b, static_cast<sf::Uint8>(textColor.a/2)});
        }
    }
}

template <typename T>
void Button<T>::mouseLeave()
{
    // Only call if assigned
    if ( m_funcs[Function::MouseLeave] ) 
         m_funcs[Function::MouseLeave]();

    if ( m_translucentHover )
    {
        const sf::Color shapeColor = m_shape.getFillColor();
        const sf::Color textColor = m_text.getFillColor();

        if ( m_drawShape )
        {
            m_shape.setFillColor({shapeColor.r, shapeColor.g, shapeColor.b, 255});
            m_text.setFillColor({textColor.r, textColor.g, textColor.b, 255});
        }
        else
        {
            m_text.setFillColor({textColor.r, textColor.g, textColor.b, 255});
        }
    }
}

template <typename T>
void Button<T>::handleEvent(sf::RenderWindow &window, sf::Event event)
{
    sf::Vector2f mouse_move = window.mapPixelToCoords({event.mouseMove.x, event.mouseMove.y});
    sf::Vector2f mouse_btn = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
    
    switch (event.type)
    {
        case sf::Event::MouseMoved:
            // Update button with new mouse position
            handleMouseMoveEvent(mouse_move);
            break;
        case sf::Event::MouseButtonPressed:
            // Allows for only processing a click release event if the press originated within bounds of the button
            handleMouseButtonPressedEvent(mouse_btn);
            break;
        case sf::Event::MouseButtonReleased:
                        
            handleMouseButtonReleasedEvent(mouse_btn);
            break;
        default:
            break;
    }
}

template <typename T>
void Button<T>::handleMouseMoveEvent(const sf::Vector2f& mousePosition)
{
    if ( contains( mousePosition ) )
    {
        if ( !m_mouseOver )
        {
            m_mouseOver = true;
            m_needsUpdate = true;
        }
    }
    else
    {
        if ( m_mouseOver )
        {
            m_mouseOver = false;
            m_needsUpdate = true;
        }
    }

    if ( m_needsUpdate )
    {
        m_needsUpdate = false;
        (m_mouseOver) ?  mouseOver() : mouseLeave();
    }
}

template <typename T>
void Button<T>::handleMouseButtonPressedEvent(const sf::Vector2f& mouseButtonPressedPosition)
{
    m_clickPressInBounds = contains(mouseButtonPressedPosition);
}

template <typename T>
void Button<T>::handleMouseButtonReleasedEvent(const sf::Vector2f& mouseButtonReleasedPosition)
{
    if ( m_mouseOver && contains(mouseButtonReleasedPosition) )
    {
        m_clicked = !m_clicked;
    }
    else
    {
        m_clicked = false;
    }

    if ( m_clickPressInBounds && m_mouseOver )
        mouseClick();
}

template <typename T>
void Button<T>::setPosition(const sf::Vector2f& position)
{
    m_position = position;
    update();
}

template <typename T>
void Button<T>::setSize(const sf::Vector2f& size)
{
    m_size = size;
    update();
}

template <typename T>
void Button<T>::setShapeFillColor(const sf::Color& color) 
{
    m_shape.setFillColor(color);

}

template <typename T>
void Button<T>::setShapeOutlineColor(const sf::Color& color) 
{
    m_shape.setOutlineColor(color);
}

template <typename T>
void Button<T>::setShapeOutlineThickness(float thickness)
{
    m_shape.setOutlineThickness(thickness);
    update();
}

template <typename T>
void Button<T>::setWillDrawShape(bool willDraw)
{
    m_drawShape = willDraw;
}

template <typename T>
void Button<T>::setTextString(const std::string& string)
{
    m_text.setString(string);
    update();
}

template <typename T>
void Button<T>::setTextFillColor(const sf::Color& color)
{
    m_text.setFillColor(color);
}

template <typename T>
void Button<T>::setMouseOverFunction(std::function<void()> function)
{
    m_funcs[Function::MouseOver] = function;
}

template <typename T>
void Button<T>::setMouseLeaveFunction(std::function<void()> function)
{
    m_funcs[Function::MouseLeave] = function;
}

template <typename T>
void Button<T>::setMouseClickOnFunction(std::function<void()> function)
{
    m_funcs[Function::ClickedOn] = function;
}

template <typename T>
void Button<T>::setMouseClickOffFunction(std::function<void()> function)
{
    m_funcs[Function::ClickedOff] = function;
}

template <typename T>
const sf::Vector2f& Button<T>::getSize() const
{
    return m_shape.getSize();
}

template <typename T>
void Button<T>::update()
{
    if ( m_drawShape )
    {
        updateShapePosition();
        updateShapeSize();
        updateAlignment();
    }
    else 
    {
        updateTextPosition();
    }
}

template <typename T>
void Button<T>::updateShapePosition()
{
    m_shape.setPosition(m_position);
}

template <typename T>
void Button<T>::updateShapeSize()
{
    m_shape.setSize(m_size);
}

template <typename T>
void Button<T>::updateTextPosition()
{
    m_text.setPosition(m_position);
}

template <typename T>
void Button<T>::updateAlignment()
{    
    const sf::Vector2f pos = m_position;
    const sf::Vector2f sz = m_size;
    const sf::Vector2f midpoint = {pos.x + sz.x/2.f, pos.y + sz.y/2.f};
    const float diffY = m_text.getCharacterSize() - m_text.getGlobalBounds().height;

    switch ( m_alignment )
    {
    case TextAlignment::Centered:
        m_text.setPosition({midpoint.x - m_text.getGlobalBounds().width/2.f, midpoint.y - m_text.getGlobalBounds().height*0.5f - m_shape.getOutlineThickness() - diffY});
        break;
    
    default:
        break;
    }
}

template <typename T>
void Button<T>::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    
    states.texture = &m_texture;
    
    if ( m_drawShape )
        target.draw(m_shape, states);
    if ( !m_text.getString().isEmpty() )
        target.draw(m_text);
}

#endif /* Button_hpp */
