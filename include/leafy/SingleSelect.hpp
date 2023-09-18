//
//  SingleSelect.hpp
//  leafy
//
//  Created by Austin Horn on 9/10/23.
//  Copyright © 2023 Austin Horn. All rights reserved.
//

#ifndef SingleSelect_hpp
#define SingleSelect_hpp

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include <leafy/Interactable.hpp>

class LEAFY_API SingleSelect : public Interactable 
{
public:
    SingleSelect(float characterSize = 30.f);
    ~SingleSelect();

    void setPosition(const sf::Vector2f &position);
    void addChoice(const std::string &choice);

    const sf::Vector2f& getSize() const;
    std::string getSelection() const;

    void handleMouseButtonPressedEvent(sf::RenderWindow& window, sf::Event event);
    void handleMouseButtonReleasedEvent(sf::RenderWindow& window, sf::Event event);
    void handleMouseMoveEvent(sf::RenderWindow& window, sf::Event event);
    virtual void handleEvent(sf::RenderWindow& window, sf::Event event) override;
    virtual void update(sf::Time delta_time) override;

private:

    typedef std::pair<sf::RectangleShape, sf::Text> Checkbox;

    void resizeBox();
    void updateChoicesText(const std::string &choice);
    void updateGeometry();

    virtual void mouseOver() override;
    virtual void mouseLeave() override;
    virtual bool clicked() const override;
    virtual bool contains(sf::Vector2f point) const override;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:

    sf::RectangleShape    m_rect;
    bool                  m_clicked;
    std::vector<Checkbox> m_choices;
    sf::Color             m_activeColor;
    sf::Color             m_inactiveColor;
    float                 m_characterSize;

};

#endif /* SingleSelect_hpp */