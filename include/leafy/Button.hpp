//
//  Button.hpp
//  Leafly
//
//  Created by Austin Horn on 1/29/23.
//  Copyright © 2023 Austin Horn. All rights reserved.
//

#ifndef Button_hpp
#define Button_hpp

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <leafy/Interactable.hpp>
#include <leafy/Shapes/StadiumShape.hpp>
#include <leafy/Shapes/RoundedRectangleShape.hpp>

#include <algorithm>
#include <cmath>

template <typename T>
class LEAFY_API Button : public Interactable
{
public:
    
    explicit Button(const T& shape = T{});
    virtual ~Button();
    
    T* operator()() const
        { return m_shape; }
    void operator>>(const std::string& text)
        { m_text.setString(text); }

    virtual void mouseOver() override;
    virtual void mouseLeave() override;
    virtual bool clicked() const override;
    virtual bool contains(sf::Vector2f point) const override;
    virtual void handleEvent(sf::RenderWindow& window, sf::Event event) override;
    
private:
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    T*           m_shape;
    sf::Text     m_text;
    bool         m_clicked;
};

#endif /* Button_hpp */
