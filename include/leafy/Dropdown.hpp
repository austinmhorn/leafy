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

#include <leafy/Interactable.hpp>

#include <cmath>

class LEAFY_API Dropdown : public Interactable {
public:
    
    Dropdown(const sf::Vector2f &size);
    ~Dropdown() = default;

    void setSize(const sf::Vector2f &size);
    void setPosition(const sf::Vector2f &position);

    const sf::Vector2f& getSize() const;
    const sf::Vector2f& getPosition() const;

    // Overidden purely virtual methods from parent class Interactable 
    bool clicked() const override;
    bool contains(sf::Vector2f point) const override;
    void mouseOver() override;
    void mouseLeave() override;
    void handleEvent(sf::RenderWindow&, sf::Event) override;
    void update(sf::Time delta_time) override;
  
protected:

    void init();
    void updateGeometry();
    void flipTriangle();
    
    void handleMouseButtonPressedEvent(sf::RenderWindow&, sf::Event);
    void handleMouseButtonReleasedEvent(sf::RenderWindow&, sf::Event);
    void handleMouseMoveEvent(sf::RenderWindow&, sf::Event);

    void draw(sf::RenderTarget&, sf::RenderStates) const override;
    
private:

    sf::RectangleShape m_rect;
    sf::VertexArray    m_triangle;
    bool               m_open;
};

#endif /* Dropdown_hpp */
