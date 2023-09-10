//
//  Screen.hpp
//  Leafy
//
//  Created by Austin Horn on 1/28/23.
//  Copyright © 2023 Austin Horn. All rights reserved.
//

#ifndef Screen_hpp
#define Screen_hpp

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <leafy/Engine/State.hpp>
#include <leafy/Button.hpp>

class LEAFY_API Screen final : public State
{
public:
    Screen(StateMachine& machine, sf::RenderWindow& window, Resources& resources, const bool replace = true);

    void pause() override;
    void resume() override;
    void handleEvent() override;
    void update() override;
    void draw() override;
    
private:
    
    sf::RectangleShape m_background;
    sf::Vector2f       m_current_mouse_position;
};


#endif /* Screen_hpp */