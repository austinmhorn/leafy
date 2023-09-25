#include <leafy/Button.hpp>

///////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief Constructor
///
/// \param shape Derived sf::Shape object; required [even if shape is disabled] to deduce T
///////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
Button<T>::Button(const T& shape)
    : m_shape( shape )
    , m_text( "", Resources::Sansation, 30 )
    , m_position( shape.getPosition() )
    , m_size( sf::Vector2f{shape.getGlobalBounds().width, shape.getGlobalBounds().height} )
    , m_mouseOver( false )
    , m_clicked( false )
    , m_needsUpdate( false )
    , m_drawShape( true )
    , m_clickPressInBounds( false ) 
    , m_translucentHover( true )
    , m_alignment( TextAlignment::Centered )
{
    m_funcs.clear();
}

template <typename T>
bool Button<T>::clicked() const
{
    return m_clicked;
}

template <typename T>
bool Button<T>::contains(sf::Vector2f point) const
{
    return ( m_drawShape ) ? m_shape.getGlobalBounds().contains(point) : m_text.getGlobalBounds().contains(point);
}

template <typename T>
void Button<T>::mouseClick() 
{
    // Only call if assigned
    if ( m_clicked && m_funcs[Function::ClickedOn] )
        m_funcs[Function::ClickedOn]();
    else if ( !m_clicked && m_funcs[Function::ClickedOff] )
        m_funcs[Function::ClickedOff]();
}

template <typename T>
void Button<T>::mouseOver()
{
    // Only call if assigned
    if ( m_funcs[Function::MouseOver] ) 
         m_funcs[Function::MouseOver]();
    if ( m_translucentHover )
    {
        const sf::Color shapeColor = m_shape.getFillColor();
        const sf::Color textColor = m_text.getFillColor();

        if ( m_drawShape )
        {
            m_shape.setFillColor({shapeColor.r, shapeColor.g, shapeColor.b, static_cast<sf::Uint8>(shapeColor.a/2)});
            m_text.setFillColor({textColor.r, textColor.g, textColor.b, static_cast<sf::Uint8>(textColor.a/2)});
        }
        else
        {
            m_text.setFillColor({textColor.r, textColor.g, textColor.b, static_cast<sf::Uint8>(textColor.a/2)});
        }
    }
}

template <typename T>
void Button<T>::mouseLeave()
{
    // Only call if assigned
    if ( m_funcs[Function::MouseLeave] ) 
         m_funcs[Function::MouseLeave]();

    if ( m_translucentHover )
    {
        const sf::Color shapeColor = m_shape.getFillColor();
        const sf::Color textColor = m_text.getFillColor();

        if ( m_drawShape )
        {
            m_shape.setFillColor({shapeColor.r, shapeColor.g, shapeColor.b, 255});
            m_text.setFillColor({textColor.r, textColor.g, textColor.b, 255});
        }
        else
        {
            m_text.setFillColor({textColor.r, textColor.g, textColor.b, 255});
        }
    }
}

template <typename T>
void Button<T>::handleEvent(sf::RenderWindow &window, sf::Event event)
{
    sf::Vector2f mouse_move = window.mapPixelToCoords({event.mouseMove.x, event.mouseMove.y});
    sf::Vector2f mouse_btn = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
    
    switch (event.type)
    {
        case sf::Event::MouseMoved:
            // Update button with new mouse position
            handleMouseMoveEvent(mouse_move);
            break;
        case sf::Event::MouseButtonPressed:
            // Allows for only processing a click release event if the press originated within bounds of the button
            handleMouseButtonPressedEvent(mouse_btn);
            break;
        case sf::Event::MouseButtonReleased:
                        
            handleMouseButtonReleasedEvent(mouse_btn);
            break;
        default:
            break;
    }
}

template <typename T>
void Button<T>::handleMouseMoveEvent(const sf::Vector2f& mousePosition)
{
    if ( contains( mousePosition ) )
    {
        if ( !m_mouseOver )
        {
            m_mouseOver = true;
            m_needsUpdate = true;
        }
    }
    else
    {
        if ( m_mouseOver )
        {
            m_mouseOver = false;
            m_needsUpdate = true;
        }
    }

    if ( m_needsUpdate )
    {
        m_needsUpdate = false;
        (m_mouseOver) ?  mouseOver() : mouseLeave();
    }
}

template <typename T>
void Button<T>::handleMouseButtonPressedEvent(const sf::Vector2f& mouseButtonPressedPosition)
{
    m_clickPressInBounds = contains(mouseButtonPressedPosition);
}

template <typename T>
void Button<T>::handleMouseButtonReleasedEvent(const sf::Vector2f& mouseButtonReleasedPosition)
{
    if ( m_mouseOver && contains(mouseButtonReleasedPosition) )
    {
        m_clicked = !m_clicked;
    }
    else
    {
        m_clicked = false;
    }

    if ( m_clickPressInBounds && m_mouseOver )
        mouseClick();
}

template <typename T>
void Button<T>::setPosition(const sf::Vector2f& position)
{
    m_position = position;
    m_shape.setPosition(position);
    updateAlignment();
}


template <typename T>
void Button<T>::setShapeFillColor(const sf::Color& color) 
{
    m_shape.setFillColor(color);
}

template <typename T>
void Button<T>::setShapeOutlineColor(const sf::Color& color) 
{
    m_shape.setOutlineColor(color);
}

template <typename T>
void Button<T>::setShapeOutlineThickness(float thickness)
{
    m_shape.setOutlineThickness(thickness);
    updateAlignment();
}

template <typename T>
void Button<T>::setWillDrawShape(bool willDraw)
{
    m_drawShape = willDraw;
}

template <typename T>
void Button<T>::setTextString(const std::string& string)
{
    m_text.setString(string);
    updateAlignment();
}

template <typename T>
void Button<T>::setTextFillColor(const sf::Color& color)
{
    m_text.setFillColor(color);
}

template <typename T>
void Button<T>::setMouseOverFunction(std::function<void()> function)
{
    m_funcs[Function::MouseOver] = function;
}

template <typename T>
void Button<T>::setMouseLeaveFunction(std::function<void()> function)
{
    m_funcs[Function::MouseLeave] = function;
}

template <typename T>
void Button<T>::setMouseClickOnFunction(std::function<void()> function)
{
    m_funcs[Function::ClickedOn] = function;
}

template <typename T>
void Button<T>::setMouseClickOffFunction(std::function<void()> function)
{
    m_funcs[Function::ClickedOff] = function;
}


template <typename T>
const sf::Vector2f& Button<T>::getSize() const
{
    return m_size;
}


template <typename T>
float Button<T>::getRadius() const
{
    return m_size.x * 0.5f;
}



template <typename T>
void Button<T>::updateAlignment()
{    
    const sf::Vector2f pos = m_position;
    const sf::Vector2f sz = m_size;
    const sf::Vector2f midpoint = {pos.x + sz.x/2.f, pos.y + sz.y/2.f};
    const float diffY = m_text.getCharacterSize() - m_text.getGlobalBounds().height;

    switch ( m_alignment )
    {
    case TextAlignment::Centered:
        m_text.setPosition({midpoint.x - m_text.getGlobalBounds().width/2.f, midpoint.y - m_text.getGlobalBounds().height*0.5f - m_shape.getOutlineThickness() - diffY});
        break;
    
    default:
        break;
    }
}

template <typename T>
void Button<T>::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.texture = &m_texture;
    
    if ( m_drawShape )
        target.draw(m_shape, states);
    if ( !m_text.getString().isEmpty() )
        target.draw(m_text);
}






///////////////////////////////////////////////////////
/// @brief Explicit template function instantiations 
///////////////////////////////////////////////////////

template <>
void Button<sf::RectangleShape>::setSize(const sf::Vector2f& size)
{
    m_size = size;
    m_shape.setSize(size);
    //update();
}
template <>
void Button<sf::RoundedRectangleShape>::setSize(const sf::Vector2f& size)
{
    m_size = size;
    m_shape.setSize(size);
    //update();
}
template <>
void Button<sf::StadiumShape>::setSize(const sf::Vector2f& size)
{
    m_size = size;
    m_shape.setSize(size);
    //update();
}

template <>
void Button<sf::CircleShape>::setRadius(float radius)
{
    m_size = sf::Vector2f(radius*2.f, radius*2.f);
    m_shape.setRadius(radius);
}

template <>
void Button<sf::PolygonShape>::setRadius(const sf::Vector2f& radius)
{
    m_size = sf::Vector2f(radius.x*2.f, radius.y*2.f);
    m_shape.setRadius(radius);
}


//////////////////////////////////////////////////
/// @brief Explicit template class instantiations 
//////////////////////////////////////////////////

template class Button<sf::RectangleShape>;
template class Button<sf::CircleShape>;
template class Button<sf::PolygonShape>;
template class Button<sf::RoundedRectangleShape>;
template class Button<sf::StadiumShape>;