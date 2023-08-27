//
//  IntroState.hpp
//  Leafly
//
//  Created by Austin Horn on 1/28/23.
//  Copyright © 2023 Austin Horn. All rights reserved.
//

#ifndef IntroState_hpp
#define IntroState_hpp

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <leafy/State.hpp>
#include <leafy/Button.hpp>

struct Resources;

class LEAFY_API IntroState final : public State
{
public:
    IntroState(StateMachine& machine, sf::RenderWindow& window, Resources& resources, const bool replace = true);

    void pause() override;
    void resume() override;
    void handleEvent() override;
    void update() override;
    void draw() override;
    
private:
    
    sf::RectangleShape m_background;
    sf::Vector2f       m_current_mouse_position;
    
    Button<sf::StadiumShape> stadiumButton;
};


#endif /* IntroState_hpp */
