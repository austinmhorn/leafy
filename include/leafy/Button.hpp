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

#include <leafy/Interactable.hpp>
#include <leafy/Engine/Resources.hpp>
#include <leafy/Shapes/PolygonShape.hpp>
#include <leafy/Shapes/RoundedRectangleShape.hpp>
#include <leafy/Shapes/StadiumShape.hpp>

#include <iostream>
#include <exception>
#include <map>
#include <type_traits>
#include <functional>

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

        void setSize(const sf::Vector2f& size);
        const sf::Vector2f& getSize() const;

        void setRadius(float radius);
        void setRadius(const sf::Vector2f& radius);
        float getRadius() const;

        bool clicked() const override;
        bool contains(sf::Vector2f point) const override;
        void handleEvent(sf::RenderWindow& window, sf::Event event) override;
        void mouseOver() override final;

    protected:

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


#endif /* Button_hpp */
