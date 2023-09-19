//
//  IntroState.cpp
//  leafy
//
//  Created by Austin Horn on 1/28/23.
//  Copyright © 2023 Austin Horn. All rights reserved.
//

#include <leafy/Engine/IntroState.hpp>
#include <leafy/Engine/StateMachine.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include <leafy/Engine/Resources.hpp>

#include <iostream>
#include <memory>

IntroState::IntroState(StateMachine& machine, sf::RenderWindow& window, Resources& resources, const bool replace)
    : State{ machine, window, resources, replace }
{
    const auto window_size = sf::Vector2f{ window.getSize() };
    
    // Fill the background with Gray
    m_background.setFillColor({100u, 100u, 100u});
    m_background.setSize(window_size);
}

void IntroState::pause()
{
    //std::cout << "IntroState Pause" << std::endl;;
}

void IntroState::resume()
{
    //std::cout << "IntroState Resume" << std::endl;;
}

void IntroState::handleEvent()
{
    for (auto event = sf::Event{}; m_window.pollEvent(event);)
    {        
        switch (event.type)
        {
            case sf::Event::Closed:
                m_machine.quit();
                break;
                
            case sf::Event::MouseMoved:
                ///< Get new mouse position
                m_current_mouse_position = m_window.mapPixelToCoords({ event.mouseMove.x, event.mouseMove.y });
                                    
                break;
                
            case sf::Event::MouseButtonPressed:
                ///< Get location for mouse button press event
                m_current_mouse_position = m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
                break;
                
            case sf::Event::MouseButtonReleased:
                ///< Get location for mouse button release event
                m_current_mouse_position = m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
                break;
                
            case sf::Event::KeyPressed:
                break;
                
            case sf::Event::TextEntered:
                break;
                
            default:
                break;
        }
        
        
    }
}

void IntroState::update()
{
    static const auto clock = sf::Clock{};
    static auto last_frame_time = sf::Time{};
    const auto delta_time = clock.getElapsedTime() - last_frame_time;
    last_frame_time = clock.getElapsedTime();
    
    handleEvent();
}

void IntroState::draw()
{
    m_window.clear();
    
    m_window.draw(m_background);

    m_window.display();
}
