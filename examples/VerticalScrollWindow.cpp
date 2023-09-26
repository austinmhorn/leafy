#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <leafy/VerticalScrollWindow.hpp>
#include <leafy/Engine/Resources.hpp> // Textures::__load_domino()

using namespace Textures; // __load_domino()

int main(int argc, char const **argv)
{
    sf::RenderWindow window = sf::RenderWindow{sf::VideoMode(800, 600), "Vertical Scroll Window Demo", sf::Style::Default};
    window.setFramerateLimit(60);

    // Load texture image
    const sf::Texture texture = __load_domino();
    
    // Create instance of a vertical scroll window 
    VerticalScrollWindow vertScrollWin(window, texture);

    // Start the game loop
    while (window.isOpen())  
    {
        for (auto event = sf::Event{}; window.pollEvent(event);) 
        {
            vertScrollWin.handleEvent(window, event);

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
        window.draw(vertScrollWin);
        window.display();
    }

    return EXIT_SUCCESS;
}
