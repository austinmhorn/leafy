//
//  UIElement.hpp
//  leafy
//
//  Created by Austin Horn on 1/29/23.
//  Copyright © 2023 Austin Horn. All rights reserved.
//

#ifndef UIElement_hpp
#define UIElement_hpp

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

#include <leafy/Config.hpp>

namespace leafy
{

class LEAFY_API UIElement 
    : public sf::Transformable
    , public sf::Drawable
{
    public:

        void setPosition(const sf::Vector2f& position);
        const sf::Vector2f& getPosition() const;
        void setSize(const sf::Vector2f& size);
        const sf::Vector2f& getSize() const;
        void setRadius(float radius);
        float getRadius() const;
        void setPolygonRadius(const sf::Vector2f& radius);
        const sf::Vector2f& getPolygonRadius() const;

        //////////////////////
        /// @brief Update protected member data for derived types
        /// @param window Reference to window element is drawn on
        /// @param event The event in the window
        //////////////////////
        void refreshBase(sf::RenderWindow& window, sf::Event event);

    private:

        virtual void handleMouseMoveEvent(const sf::Vector2f& mousePosition);
        virtual void handleMouseButtonPressedEvent(const sf::Vector2f& mouseButtonPressedPosition);
        virtual void handleMouseButtonReleasedEvent(const sf::Vector2f& mouseButtonReleasedPosition);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;
   
    protected:
            
        UIElement() = default;
        ~UIElement() override = default;

        UIElement(const UIElement&) = default;
        UIElement& operator=(const UIElement&) = default;

        UIElement(UIElement&&) noexcept = default;
        UIElement& operator=(UIElement&&) noexcept = default;
        
        virtual void mouseEnter() = 0;
        virtual void mouseLeave() = 0;
        virtual void pressed() = 0;
        virtual void clicked() = 0;
        virtual bool contains(const sf::Vector2f& point) const = 0;
        virtual void handleEvent(sf::RenderWindow& window, sf::Event event) = 0;
        virtual void update(sf::Time delta_time) = 0;

        mutable bool m_mouseOver : 1;
        mutable bool m_needsUpdate : 1;
        mutable bool m_mouseButtonPressed : 1;
        mutable bool m_mouseButtonReleased : 1;
        sf::Mouse::Button m_mouseButton;

        [[maybe_unused]] mutable bool m_active = false;

        sf::Vector2f m_position;
        sf::Vector2f m_size;
};

}

#endif /* UIElement_hpp */
