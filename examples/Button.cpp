#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>

#include <leafy/Engine/Application.hpp>
#include <leafy/Button.hpp>

#include <iostream>
#include <memory>

struct Resources;

class LEAFY_API IntroState final : public State
{
public:
    
    IntroState(StateMachine& machine, sf::RenderWindow& window, Resources& resources, const bool replace)
        : State{ machine, window, resources, replace }
        , stadiumButton(sf::StadiumShape())
    {
        const auto window_size = sf::Vector2f{ window.getSize() };
        
        // Fill the background with Gray
        m_background.setFillColor({100u, 100u, 100u});
        m_background.setSize(window_size);
        
        stadiumButton()->setFillColor(sf::Color::Blue);
        stadiumButton()->setPosition(window_size.x/2.f - stadiumButton()->getGlobalBounds().width/2.f, window_size.y/2.f - stadiumButton()->getGlobalBounds().height/2.f);
    }

    void pause()
    {
        //std::cout << "IntroState Pause" << std::endl;;
    }

    void resume()
    {
        //std::cout << "IntroState Resume" << std::endl;;
    }

    void handleEvent()
    {
        for (auto event = sf::Event{}; m_window.pollEvent(event);)
        {
            stadiumButton.handleEvent(m_window, event);
            
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

    void update()
    {
        static const auto clock = sf::Clock{};
        static auto last_frame_time = sf::Time{};
        const auto delta_time = clock.getElapsedTime() - last_frame_time;
        last_frame_time = clock.getElapsedTime();
        
        handleEvent();
    }

    void draw()
    {
        m_window.clear();
        m_window.draw(m_background);
        m_window.draw(stadiumButton);
        m_window.display();
    }
        
private:
        
        sf::RectangleShape       m_background;
        sf::Vector2f             m_current_mouse_position;
    
        Button<sf::StadiumShape> stadiumButton;
};

int main(int argc, char const **argv)
{
    auto app = Application{800, 600, "Button Demo", sf::Style::Close};

    app.getMachine().init(StateMachine::build<IntroState>(app.getMachine(), app.getWindow(), app.getResources(), true));

    app.run();

    return EXIT_SUCCESS;
}

