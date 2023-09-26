#include <SFML/Graphics.hpp>
#include <leafy/Checkbox.hpp>

#include <iostream>

int main(int argc, char const **argv)
{
    sf::RenderWindow window = sf::RenderWindow{sf::VideoMode(800, 600), "Checkbox Demo", sf::Style::Close};
    const auto window_size = sf::Vector2f{ window.getSize() };

    Checkbox checkbox1(15.f, true);
    Checkbox checkbox2(24.f);
    Checkbox checkbox3(30.f);

    checkbox1.setPosition({window_size.x/2.f, window_size.y/2.f - 200.f});
    checkbox1.addChoice("Choice 1");
    checkbox1.addChoice("Choice 2");
    checkbox1.addChoice("A long string for Choice 3");

    checkbox2.setPosition({window_size.x/4.f, window_size.y/2.f - 50.f});
    checkbox2.addChoice("On");
    checkbox2.addChoice("Off");

    checkbox3.setPosition({window_size.x/2.f, window_size.y/2.f + 100.f});
    checkbox3.addChoice("Low");
    checkbox3.addChoice("Medium");
    checkbox3.addChoice("High");
    checkbox3.addChoice("Very High");

    // Start the game loop
    while (window.isOpen())  
    {
        for (auto event = sf::Event{}; window.pollEvent(event);) 
        {
            checkbox1.handleEvent(window, event);
            checkbox2.handleEvent(window, event);
            checkbox3.handleEvent(window, event);

            switch(event.type) 
            {
                case sf::Event::Closed:
                    window.close();
                break;

                default:
                break;
            }
        }

        static const auto clock = sf::Clock{};
        static auto last_frame_time = sf::Time{};
        const auto delta_time = clock.getElapsedTime() - last_frame_time;
        last_frame_time = clock.getElapsedTime();

        // Print choice string of active selection for each Checkbox object
        for ( auto &s : checkbox1.getSelection() )
        {
            std::cout << "checkbox1: " << s << std::endl;
        }
        for ( auto &s : checkbox2.getSelection() )
        {
            std::cout << "checkbox2: " << s << std::endl;
        }
        for ( auto &s : checkbox3.getSelection() )
        {
            std::cout << "checkbox3: " << s << std::endl;
        }

        window.clear();
        window.draw(checkbox1);
        window.draw(checkbox2);
        window.draw(checkbox3);
        window.display();
    }

    return EXIT_SUCCESS;
}
