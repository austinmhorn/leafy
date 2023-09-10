//
//  Application.hpp
//  Leafly
//
//  Created by Austin Horn on 9/30/22.
//  Copyright © 2022 Austin Horn. All rights reserved.
//

#ifndef Application_hpp
#define Application_hpp

#include <SFML/Graphics/RenderWindow.hpp>

#include <leafy/Engine/StateMachine.hpp>
#include <leafy/Engine/Resources.hpp>
#include <leafy/Engine/SystemInfo.hpp>
#include <leafy/Engine/Screen.hpp>


class LEAFY_API Application
{
public:
    
    Application(unsigned int window_width, unsigned int window_height, const std::string& title, sf::Uint32 style=sf::Style::Default, const sf::ContextSettings& settings=sf::ContextSettings());
    virtual ~Application() = default;
    
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;
    
    Application(Application&&) noexcept = delete;
    Application& operator=(Application&&) noexcept = delete;

    virtual void init();
    virtual void run();
    
protected:
    
    virtual void loadResources();

private:

    StateMachine     m_machine;
    sf::RenderWindow m_window;
    Resources        m_resources;
};


#endif /* Application_hpp */
