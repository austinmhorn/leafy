#include <leafy/VerticalScrollWindow.hpp>
#include <leafy/Engine/Resources.hpp>

#include <cmath> // std::ceil()

namespace leafy
{

VerticalScrollWindow::VerticalScrollWindow(sf::RenderWindow& window, const sf::Texture& texture, const sf::FloatRect& viewport)
    : m_window( window )                                                                            // Explicitly initialize reference member 
    , m_prevWindowSize( window.getSize() )                                                          // Save window dimensions at time of creation 
    , m_currWindowSize( window.getSize().x * viewport.width, window.getSize().y * viewport.height ) // Calculate the size of the view using the ratio of the viewport to the window
    , m_texture( &texture )                                                                         // Point m_texture to the texture reference arguement
    , m_view( {0.f, 0.f, m_currWindowSize.x, m_currWindowSize.y} )                                  // Create a view the size of the window
    , m_viewport( viewport )                                                                        // Set viewport rectangle
    , m_sprite( *m_texture )                                                                        // Assign texture to sprite
{   
    // Fetch texture rectangle
    m_textureBounds = sf::FloatRect(0.f, 0.f, m_texture->getSize().x, m_texture->getSize().y);
    
    // Create a view the same size as the window it is referenced from
    m_view.setViewport(m_viewport);
    
    // Update view coordinate path system
    updateView();
}
const sf::Vector2f& VerticalScrollWindow::getSize() const
{
    return m_currWindowSize;
}
void VerticalScrollWindow::handleEvent(sf::RenderWindow& window, sf::Event event) 
{
    sf::Vector2f mouse_move = window.mapPixelToCoords({event.mouseMove.x, event.mouseMove.y});
    sf::Vector2f mouse_btn = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
    sf::Vector2f mouse_scroll = {static_cast<float>(event.mouseWheelScroll.x), static_cast<float>(event.mouseWheelScroll.y)};
    
    switch (event.type)
    {
        case sf::Event::MouseMoved:
            // Call mouse hover functions as appropriate
            refreshBase(window, event);
            break;
        case sf::Event::MouseButtonPressed:
            refreshBase(window, event);
            /// TODO: Add grab scrollbar
            break;
        case sf::Event::MouseButtonReleased: 
            refreshBase(window, event);
            /// TODO: Add release scrollbar    
            break;
        case sf::Event::MouseWheelScrolled:
            // VerticalScrollWindow objects only react to vertical wheel scroll events
            if ( event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel && contains(mouse_scroll) )  
                handleMouseVerticalWheelScrollEvent( event.mouseWheelScroll.delta );
            break;
        case sf::Event::Resized:
            // Fetch new window size and update geometry
            handleResizeEvent( {static_cast<float>(event.size.width), static_cast<float>(event.size.height)} );
            break;
        default:
            break;
    }
}
void VerticalScrollWindow::update(sf::Time delta_time)
{
}
void VerticalScrollWindow::handleMouseVerticalWheelScrollEvent(float delta_scroll)
{
    // Scrolling UP
    if ( delta_scroll > 0 )
    {
        // Only process scroll event if view is not at the top 
        if ( m_view.getCenter().y != m_viewCenterStart.y )
        {
            // Check if scrolled off the top of the screen, if not, move the view up
            if ( m_view.getCenter().y - m_view.getSize().y/2.f < 0.f )
                m_view.setCenter(m_viewCenterStart);
            else
                m_view.move(0.f, -std::ceil( delta_scroll ));
        }
    }
    // Scrolling DOWN
    else if ( delta_scroll < 0  )
    {
        // Only process scroll event if view is not at the bottom 
        if ( m_view.getCenter().y != m_viewCenterEnd.y )
        {
            // Check if scrolled off the bottom of the screen, if not, move the view down
            if ( m_view.getCenter().y > m_viewCenterEnd.y ) 
                m_view.setCenter(m_viewCenterEnd);
            else
                m_view.move(0.f, -std::ceil( delta_scroll ));
        }
    }
}
void VerticalScrollWindow::handleResizeEvent(const sf::Vector2f& new_size)
{
    // Fetch window size prior to resize event
    sf::Vector2f oldSize = m_prevWindowSize;
    // Calculate the delta change of resize event as a ratio 
    const sf::Vector2f deltaResize = {new_size.x / oldSize.x, new_size.y / oldSize.y};
    // Scale sprite respectively
    m_sprite.setScale(deltaResize.x, deltaResize.y);
    // Determine new visible area as a float rectangle
    sf::FloatRect visibleArea = sf::FloatRect{0.f, 0.f, new_size.x, new_size.y};

    // Assign new visible area to view
    m_view = sf::View(visibleArea);
    // Set the viewport
    m_view.setViewport(m_viewport);
    // Fetch and assign the new center point for the view
    m_view.setCenter(m_view.getCenter());

    // Update view coordinate path system
    updateView(deltaResize.y);

    // Track new window size
    m_currWindowSize = new_size;
}
void VerticalScrollWindow::updateView(float resize_factor)
{    
    // Calculate the VerticalScrollWindow's viewport global bounds
    m_viewportBounds = {m_view.getCenter().x - m_view.getSize().x/2.f, m_view.getCenter().y - m_view.getSize().y/2.f, m_view.getSize().x, m_view.getSize().y};
    // Determine the center coordinate for the top of the view || STOP point when scrolling UP
    m_viewCenterStart = m_view.getCenter();
    // Determine the center coordinate for the bottom of the view || STOP point when scrolling DOWN
    m_viewCenterEnd = { m_viewCenterStart.x, (m_texture->getSize().y * resize_factor) - m_view.getSize().y/2.f };
}
void VerticalScrollWindow::mouseEnter() 
{

}
void VerticalScrollWindow::mouseLeave() 
{

}
void VerticalScrollWindow::pressed() 
{

}
void VerticalScrollWindow::clicked()
{

}

bool VerticalScrollWindow::contains(const sf::Vector2f& point) const 
{
    return m_viewportBounds.contains(point);
}

void VerticalScrollWindow::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
    m_window.setView(m_view);

    target.draw(m_sprite);

    // Set the default view back
    m_window.setView(m_window.getDefaultView());
}

}