//
//  Interactable.hpp
//  leafy
//
//  Created by Austin Horn on 1/29/23.
//  Copyright © 2023 Austin Horn. All rights reserved.
//

#ifndef Interactable_hpp
#define Interactable_hpp

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

#include <leafy/Config.hpp>

class LEAFY_API Interactable : public sf::Transformable, public sf::Drawable
{
    protected:
            
        Interactable() = default;
        ~Interactable() override = default;

        Interactable(const Interactable&) = default;
        Interactable& operator=(const Interactable&) = default;
        
        Interactable(Interactable&&) noexcept = default;
        Interactable& operator=(Interactable&&) noexcept = default;
        
        virtual void mouseClick() {}
        virtual void mouseOver() = 0;
        virtual void mouseLeave() = 0;
        virtual bool clicked() const = 0;
        virtual bool contains(sf::Vector2f point) const = 0;
        virtual void handleEvent(sf::RenderWindow& window, sf::Event event) = 0;
        virtual void update(sf::Time delta_time);

    private:

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;

};

#endif /* Interactable_hpp */
