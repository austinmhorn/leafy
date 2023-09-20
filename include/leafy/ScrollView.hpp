//
//  ScrollView.hpp
//  leafy
//
//  Created by Austin Horn on 1/28/23.
//  Copyright © 2023 Austin Horn. All rights reserved.
//

#ifndef ScrollView_hpp
#define ScrollView_hpp

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <leafy/Engine/Resources.hpp>
#include <leafy/Interactable.hpp>

class LEAFY_API ScrollView : public Interactable
{
public:

    ScrollView(sf::RenderWindow& window, const sf::Texture& texture);

    const sf::Vector2f &getSize() const;

    virtual void handleEvent(sf::RenderWindow& window, sf::Event event) override;
    
private:

    void handleResizeEvent(const sf::Vector2f& newSize);

    virtual void mouseOver() override;
    virtual void mouseLeave() override;
    virtual bool clicked() const override;
    virtual bool contains(sf::Vector2f point) const override;
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:

    sf::RenderWindow&  m_window;
    sf::Vector2f       m_windowSize;

    sf::View           m_view;
    sf::FloatRect      m_viewport;

    sf::FloatRect      m_viewportBounds;
    sf::Vector2f       m_viewCenterStart;
    sf::Vector2f       m_viewCenterEnd;

    sf::FloatRect      m_fbounds;
    sf::IntRect        m_ibounds;
    const sf::Texture* m_texture; 
    sf::Sprite         m_sprite;

    sf::Vector2f       m_size;

};


#endif /* ScrollView_hpp */