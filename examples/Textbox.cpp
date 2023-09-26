#include <SFML/Graphics.hpp>
#include <leafy/Textbox.hpp>

int main(int argc, char const **argv)
{
    sf::RenderWindow window = sf::RenderWindow{sf::VideoMode(800, 600), "Textbox Demo", sf::Style::Close};
    const auto window_size = sf::Vector2f{ window.getSize() };

    sf::RectangleShape background;
    background.setSize(window_size);
    background.setFillColor({32, 32, 32});

    Textbox textbox = Textbox(window);
    textbox.setPosition({window_size.x/2.f - textbox.getSize().x/2.f, window_size.y/2.f - textbox.getSize().y/2.f});

    // Start the game loop
    while (window.isOpen())  
    {
        for (auto event = sf::Event{}; window.pollEvent(event);) 
        {
            textbox.handleEvent(window, event);

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

        textbox.update(delta_time);

        window.clear();
        window.draw(background);
        window.draw(textbox);
        window.display();
    }

    return EXIT_SUCCESS;
}
