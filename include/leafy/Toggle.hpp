//
//  Toggle.hpp
//  leafy
//
//  Created by Austin Horn.
//  Copyright © 2023 Austin Horn. All rights reserved.
//

#ifndef Toggle_hpp
#define Toggle_hpp

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include <leafy/UIElement.hpp>
#include <leafy/Shapes/StadiumShape.hpp>

#include <cmath>

namespace leafy
{

class LEAFY_API Toggle 
    : public UIElement 
{
    public:

        enum Side { Left, Right, Top, Bottom };
        
        Toggle(bool, sf::Vector2f);
        ~Toggle() = default;
        
        void setPosition(const sf::Vector2f&);
        void setPosition(float, float);
        const sf::Vector2f& getPosition() const;
        void setDescription(const std::string&);
        sf::Text& getDescription();
        void setTextSide(Toggle::Side);
        void setSize(const sf::Vector2f& size);
        const sf::Vector2f& getSize() const;
        
        const bool isOn() const;

        // Overidden purely virtual methods from parent class UIElement 
        bool contains(const sf::Vector2f& point) const override;
        void handleEvent(sf::RenderWindow&, sf::Event) override;
        void update(sf::Time delta_time) override;
    
    private:

        void init();

        void animate(sf::Time&);
        void animateOn(float);
        void animateOff(float);
        void limitVelocity(sf::Time delta_time);
        void stopSlider(float dest_x);
        void adjustSliderPosition();
        void adjustStatusPosition();
        void updateGeometry();
        void updatePhysics();
        void updateTextPosition();

        void mouseEnter() override;
        void mouseLeave() override;
        void pressed() override;
        void clicked() override;
        void draw(sf::RenderTarget&, sf::RenderStates) const override;
                
        sf::StadiumShape m_shape;
        sf::CircleShape  m_slider;
        sf::Text         m_status;
        sf::Text         m_text;
        Toggle::Side     m_side;
        bool             m_on;
        bool             m_isAnimating;
        sf::Vector2f     m_velocity;
        float            m_velocityXMax;
        float            m_acceleration;
};

}

#endif /* Toggle_hpp */
