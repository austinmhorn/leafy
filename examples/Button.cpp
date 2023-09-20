#include <SFML/Graphics.hpp>
#include <leafy/Button.hpp>

int main(int argc, char const **argv)
{
    sf::RenderWindow window = sf::RenderWindow{sf::VideoMode(800, 600), "Button Demo", sf::Style::Close};
    const auto window_size = sf::Vector2f{ window.getSize() };

    Button stadiumButton = Button(sf::StadiumShape());
    
    stadiumButton()->setPosition(window_size.x/2.f - stadiumButton()->getGlobalBounds().width/2.f, window_size.y/2.f - stadiumButton()->getGlobalBounds().height/2.f);
    stadiumButton()->setFillColor(sf::Color::Blue);
    
    // Start the game loop
    while (window.isOpen())  
    {
        for (auto event = sf::Event{}; window.pollEvent(event);) 
        {
            // Update the button with event and window
            stadiumButton.handleEvent(window, event);

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
        window.draw(stadiumButton);
        window.display();
    }

    return EXIT_SUCCESS;
}
