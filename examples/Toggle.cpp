#include <SFML/Window/Event.hpp>
#include <leafy/Toggle.hpp>

int main(int argc, char const **argv)
{
    sf::RenderWindow window = sf::RenderWindow{sf::VideoMode(800, 600), "Toggle Demo", sf::Style::Close};
    window.setFramerateLimit(60);
    bool running = true;
    const auto window_size = sf::Vector2f{ window.getSize() };

    Toggle toggle = Toggle(false, sf::Vector2f(80.f, 30.f));
    Toggle toggle2 = Toggle(false, sf::Vector2f(160.f, 40.f));
    Toggle toggle3 = Toggle(false, sf::Vector2f(240.f, 50.f));
    Toggle toggle4 = Toggle(false, sf::Vector2f(320.f, 60.f));

    // Set toggle positions
    toggle.setPosition({window_size.x/2.f - toggle.getSize().x/2.f, (window_size.y/2.f) - 200.f});
    toggle.setTextSide(Toggle::Left);
    toggle.setDescription("Tiny toggle description on the LEFT");

    toggle2.setPosition({window_size.x/2.f - toggle2.getSize().x/2.f, window_size.y/2.f - 100.f});
    toggle2.setTextSide(Toggle::Right);
    toggle2.setDescription("Small toggle description on the RIGHT");

    toggle3.setPosition({window_size.x/2.f - toggle3.getSize().x/2.f, window_size.y/2.f + 20.f});
    toggle3.setTextSide(Toggle::Top);
    toggle3.setDescription("Medium toggle description on the TOP"); 

    toggle4.setPosition({window_size.x/2.f - toggle4.getSize().x/2.f, window_size.y/2.f + 100.f + toggle4.getSize().y});
    toggle4.setTextSide(Toggle::Bottom);
    toggle4.setDescription("Large toggle description on the BOTTOM"); 

    // Start the game loop
    while (running) 
    {
        for (auto event = sf::Event{}; window.pollEvent(event);) 
        {
            // Update the toggles with event and window
            toggle.handleEvent(window, event);
            toggle2.handleEvent(window, event);
            toggle3.handleEvent(window, event);
            toggle4.handleEvent(window, event);

            switch(event.type) 
            {
                case sf::Event::Closed:
                    running = false;
                break;

                default:
                break;
            }
        }

        static const auto clock = sf::Clock{};
        static auto last_frame_time = sf::Time{};
        const auto delta_time = clock.getElapsedTime() - last_frame_time;
        last_frame_time = clock.getElapsedTime();

        toggle.update(delta_time);
        toggle2.update(delta_time);
        toggle3.update(delta_time);
        toggle4.update(delta_time);

        window.clear();
        window.draw(toggle);
        window.draw(toggle2);
        window.draw(toggle3);
        window.draw(toggle4);
        window.display();
    }

    return EXIT_SUCCESS;
}
