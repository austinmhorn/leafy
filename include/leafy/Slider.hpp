//
//  Slider.hpp
//  leafy
//
//  Created by Austin Horn on 9/10/23.
//  Copyright © 2023 Austin Horn. All rights reserved.
//

#ifndef Slider_hpp
#define Slider_hpp

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include <leafy/Interactable.hpp>

class LEAFY_API Slider : public Interactable 
{
public:
    Slider(sf::Vector2f size, unsigned int value = 0);
    ~Slider();

    void setPosition(const sf::Vector2f& position);
    void setDescription(const std::string &info);

    const sf::Vector2f& getSize() const;


    void handleMouseButtonPressedEvent(sf::RenderWindow& window, sf::Event event);
    void handleMouseButtonReleasedEvent(sf::RenderWindow& window, sf::Event event);
    void handleMouseMoveEvent(sf::RenderWindow& window, sf::Event event);
    virtual void handleEvent(sf::RenderWindow& window, sf::Event event) override;
    virtual void update(sf::Time delta_time) override;
    void moveSlider(const sf::Vector2f& position);

private:

    void updateGeometry();

    virtual void mouseOver() override;
    virtual void mouseLeave() override;
    virtual bool clicked() const override;
    virtual bool contains(sf::Vector2f point) const override;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:

    sf::RectangleShape m_rect;
    sf::CircleShape    m_slider;
    unsigned int       m_value;
    sf::Text           m_valueText;
    sf::Text           m_description;
    bool               m_clicked;
};

#endif /* Slider_hpp */