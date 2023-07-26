//
//  Application.hpp
//  LockedInside
//
//  Created by Austin Horn on 9/30/22.
//  Copyright © 2022 Austin Horn. All rights reserved.
//

#ifndef Application_hpp
#define Application_hpp

#include "../State/Base/StateMachine.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

#include "Resources.hpp"
#include "../SystemInfo.hpp"

class Application
{
public:
    
    Application(unsigned int window_width, unsigned int window_height, const std::string& title, sf::Uint32 style=sf::Style::Default, const sf::ContextSettings& settings=sf::ContextSettings());
    virtual ~Application() = default;
    
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;
    
    Application(Application&&) noexcept = delete;
    Application& operator=(Application&&) noexcept = delete;

    virtual void run();
    
protected:
    
    virtual void init();
    virtual void loadResources();

private:

    StateMachine     m_machine;
    sf::RenderWindow m_window;
    Resources        m_resources;
};


#endif /* Application_hpp */
