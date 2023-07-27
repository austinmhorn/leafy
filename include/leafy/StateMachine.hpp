//
//  StateMachine.hpp
//  Leafly
//
//  Created by Austin Horn on 1/28/23.
//  Copyright © 2023 Austin Horn. All rights reserved.
//

#ifndef StateMachine_hpp
#define StateMachine_hpp

#include <leafy/State.hpp>

#include <iostream>
#include <memory>
#include <stack>
#include <stdexcept>

namespace sf
{
    class RenderWindow;
}

class StateMachine
{
public:
    StateMachine();
    virtual ~StateMachine() = default;
    
    StateMachine(const StateMachine&) = delete;
    StateMachine& operator=(const StateMachine&) = delete;
    
    StateMachine(StateMachine&&) noexcept = delete;
    StateMachine& operator=(StateMachine&&) noexcept = delete;

    void init(std::unique_ptr<State> state);

    void nextState();
    void lastState();

    void update();
    void draw();

    [[nodiscard]] bool running() const;
    void quit();

    template <typename T>
    static std::unique_ptr<T> build(StateMachine& machine, sf::RenderWindow& window, Resources& resources, bool replace = true);

private:
    // The stack of states
    std::stack<std::unique_ptr<State>> m_states;

    bool m_resume;
    bool m_running;
};







////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
std::unique_ptr<T> StateMachine::build(StateMachine& machine, sf::RenderWindow& window, Resources& resources, bool replace)
{
    auto new_state = std::unique_ptr<T>{ nullptr };

    try
    {
        new_state = std::make_unique<T>(machine, window, resources, replace);
    }
    catch(std::runtime_error& exception)
    {
        std::cout << "Creation of new state was unsuccessful\n";
        std::cout << exception.what() << std::endl;
    }

    return new_state;
}


#endif /* StateMachine_hpp */
