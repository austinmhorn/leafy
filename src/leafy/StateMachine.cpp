//
//  StateMachine.cpp
//  Leafly
//
//  Created by Austin Horn on 1/28/23.
//  Copyright © 2023 Austin Horn. All rights reserved.
//

#include <leafy/StateMachine.hpp>
#include <leafy/State.hpp>

#include <iostream>

StateMachine::StateMachine()
    : m_resume(false)
    , m_running(false)
{
    //std::cout << "StateMachine Init" << std::endl;
}

void StateMachine::init(std::unique_ptr<State> state)
{
    m_running = true;

    m_states.push(std::move(state));
}

void StateMachine::nextState()
{
    if (m_resume)
    {
        // Cleanup the current state
        if (!m_states.empty())
        {
            m_states.pop();
        }

        // Resume previous state
        if (!m_states.empty())
        {
            m_states.top()->resume();
        }

        m_resume = false;
    }

    // There needs to be a state
    if (!m_states.empty())
    {
        auto temp = m_states.top()->next();

        // Only change states if there's a next one existing
        if (temp != nullptr)
        {
            // Replace the running state
            if (temp->replace())
            {
                m_states.pop();
            }
            // Pause the running state
            else
            {
                m_states.top()->pause();
            }

            m_states.push(std::move(temp));
        }
    }
}

void StateMachine::lastState()
{
    m_resume = true;
}

void StateMachine::update()
{
    // Let the state update the game
    m_states.top()->update();
}

void StateMachine::draw()
{
    // Let the state draw the screen
    m_states.top()->draw();
}

bool StateMachine::running() const
{
    return m_running;
}

void StateMachine::quit()
{
    m_running = false;
}
