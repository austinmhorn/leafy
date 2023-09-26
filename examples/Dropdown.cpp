#include <SFML/Graphics.hpp>
#include <leafy/Dropdown.hpp>
using namespace leafy;

int main(int argc, char const **argv)
{
    sf::RenderWindow window = sf::RenderWindow{sf::VideoMode(800, 600), "Dropdown Demo", sf::Style::Close};
    const auto window_size = sf::Vector2f{ window.getSize() };

    Dropdown dropdown1({120.f, 20.f});
    Dropdown dropdown2({200.f, 30.f});
    Dropdown dropdown3({350.f, 40.f});

    dropdown1.setPosition({window_size.x/2.f - dropdown1.getSize().x/2.f, window_size.y/2.f - 100.f});
    dropdown2.setPosition({window_size.x/2.f - dropdown2.getSize().x/2.f, window_size.y/2.f - dropdown2.getSize().y/2.f});
    dropdown3.setPosition({window_size.x/2.f - dropdown3.getSize().x/2.f, window_size.y/2.f + 100.f});
    
    // Start the game loop
    while (window.isOpen())  
    {
        for (auto event = sf::Event{}; window.pollEvent(event);) 
        {

            // Update the Dropdown with event and window
            dropdown1.handleEvent(window, event);
            dropdown2.handleEvent(window, event);
            dropdown3.handleEvent(window, event);

            switch(event.type) 
            {
                case sf::Event::Closed:
                    window.close();
                break;

                default:
                break;
            }
        }

        window.clear();
        window.draw(dropdown1);
        window.draw(dropdown2);
        window.draw(dropdown3);
        window.display();
    }

    return EXIT_SUCCESS;
}
