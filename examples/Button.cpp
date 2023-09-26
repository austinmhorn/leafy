#include <SFML/Graphics.hpp>

#include <leafy/Button.hpp>
using namespace leafy;

#include <iostream>

void customMouseEnterFunction()
{
    std::cout << "StadiumButton engaged -- performed callback to custom MouseEnter function" << std::endl;
}
void customMouseLeaveFunction()
{
    std::cout << "StadiumButton disengaged -- performed callback to custom MouseLeave function" << std::endl;
}
void customMouseClickOnFunction()
{
    std::cout << "StadiumButton ON -- performed callback to custom ClickedOn function" << std::endl;
}
void customMouseClickOffFunction()
{
    std::cout << "StadiumButton OFF -- performed callback to custom ClickedOff function" << std::endl;
}


int main(int argc, char const **argv)
{
    sf::RenderWindow window = sf::RenderWindow{sf::VideoMode(800, 600), "Button Demo", sf::Style::Close};
    window.setFramerateLimit(60);
    const auto window_size = sf::Vector2f{ window.getSize() };
    
    // Let this first Button instance serve as the "full-use" example,
    // as it is the only button connected with callback functions
    Button stadiumButton = Button(sf::StadiumShape()); // Demonstrates sf::StadiumShape compatability
    stadiumButton.setSize({300.f, 60.f});
    stadiumButton.setPosition({window_size.x - stadiumButton.getSize().x*1.25f, stadiumButton.getSize().y*0.25f});
    stadiumButton.setShapeFillColor(sf::Color::Red);
    stadiumButton.setShapeOutlineColor(sf::Color::White);
    stadiumButton.setShapeOutlineThickness(1.25f);
    stadiumButton.setTextString("Stadium Button");
    stadiumButton.setTextFillColor(sf::Color::White);
    // Connect callback functions to this button only
    stadiumButton.setMouseEnterFunction( customMouseEnterFunction );
    stadiumButton.setMouseLeaveFunction( customMouseLeaveFunction );
    stadiumButton.setMouseClickOnFunction( customMouseClickOnFunction );
    stadiumButton.setMouseClickOffFunction( customMouseClickOffFunction );

    Button rectButton = Button(sf::RectangleShape()); // Demonstrates sf::RectangleShape compatability
    rectButton.setSize({250.f, 100.f});
    rectButton.setPosition({window_size.x/2.f - rectButton.getSize().x/2.f, window_size.y/2.f - rectButton.getSize().y });
    rectButton.setShapeFillColor({72, 72, 72});
    rectButton.setShapeOutlineColor(sf::Color::White);
    rectButton.setShapeOutlineThickness(1.25f);
    rectButton.setTextString("Rectangle Button");
    rectButton.setTextFillColor(sf::Color::White);

    Button circleButton = Button(sf::CircleShape()); // Demonstrates sf::CircleShape compatability
    circleButton.setRadius(100.f);
    circleButton.setPosition( {0.f, 0.f} );
    circleButton.setShapeFillColor(sf::Color::Yellow);
    circleButton.setShapeOutlineColor(sf::Color::White);
    circleButton.setShapeOutlineThickness(1.25f);
    circleButton.setTextString("Circle");
    circleButton.setTextFillColor(sf::Color::Black);

    Button polygonButton = Button(sf::PolygonShape({0.f, 0.f}, 10.f)); // Demonstrates sf::PolygonShape compatability
    polygonButton.setPolygonRadius({150.f, 50.f});
    polygonButton.setPosition({polygonButton.getPolygonRadius().x*0.25f, window_size.y - 2.f*polygonButton.getPolygonRadius().y});
    polygonButton.setShapeFillColor(sf::Color::Blue);
    polygonButton.setShapeOutlineColor(sf::Color::White);
    polygonButton.setShapeOutlineThickness(1.25f);
    polygonButton.setTextString("Polygon");
    polygonButton.setTextFillColor(sf::Color::White);

    Button roundedRectButton = Button(sf::RoundedRectangleShape()); // Demonstrates sf::RoundedRectangleShape compatability
    roundedRectButton.setSize({300.f, 180.f});
    roundedRectButton.setPosition({window_size.x - roundedRectButton.getSize().x - 25.f, window_size.y - roundedRectButton.getSize().y - 25.f});
    roundedRectButton.setShapeFillColor({120, 120, 120});
    roundedRectButton.setShapeOutlineColor(sf::Color::White);
    roundedRectButton.setShapeOutlineThickness(1.25f);
    roundedRectButton.setTextString("Rounded Rectangle");
    roundedRectButton.setTextFillColor(sf::Color::White);

    while (window.isOpen())  
    {
        for (auto event = sf::Event{}; window.pollEvent(event);) 
        {
            // Simply provide a reference to the window and the event
            stadiumButton.handleEvent(window, event);
            rectButton.handleEvent(window, event);
            circleButton.handleEvent(window, event);
            polygonButton.handleEvent(window, event);
            roundedRectButton.handleEvent(window, event);

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
        window.draw(rectButton);
        window.draw(circleButton);
        window.draw(polygonButton);
        window.draw(roundedRectButton);
        window.display();
    }

    return EXIT_SUCCESS;
}
