#include <SFML/Graphics.hpp>
#include <leafy/Slider.hpp>
using namespace leafy;

int main(int argc, char const **argv)
{
    sf::RenderWindow window = sf::RenderWindow{sf::VideoMode(800, 600), "Slider Demo", sf::Style::Close};
    const auto window_size = sf::Vector2f{ window.getSize() };

    Slider slider({100.f, 4.f}, 25);
    Slider slider2({180.f, 5.f}, 50);
    Slider slider3({250.f, 6.f}, 75);
    Slider slider4({310.f, 7.f}, 100);

    slider.setPosition({window_size.x/2.f - slider.getSize().x/2.f, window_size.y/2.f - 150.f - slider.getSize().y/2.f});
    slider2.setPosition({window_size.x/2.f - slider2.getSize().x/2.f, window_size.y/2.f - 60.f - slider2.getSize().y/2.f});
    slider3.setPosition({window_size.x/2.f - slider3.getSize().x/2.f, window_size.y/2.f + 30.f + slider3.getSize().y/2.f});
    slider4.setPosition({window_size.x/2.f - slider4.getSize().x/2.f, window_size.y/2.f + 150.f + slider4.getSize().y/2.f});

    slider.setDescription("Tiny Slider with description on TOP");
    slider2.setDescription("Small Slider with description on TOP");
    slider3.setDescription("Medium Slider with description on TOP");
    slider4.setDescription("Large Slider with description on TOP");
    
    // Start the game loop
    while (window.isOpen())  
    {
        for (auto event = sf::Event{}; window.pollEvent(event);) 
        {
            slider.handleEvent(window, event);
            slider2.handleEvent(window, event);
            slider3.handleEvent(window, event);
            slider4.handleEvent(window, event);

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

        slider.update(delta_time);
        slider2.update(delta_time);
        slider3.update(delta_time);
        slider4.update(delta_time);
        
        window.clear();
        window.draw(slider);
        window.draw(slider2);
        window.draw(slider3);
        window.draw(slider4);
        window.display();
    }

    return EXIT_SUCCESS;
}
