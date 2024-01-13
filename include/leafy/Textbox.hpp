//
//  Textbox.hpp
//  leafy
//
//  Created by Austin Horn.
//  Copyright © 2023 Austin Horn. All rights reserved.
//

#ifndef Textbox_hpp
#define Textbox_hpp

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>

#include <leafy/UIElement.hpp>
#include <leafy/SmartMouse.hpp>

#include <cctype>
#include <iostream>

namespace leafy
{

class LEAFY_API Textbox 
    : public virtual UIElement
{
    public:
        
        enum class Side : unsigned 
        {
            Top    = 'T',
            Right  = 'R',
            Bottom = 'B',
            Left   = 'L'
        };
        
        struct Description 
        {
            sf::Text    text;
            Side        side;
        };
            
        Textbox(sf::RenderWindow& window);
            
        void setSize(const sf::Vector2f& size);
        void setPosition(const sf::Vector2f& position);
        void setFocus(bool focus);
        bool getFocus() const;
        void setFillColor(sf::Color color);
        void setOutlineColor(sf::Color color);
        void setTextFillColor(sf::Color color);
        void setDescriptionString(const std::string& string);
        void setDescriptionSide(Side side);
        void setDescriptionCharacterSize(unsigned int size);
        void setDescriptionFillColor(sf::Color color);
        
        const sf::Vector2f& getSize() const;
        const sf::Vector2f& getPosition() const;
        const sf::Color& getFillColor() const;
        const sf::Color& getOutlineColor() const;
        const std::string& getInputString() const;
        
        bool contains(const sf::Vector2f& point) const override;

        void handleEvent(sf::RenderWindow& window, sf::Event event) override;
        void update(sf::Time elapsed) override;
        
        std::string clear();
        
        
    private:

        void updateText(sf::Time elapsed);
        void positionText();
        void positionDescription();
        void processKey(sf::Uint32 unicode);

        void pressed() override;
        void clicked() override;
        void mouseEnter() override;
        void mouseLeave() override;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        sf::RectangleShape m_rect;
        std::string        m_input;
        sf::Text           m_text;
        sf::Font           m_font;
        bool               m_focus;
        sf::Time           m_timer;
        Description        m_description;
        SmartMouse*        m_mouse;
        char               m_cursor;
};

}

#endif /* Textbox_hpp */
