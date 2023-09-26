//
//  Application.cpp
//  leafy
//
//  Created by Austin Horn on 9/30/22.
//  Copyright © 2022 Austin Horn. All rights reserved.
//
#include <cassert> 

#include <leafy/Engine/Application.hpp>

namespace leafy
{

Application::Application(unsigned int               window_width,
                         unsigned int               window_height,
                         const std::string&         title,
                         sf::Uint32                 style,
                         const sf::ContextSettings& settings)
    : m_window(sf::VideoMode(window_width, window_height), title, style, settings)
{
    init();
}

void Application::init()
{
    m_window.setFramerateLimit(30);
    
    loadResources();
    
    unsigned int width = 0;
    unsigned int height = 0;
    getScreenResolution(width, height);

    m_machine.init( StateMachine::build<IntroState>(m_machine, m_window, m_resources, true) );    
}

void Application::run()
{
    // Main loop
    while (m_machine.running())
    {
        m_machine.nextState();
        m_machine.update();
        m_machine.draw();
    }
}

void Application::loadResources()
{
    // Load icon
    init_icon(&m_window);
}

}