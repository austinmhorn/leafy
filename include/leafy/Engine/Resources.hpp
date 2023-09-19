//
//  Resources.hpp
//  leafy
//
//  Created by Austin Horn on 9/30/22.
//  Copyright © 2022 Austin Horn. All rights reserved.
//

#ifndef Assets_hpp
#define Assets_hpp

#include <SFML/Graphics.hpp>

#include <iostream>   // std::cin, std::cout
#include <new>        // std::bad_alloc
#include <cmath>      // std::ceil, std::log
#include <map>
#include <filesystem> // std::filesystem::path
#include <cassert>    // assert

#include <leafy/SmartMouse.hpp>

static const std::filesystem::path __filepath_icon      = "examples/data/images/icon.png";
static const std::filesystem::path __filepath_Sansation = "examples/data/fonts/sansation.ttf";

static void init_icon(sf::RenderWindow* window) {
    static sf::Image icon;
    assert(icon.loadFromFile(__filepath_icon));
    window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}



////////////////////////////////////////////////////////////
/// \namespace Fonts
///
/// \brief
////////////////////////////////////////////////////////////
namespace Fonts {
    static const sf::Font __init_Sansation() {
        static sf::Font font;
        assert(font.loadFromFile(__filepath_Sansation));
        return font;
    }

} // MARK: End of namespace 'Font'




////////////////////////////////////////////////////////////
/// \namespace Textures
///
/// \brief
////////////////////////////////////////////////////////////
namespace Textures {
/*
     static const std::basic_string<char> path_to_texture = "filepath/to/texture.png";

     static sf::Texture init_texture() {
        static sf::Texture texture;
        try {
            if ( !texture.loadFromFile(path_to_texture) )
                throw std::runtime_error("Failed loading texture " + path_to_texture);
        }
        catch(const std::runtime_error &e) {
            std::cerr << "std::runtime_error::what(): " << e.what() << std::endl;
        }
        return texture;
    }
*/
} // MARK: End of namespace 'Textures'

struct Resources
{
    static const sf::Font Sansation;
    
    static const sf::Color Gray;
    static const sf::Color DarkGreen;
    static const sf::Color DarkRed;
    static const sf::Color DarkPurple;
    static const sf::Color LightBlue;
    static const sf::Color Seafoam;
    static const sf::Color LightGreen;
    static const sf::Color Peach;
    static const sf::Color Tan;
    static const sf::Color Pink;
    static const sf::Color LightPurple;
    static const sf::Color Orange;
    static const sf::Color DarkBlue;

    static SmartMouse smartmouse;
};

#endif /* Assets_hpp */
