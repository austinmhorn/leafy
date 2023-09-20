#include <leafy/ScrollView.hpp>

#include <cmath>

ScrollView::ScrollView(sf::RenderWindow& window, const sf::Texture& texture)
    : m_window( window )
    , m_windowSize( window.getSize() )
    , m_texture(&texture)
    , m_viewport( sf::FloatRect{0.f, 0.f, 1.f, 1.f} )
    , m_size( window.getSize() )
{    


    m_fbounds = sf::FloatRect(0.f, 0.f, m_texture->getSize().x, m_texture->getSize().y);
    m_ibounds = sf::IntRect(m_fbounds);

    m_sprite.setTexture(*m_texture);

    m_view = sf::View(sf::FloatRect(0.f, 0.f, m_size.x, m_size.y));
    m_view.setViewport(m_viewport);

    m_viewportBounds = {m_view.getCenter().x - m_view.getSize().x/2.f, m_view.getCenter().y - m_view.getSize().y/2.f, m_view.getSize().x, m_view.getSize().y};

    m_viewCenterStart = m_view.getCenter();
    m_viewCenterEnd = { m_viewCenterStart.x, m_texture->getSize().y - m_view.getSize().y/2.f };
    
}
const sf::Vector2f& ScrollView::getSize() const
{
    
}
void ScrollView::handleEvent(sf::RenderWindow& window, sf::Event event) 
{
    sf::Vector2f mouse_move = window.mapPixelToCoords({event.mouseMove.x, event.mouseMove.y});
    sf::Vector2f mouse_btn = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
    sf::Vector2f mouse_scroll = {static_cast<float>(event.mouseWheelScroll.x), static_cast<float>(event.mouseWheelScroll.y)};
    
    switch (event.type)
    {
        case sf::Event::MouseMoved:
            
            contains(mouse_move) ? mouseOver() : mouseLeave();
            
            break;
        case sf::Event::MouseButtonReleased:
            
            std::cout << "CLICK AT: " << mouse_btn.x << ", " << mouse_btn.y << std::endl;
            if (contains(mouse_btn))
            {
                std::cout << "clicked" << std::endl;
                
            }
            
            break;
            
        case sf::Event::MouseWheelScrolled:

            if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) 
            {
                if ( contains(mouse_scroll) )
                {
                    if ( event.mouseWheelScroll.delta > 0 ) // Scroll UP
                    {
                        if ( m_view.getCenter().y == m_viewCenterStart.y )
                            break;
                        else if ( m_view.getCenter().y - m_view.getSize().y/2.f < 0.f )
                            m_view.setCenter(m_viewCenterStart);
                        else
                            m_view.move(0.f, -std::ceil(event.mouseWheelScroll.delta));
                    }
                    else if ( event.mouseWheelScroll.delta < 0  ) // Scroll DOWN
                    {
                        if ( m_view.getCenter().y == m_viewCenterEnd.y )
                            break;
                        else if ( m_view.getCenter().y > m_viewCenterEnd.y )
                            m_view.setCenter(m_viewCenterEnd);
                        else
                            m_view.move(0.f, -std::ceil(event.mouseWheelScroll.delta));
                    }

                }
            }
            else if (event.mouseWheelScroll.wheel == sf::Mouse::HorizontalWheel) 
            {}
            else 
            {}

            break;

        case sf::Event::Resized:
            handleResizeEvent( {static_cast<float>(event.size.width), static_cast<float>(event.size.height)} );
            break;

        default:
            break;
    }

}
void ScrollView::handleResizeEvent(const sf::Vector2f& newSize)
{
    sf::Vector2f oldSize = m_windowSize;
    const sf::Vector2f delta_resize = {newSize.x / oldSize.x, newSize.y / oldSize.y};

    m_sprite.setScale(delta_resize.x, delta_resize.y);

    sf::FloatRect visibleArea = sf::FloatRect{0.f, 0.f, newSize.x, newSize.y};
    m_view = sf::View(visibleArea);
    m_view.setViewport(m_viewport);
    m_view.setCenter(m_view.getCenter());
    m_viewportBounds = {m_view.getCenter().x - m_view.getSize().x/2.f, m_view.getCenter().y - m_view.getSize().y/2.f, m_view.getSize().x, m_view.getSize().y};
    m_viewCenterStart = m_view.getCenter();
    m_viewCenterEnd = { m_viewCenterStart.x, (m_texture->getSize().y * delta_resize.y) - m_view.getSize().y/2.f };
}
void ScrollView::mouseOver() 
{

}
void ScrollView::mouseLeave() 
{

}
bool ScrollView::clicked() const 
{
    return false;
}
bool ScrollView::contains(sf::Vector2f point) const 
{
    return m_viewportBounds.contains(point);
}

void ScrollView::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
    m_window.setView(m_view);

    target.draw(m_sprite);

    // Set the default view back
    m_window.setView(m_window.getDefaultView());
}