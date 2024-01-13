//
//  Dropdown.hpp
//  leafy
//
//  Created by Austin Horn.
//  Copyright © 2023 Austin Horn. All rights reserved.
//

#ifndef Dropdown_hpp
#define Dropdown_hpp

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include <leafy/UIElement.hpp>

#include <cmath>

namespace leafy
{

class LEAFY_API Dropdown 
    : public UIElement 
{
    public:
        
        Dropdown(const sf::Vector2f &size);
        ~Dropdown() = default;

        void setSize(const sf::Vector2f &size);
        void setPosition(const sf::Vector2f &position);

        const sf::Vector2f& getSize() const;
        const sf::Vector2f& getPosition() const;

        virtual bool contains(const sf::Vector2f& point) const override;
        void handleEvent(sf::RenderWindow&, sf::Event) override;
        void update(sf::Time delta_time) override;
    
    protected:

        void init();
        void updateGeometry();
        void flipTriangle();
        
        virtual void handleMouseButtonReleasedEvent(const sf::Vector2f& mouseButtonReleasedPosition) override;

        void draw(sf::RenderTarget&, sf::RenderStates) const override;
        
        void mouseEnter() override;
        void mouseLeave() override;
        void pressed() override;
        void clicked() override;

    private:

        sf::RectangleShape m_rect;
        sf::VertexArray    m_triangle;
        bool               m_open;
};

}

#endif /* Dropdown_hpp */
