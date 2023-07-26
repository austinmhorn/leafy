#ifndef Textbox_hpp
#define Textbox_hpp

#include "Base/Interactable.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>

#include <cctype>
#include <iostream>

class Textbox : public Interactable
{
public:
    
    enum class Side : unsigned {
        Top    = 'T',
        Right  = 'R',
        Bottom = 'B',
        Left   = 'L'
    };
    
    struct Description {
        sf::Text    text;
        Side        side;
    };
        
    Textbox();
        
    void setSize(const sf::Vector2f& size);
    void setPosition(const sf::Vector2f& position);
    void setFocus(bool focus);
    void setFillColor(sf::Color color);
    void setOutlineColor(sf::Color color);
    void setTextFillColor(sf::Color color);
    void setDescriptionString(const std::string& string);
    void setDescriptionSide(Side side);
    void setDescriptionCharacterSize(unsigned int size);
    void setDescriptionFillColor(sf::Color color);
    
    const sf::Vector2f& getSize() const;
    const sf::Vector2f& getPosition() const;
    const bool          hasFocus() const;
    const sf::Color&    getFillColor() const;
    const sf::Color&    getOutlineColor() const;
    const std::string&  getInputString() const;
    
    const bool contains(const sf::Vector2f point) const;
    void processKey(sf::Uint32 unicode);
    
    virtual void mouseOver() override;
    virtual void mouseLeave() override;
    virtual void handleEvent(sf::RenderWindow& window, sf::Event event) override;
    virtual void update(sf::Time elapsed) override;
    
    std::string clear();
    
private:
    
    void updateText(sf::Time elapsed);
    void positionText();
    void positionDescription();
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
private:
    
    sf::RectangleShape m_rect;
    std::string        m_input;
    sf::Text           m_text;
    sf::Font           m_font;
    bool               m_focus;
    sf::Time           m_timer;
    Description        m_description;
};

#endif /* Textbox_hpp */
