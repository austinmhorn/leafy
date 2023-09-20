#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <leafy/ScrollView.hpp>

using namespace Textures; // See <leafy/Engine/Resources.hpp>

int main(int argc, char const **argv)
{
    sf::RenderWindow window = sf::RenderWindow{sf::VideoMode(800, 600), "ScrollView Demo", sf::Style::Close | sf::Style::Resize};
    window.setFramerateLimit(60);
    bool running = true;
    const auto window_size = sf::Vector2f{ window.getSize() };

    sf::Texture texture = __load_domino();

    ScrollView sv2(window, texture);


    // Start the game loop
    while (running)  
    {
        for (auto event = sf::Event{}; window.pollEvent(event);) 
        {
            //sv1.handleEvent(window, event);
            sv2.handleEvent(window, event);

            switch(event.type) 
            {
                case sf::Event::Closed:
                    running = false;
                break;

                default:
                break;
            }
        }

        window.clear();
        //window.draw(sv1);
        window.draw(sv2);
        window.display();
    }

    return EXIT_SUCCESS;
}
