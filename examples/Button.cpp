#include <SFML/Graphics.hpp>

#include <leafy/Button.hpp>
#include <leafy/Shapes/StadiumShape.hpp>

void customMouseOverFunction()
{
    std::cout << "Mouse entered bounds of button" << std::endl;
}

void customMouseLeaveFunction()
{
    std::cout << "Mouse exited bounds of button" << std::endl;
}

void customMouseClickOnFunction()
{
    std::cout << "Button activated" << std::endl;
}

void customMouseClickOffFunction()
{
    std::cout << "Button deactivated" << std::endl;
}


int main(int argc, char const **argv)
{
    sf::RenderWindow window = sf::RenderWindow{sf::VideoMode(800, 600), "Button Demo", sf::Style::Close};
    window.setFramerateLimit(60);
    const auto window_size = sf::Vector2f{ window.getSize() };

    Button stadiumButton = Button(sf::StadiumShape());
    stadiumButton.setSize({200.f, 40.f});
    
    stadiumButton.setPosition({window_size.x/2.f - stadiumButton.getSize().x/2.f, 40.f});
    stadiumButton.setShapeFillColor(sf::Color::Red);
    stadiumButton.setShapeOutlineColor(sf::Color::White);
    stadiumButton.setShapeOutlineThickness(1.25f);
    stadiumButton.setTextString("Button");
    stadiumButton.setTextFillColor(sf::Color::White);
    stadiumButton.setMouseOverFunction( customMouseOverFunction );
    stadiumButton.setMouseLeaveFunction( customMouseLeaveFunction );
    stadiumButton.setMouseClickOnFunction( customMouseClickOnFunction );
    stadiumButton.setMouseClickOffFunction( customMouseClickOffFunction );

    Button biggerButton = Button(sf::StadiumShape());
    biggerButton.setSize({300.f, 60.f});
    biggerButton.setPosition({window_size.x/2.f - biggerButton.getSize().x/2.f, window_size.y/2.f - biggerButton.getSize().y/2.f});
    biggerButton.setShapeFillColor({72, 72, 72});
    biggerButton.setShapeOutlineColor(sf::Color::White);
    biggerButton.setShapeOutlineThickness(1.25f);
    biggerButton.setTextString("Bigger Button");
    biggerButton.setTextFillColor(sf::Color::White);

    // Start the game loop
    while (window.isOpen())  
    {
        for (auto event = sf::Event{}; window.pollEvent(event);) 
        {
            stadiumButton.handleEvent(window, event);
            biggerButton.handleEvent(window, event);

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
        window.draw(biggerButton);
        window.display();
    }

    return EXIT_SUCCESS;
}
