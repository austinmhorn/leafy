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

#include <leafy/UIElement.hpp>

namespace leafy
{

class LEAFY_API Slider 
    : public UIElement 
{
    public:

        Slider(sf::Vector2f size, unsigned int value = 0);
        ~Slider();

        void setPosition(const sf::Vector2f& position);
        void setDescription(const std::string &info);

        const sf::Vector2f& getSize() const;

        void handleEvent(sf::RenderWindow& window, sf::Event event) override;
        void update(sf::Time delta_time) override;

    private:

        void moveSlider(const sf::Vector2f& position);
        void updateGeometry();

        virtual void handleMouseMoveEvent(const sf::Vector2f& mousePosition) override;
        virtual void handleMouseButtonPressedEvent(const sf::Vector2f& mouseButtonPressedPosition) override;
        virtual void handleMouseButtonReleasedEvent(const sf::Vector2f& mouseButtonReleasedPosition) override;

        void pressed() override;
        void clicked() override;
        void mouseEnter() override;
        void mouseLeave() override;
        bool contains(const sf::Vector2f& point) const override;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        sf::RectangleShape m_rect;
        sf::CircleShape    m_slider;
        unsigned int       m_value;
        sf::Text           m_valueText;
        sf::Text           m_description;

        sf::Vector2f m_mousePosition;
        float        m_mousePositionOffset;
};

}

#endif /* Slider_hpp */