
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>

#include <leafy/Engine/Application.hpp>
#include <leafy/Toggle.hpp>

#include <iostream>
#include <memory>

struct Resources;

class LEAFY_API IntroState final : public State
{
public:
    
    IntroState(StateMachine& machine, sf::RenderWindow& window, Resources& resources, const bool replace)
        : State{ machine, window, resources, replace }
        , m_toggle(false, sf::Vector2f(80.f, 30.f))
        , m_toggle_2(false, sf::Vector2f(160.f, 40.f))
        , m_toggle_3(false, sf::Vector2f(240.f, 50.f))
        , m_toggle_4(false, sf::Vector2f(320.f, 60.f))
    {
        const auto window_size = sf::Vector2f{ window.getSize() };
    
        // Fill the background with Gray
        m_background.setFillColor({100u, 100u, 100u});
        m_background.setSize(window_size);

        // Set toggle positions
        m_toggle.setPosition({window_size.x/2.f - m_toggle.getSize().x/2.f, (window_size.y/2.f) - 200.f});
        m_toggle.setTextSide(Toggle::Left);
        m_toggle.setDescription("Tiny toggle description on the Top");

        m_toggle_2.setPosition({window_size.x/2.f - m_toggle_2.getSize().x/2.f, window_size.y/2.f - 100.f});
        m_toggle_2.setTextSide(Toggle::Right);
        m_toggle_2.setDescription("Small toggle description on the Right");

        m_toggle_3.setPosition({window_size.x/2.f - m_toggle_3.getSize().x/2.f, window_size.y/2.f + 20.f});
        m_toggle_3.setTextSide(Toggle::Top);
        m_toggle_3.setDescription("Medium toggle description on the Top"); 

        m_toggle_4.setPosition({window_size.x/2.f - m_toggle_4.getSize().x/2.f, window_size.y/2.f + 100.f + m_toggle_4.getSize().y});
        m_toggle_4.setTextSide(Toggle::Bottom);
        m_toggle_4.setDescription("Large toggle description on the Bottom"); 
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
            m_toggle.handleEvent(m_window, event);
            m_toggle_2.handleEvent(m_window, event);
            m_toggle_3.handleEvent(m_window, event);
            m_toggle_4.handleEvent(m_window, event);
            
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
        
        m_toggle.update(delta_time);
        m_toggle_2.update(delta_time);
        m_toggle_3.update(delta_time);
        m_toggle_4.update(delta_time);
    }

    void draw()
    {
        m_window.clear();
        m_window.draw(m_background);
        m_window.draw(m_toggle);
        m_window.draw(m_toggle_2);
        m_window.draw(m_toggle_3);
        m_window.draw(m_toggle_4);
        m_window.display();
    }
    
private:
    
    sf::RectangleShape m_background;
    sf::Vector2f       m_current_mouse_position;
    Toggle             m_toggle;
    Toggle             m_toggle_2;
    Toggle             m_toggle_3;
    Toggle             m_toggle_4;
};

int main(int argc, char const **argv)
{
    auto app = Application{800, 600, "Toggle Demo", sf::Style::Close};

    app.getMachine().init(StateMachine::build<IntroState>(app.getMachine(), app.getWindow(), app.getResources(), true));

    app.run();

    return EXIT_SUCCESS;
}

