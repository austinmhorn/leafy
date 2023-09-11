//
//  SmartMouse.hpp
//  leafy
//
//  Created by Austin Horn on 1/29/23.
//  Copyright © 2023 Austin Horn. All rights reserved.
//

#ifndef SmartCursor_hpp
#define SmartCursor_hpp

#include <SFML/Window/Cursor.hpp>
#include <SFML/Window/Export.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <iostream>

class SmartMouse : public sf::Cursor
{
public:
    
    enum class Pointer : unsigned
    {
        Arrow      =  0,
        Text       =  1,
        Hand       =  2,
        Cross      =  3,
        NotAllowed =  4,        

        ///< Keep last -- indicates # of enumerations
        Count = 5
    };
    
public:
    
    SmartMouse();
    ~SmartMouse();
    
    void create(sf::RenderWindow* window, Pointer pointer);
    void setPointer(Pointer pointer);
    void handleEvent(sf::Event event);
    void reset();
    
    const bool& getLmbReleased() const;
    const bool& getRmbReleased() const;
    
private:
            
    void assignWindow(sf::RenderWindow* window);
    void assignCursorToWindow();
    const void init();
    
private:
    
    sf::Cursor Arrow;
    sf::Cursor Text;
    sf::Cursor Hand;
    sf::Cursor Cross;
    sf::Cursor NotAllowed;
    
private:
    
    sf::RenderWindow* m_window;
    sf::Drawable*     m_held;
    Pointer           m_pointer;
    sf::Vector2f      m_position;
    bool              m_lmb_released;
    bool              m_rmb_released;
};



#endif /* SmartCursor_hpp */
