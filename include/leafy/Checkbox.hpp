//
//  Checkbox.hpp
//  leafy
//
//  Created by Austin Horn on 9/10/23.
//  Copyright © 2023 Austin Horn. All rights reserved.
//

#ifndef Checkbox_hpp
#define Checkbox_hpp

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include <leafy/Interactable.hpp>

class LEAFY_API Checkbox : public Interactable 
{
public:
    Checkbox(float characterSize = 30.f, bool multipleSelectionsAllowed = false);
    ~Checkbox();

    void setPosition(const sf::Vector2f &position);
    void addChoice(const std::string &choice);

    const sf::Vector2f& getSize() const;
    std::vector<std::string> getSelection() const;

    void handleMouseButtonPressedEvent(sf::RenderWindow& window, sf::Event event);
    void handleMouseButtonReleasedEvent(sf::RenderWindow& window, sf::Event event);
    void handleMouseMoveEvent(sf::RenderWindow& window, sf::Event event);
    virtual void handleEvent(sf::RenderWindow& window, sf::Event event) override;
    virtual void update(sf::Time delta_time) override;

private:

    typedef std::pair<sf::RectangleShape, sf::Text> Box;

    void resizeBox();
    void updateChoicesText(const std::string &choice);
    void updateGeometry();

    virtual void mouseOver() override;
    virtual void mouseLeave() override;
    virtual bool clicked() const override;
    virtual bool contains(sf::Vector2f point) const override;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:

    sf::RectangleShape m_rect;
    bool               m_clicked;
    std::vector<Box>   m_choices;
    sf::Color          m_activeColor;
    sf::Color          m_inactiveColor;
    float              m_characterSize;
    bool               m_allowMultipleSelections;
};

#endif /* Checkbox_hpp */