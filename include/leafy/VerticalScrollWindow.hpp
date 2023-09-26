//
//  VerticalScrollWindow.hpp
//  leafy
//
//  Created by Austin Horn on 1/28/23.
//  Copyright © 2023 Austin Horn. All rights reserved.
//

#ifndef VerticalScrollWindow_hpp
#define VerticalScrollWindow_hpp

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <leafy/UIElement.hpp>

class LEAFY_API VerticalScrollWindow 
    : public UIElement
{
    public:

        VerticalScrollWindow(sf::RenderWindow& window, const sf::Texture& texture, const sf::FloatRect& viewport = {0.f, 0.f, 1.f, 1.f});

        const sf::Vector2f &getSize() const;

        virtual void handleEvent(sf::RenderWindow& window, sf::Event event) override;
        
    protected:

        void handleMouseVerticalWheelScrollEvent(float delta_scroll);
        void handleResizeEvent(const sf::Vector2f& new_size);
        void updateView(float resize_factor = 1.f);

        virtual void mouseClick() override;
        virtual void mouseEnter() override;
        virtual void mouseLeave() override;
        virtual bool contains(const sf::Vector2f& point) const override;
        
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    private:

        sf::RenderWindow&  m_window;
        sf::Vector2f       m_prevWindowSize;
        sf::Vector2f       m_currWindowSize;
        const sf::Texture* m_texture; 
        sf::View           m_view;
        sf::FloatRect      m_viewport;
        sf::Sprite         m_sprite;
        sf::FloatRect      m_viewportBounds;
        sf::Vector2f       m_viewCenterStart;
        sf::Vector2f       m_viewCenterEnd;
        sf::FloatRect      m_textureBounds;

};


#endif /* VerticalScrollWindow_hpp */