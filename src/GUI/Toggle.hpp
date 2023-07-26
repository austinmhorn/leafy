//
//  Toggle.hpp
//  War
//
//  Created by Austin Horn on 12/2/22.
//  Copyright © 2022 Austin Horn. All rights reserved.
//

#ifndef Toggle_hpp
#define Toggle_hpp

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include "Base/Interactable.hpp"
#include "Shapes/StadiumShape.hpp"

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
    
    const bool contains(const sf::Vector2f&) const;
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
    sf::StadiumShape m_shadow;
    sf::CircleShape  m_slider;
    sf::Text         m_status;
    
    bool             m_on;
    sf::Vector2f     m_size;
    sf::Text         m_text;
    Toggle::Side     m_side;
    
    bool             m_clicked;
};

#endif /* Toggle_hpp */
