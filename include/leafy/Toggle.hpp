//
//  Toggle.hpp
//  Leafly
//
//  Created by Austin Horn.
//  Copyright © 2023 Austin Horn. All rights reserved.
//

#ifndef Toggle_hpp
#define Toggle_hpp

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include <leafy/Interactable.hpp>
#include <leafy/StadiumShape.hpp>

#include <cmath>

class Toggle : public Interactable {
public:
    
    enum Side {
        Top,
        Bottom,
        Left,
        Right,
        TopLeft,
        TopRight,
        BottomLeft,
        BottomRight
    };
    
public:
    
    Toggle(bool, sf::Vector2f = {80.0f, 40.0f});
    ~Toggle() = default;
    Toggle(Toggle&);
    Toggle(const Toggle&);
    Toggle& operator=(const Toggle&);
    
    void setPosition(const sf::Vector2f&);
    void setPosition(float, float);
    void setDescription(const std::string&);
    void setTextSide(Toggle::Side);
    
    sf::Vector2f getApproxSize() const;
    sf::Vector2f getExactSize() const;
    const bool&  isOn() const;
    
    bool contains(sf::Vector2f point) const override;
    void mouseOver() override;
    void mouseLeave() override;
    void handleEvent(sf::RenderWindow&, sf::Event) override;
    void update(sf::Time delta_time) override;
    
    void handleMouseButtonPressedEvent(sf::RenderWindow&, sf::Event);
    void handleMouseButtonReleasedEvent(sf::RenderWindow&, sf::Event);
    void handleMouseMoveEvent(sf::RenderWindow&, sf::Event);
    
private:
    
    void        setClicked(bool clicked);
    const bool& getClicked() const;
    void adjustSliderPosition();
    void adjustStatusPosition();
    
    void init();
    void animate(sf::Time&);
    void animateOn(float);
    void animateOff(float);
    void draw(sf::RenderTarget&, sf::RenderStates) const override;
    
private:
    
    sf::StadiumShape m_shape;
    sf::CircleShape  m_slider;
    sf::Text         m_status;
    sf::Text         m_text;
    Toggle::Side     m_side;
    bool             m_on;
    sf::Vector2f     m_size;
    bool             m_clicked;
};

#endif /* Toggle_hpp */
