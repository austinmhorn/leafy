#include <SFML/Graphics.hpp>
#include <leafy/SingleSelect.hpp>

#include <iostream>

int main(int argc, char const **argv)
{
    sf::RenderWindow window = sf::RenderWindow{sf::VideoMode(800, 600), "SingleSelect Demo", sf::Style::Close};
    bool running = true;
    const auto window_size = sf::Vector2f{ window.getSize() };

    SingleSelect ss1(15.f);
    SingleSelect ss2(24.f);
    SingleSelect ss3(30.f);

    ss1.setPosition({window_size.x/2.f, window_size.y/2.f - 200.f});
    ss1.addChoice("Choice 1");
    ss1.addChoice("Choice 2");
    ss1.addChoice("A long string for Choice 3");

    ss2.setPosition({window_size.x/4.f, window_size.y/2.f - 50.f});
    ss2.addChoice("On");
    ss2.addChoice("Off");

    ss3.setPosition({window_size.x/2.f, window_size.y/2.f + 100.f});
    ss3.addChoice("Low");
    ss3.addChoice("Medium");
    ss3.addChoice("High");
    ss3.addChoice("Very High");

    // Start the game loop
    while (running)  
    {
        for (auto event = sf::Event{}; window.pollEvent(event);) 
        {
            ss1.handleEvent(window, event);
            ss2.handleEvent(window, event);
            ss3.handleEvent(window, event);

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

        // Print choice string of active selection for each SingleSelect object
        if ( ss1.getSelection() != "" )
        {
            std::cout << "ss1: " << ss1.getSelection() << std::endl;
        }
        if ( ss2.getSelection() != "" )
        {
            std::cout << "ss2: " << ss2.getSelection() << std::endl;
        }
        if ( ss3.getSelection() != "" )
        {
            std::cout << "ss3: " << ss3.getSelection() << std::endl;
        }

        window.clear();
        window.draw(ss1);
        window.draw(ss2);
        window.draw(ss3);
        window.display();
    }

    return EXIT_SUCCESS;
}
