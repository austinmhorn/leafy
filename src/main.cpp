#include "Core/Application.hpp"

int main(int argc, char const **argv)
{
    auto app = Application{800, 600, "SFAF Demo", sf::Style::Close};
    app.run();

    return EXIT_SUCCESS;
}

