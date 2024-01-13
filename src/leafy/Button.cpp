#include <leafy/Button.hpp>

namespace leafy
{
/*
template <typename _Shape>
Button<_Shape>::Button()
    : m_shape(  )
    , m_label( "", Resources::Sansation, 30 )
    , m_drawShape( true )
    , m_translucentHover( true )
    , m_alignment( TextAlignment::Centered )
{
    // Reset function map
    m_funcs.clear();

    // Extract size & position from shape parameter
    m_size = sf::Vector2f{m_shape.getGlobalBounds().width, m_shape.getGlobalBounds().height};
    m_position = m_shape.getPosition();
}
*/
template <typename _Shape>
Button<_Shape>::Button(const _Shape& shape)
    : m_shape( shape )
    , m_label( "", Resources::Sansation, 30 )
    , m_drawShape( true )
    , m_translucentHover( true )
    , m_alignment( TextAlignment::Centered )
{
    // Reset function map
    m_funcs.clear();

    // Extract size & position from shape parameter
    m_size = sf::Vector2f{shape.getGlobalBounds().width, shape.getGlobalBounds().height};
    m_position = m_shape.getPosition();
}


template <typename _Shape>
bool Button<_Shape>::contains(const sf::Vector2f& point) const
{
    return ( m_drawShape ) 
        ? m_shape.getGlobalBounds().contains(point) 
        : m_label.getGlobalBounds().contains(point);
}

template <typename _Shape>
void Button<_Shape>::pressed() 
{
    if ( m_drawShape )
    {
        m_shape.setOutlineThickness(m_shape.getOutlineThickness() + 2.f);

    }
}

template <typename _Shape>
void Button<_Shape>::clicked() 
{
    // Only call if assigned
    if ( !m_active  &&  m_funcs[Function::ClickedOn] )
        m_funcs[Function::ClickedOn]();
    else if ( m_active  &&  m_funcs[Function::ClickedOff] )
        m_funcs[Function::ClickedOff]();

    if ( m_drawShape )
    {
        m_shape.setOutlineThickness(m_shape.getOutlineThickness() - 2.f);
    }
}

template <typename _Shape>
void Button<_Shape>::mouseEnter()
{
    // Only call if assigned
    if ( m_funcs[Function::MouseEnter] ) 
         m_funcs[Function::MouseEnter]();
    
    // Halve the current fill color's alpha value 
    if ( m_translucentHover )
    {
        const sf::Color shapeColor = m_shape.getFillColor();
        const sf::Color textColor = m_label.getFillColor();

        if ( m_drawShape )
        {
            m_shape.setFillColor({shapeColor.r, shapeColor.g, shapeColor.b, static_cast<sf::Uint8>(shapeColor.a/2)});
            m_label.setFillColor({textColor.r, textColor.g, textColor.b, static_cast<sf::Uint8>(textColor.a/2)});
        }
        else
        {
            m_label.setFillColor({textColor.r, textColor.g, textColor.b, static_cast<sf::Uint8>(textColor.a/2)});
        }
    }
}

template <typename _Shape>
void Button<_Shape>::mouseLeave()
{
    // Only call if assigned
    if ( m_funcs[Function::MouseLeave] ) 
         m_funcs[Function::MouseLeave]();

    if ( m_translucentHover )
    {
        const sf::Color shapeColor = m_shape.getFillColor();
        const sf::Color textColor = m_label.getFillColor();

        if ( m_drawShape )
        {
            m_shape.setFillColor({shapeColor.r, shapeColor.g, shapeColor.b, 255});
            m_label.setFillColor({textColor.r, textColor.g, textColor.b, 255});
        }
        else
        {
            m_label.setFillColor({textColor.r, textColor.g, textColor.b, 255});
        }
    }
}

template <typename _Shape>
void Button<_Shape>::handleEvent(sf::RenderWindow &window, sf::Event event)
{   
    switch (event.type)
    {
        case sf::Event::MouseMoved:
            refreshBase(window, event);
            break;
        case sf::Event::MouseButtonPressed:
            refreshBase(window, event);
            break;
        case sf::Event::MouseButtonReleased:                        
            refreshBase(window, event);
            break;
        default:
            break;
    }
}


template <typename _Shape>
void Button<_Shape>::update(sf::Time delta_time) 
{   
}

template <typename _Shape>
void Button<_Shape>::setPosition(const sf::Vector2f& position)
{
    m_position = position;
    m_shape.setPosition(position);
    updateAlignment();
}

template <typename _Shape>
const sf::Vector2f& Button<_Shape>::getPosition() const
{
    return m_shape.getPosition();
}

template <typename _Shape>
void Button<_Shape>::setShapeFillColor(const sf::Color& color) 
{
    m_shape.setFillColor(color);
}

template <typename _Shape>
void Button<_Shape>::setShapeOutlineColor(const sf::Color& color) 
{
    m_shape.setOutlineColor(color);
}

template <typename _Shape>
void Button<_Shape>::setShapeOutlineThickness(float thickness)
{
    m_shape.setOutlineThickness(thickness);
    updateAlignment();
}

template <typename _Shape>
void Button<_Shape>::setDrawShape(bool willDraw)
{
    m_drawShape = willDraw;
    updateAlignment();
}

template <typename _Shape>
void Button<_Shape>::setLabelString(const std::string& string)
{
    m_label.setString(string);
    updateAlignment();
}

template <typename _Shape>
void Button<_Shape>::setNumberLabelLines(unsigned int lines)
{
}

template <typename _Shape>
void Button<_Shape>::setTextFillColor(const sf::Color& color)
{
    m_label.setFillColor(color);
}

template <typename _Shape>
void Button<_Shape>::setMouseEnterFunction(std::function<void()> function)
{
    m_funcs[Function::MouseEnter] = function;
}

template <typename _Shape>
void Button<_Shape>::setMouseLeaveFunction(std::function<void()> function)
{
    m_funcs[Function::MouseLeave] = function;
}

template <typename _Shape>
void Button<_Shape>::setMouseClickOnFunction(std::function<void()> function)
{
    m_funcs[Function::ClickedOn] = function;
}

template <typename _Shape>
void Button<_Shape>::setMouseClickOffFunction(std::function<void()> function)
{
    m_funcs[Function::ClickedOff] = function;
}

template <typename _Shape>
void Button<_Shape>::updateAlignment()
{    
    // Downsize from default text character size if shape's height < 60
    if ( 0.f < m_size.y && m_size.y < 60.f )
        m_label.setCharacterSize( m_size.y/2.f );

    // Difference between text rectangle height and character pixel size 
    const float diffY = m_label.getCharacterSize() - m_label.getGlobalBounds().height;
    // Contains the global coordinate center point for the shape
    sf::Vector2f midpoint;

    // Provides the member typedef type which is the type referred to by _Shape. Otherwise type is _Shape.
    using type_t = typename std::remove_reference<_Shape>::type;

    // Determine geometric type
    bool isRect = (std::is_same<sf::RectangleShape, type_t>::value || std::is_same<sf::RoundedRectangleShape, type_t>::value);
    bool isStad = std::is_same<sf::StadiumShape, type_t>::value;
    bool isCirc = std::is_same<sf::CircleShape, type_t>::value;   
    bool isPoly = std::is_same<sf::PolygonShape, type_t>::value;

    switch ( m_alignment )
    {
        default:
        case TextAlignment::Centered:
            // Determine shape midpoint
            if ( isRect || isStad ) // Position text in a shape with width and height geometry
                midpoint = {m_position.x + m_size.x/2.f, m_position.y + m_size.y/2.f};
            else if ( isCirc ) // Position text in a shape with circlular radial geometry
                midpoint = {2.f*(m_position.x + m_size.x/2.f), 2.f*(m_position.y + m_size.y/2.f)};
            else if ( isPoly ) // Otherwise, position text in a shape with convex polygon geometry
                midpoint = {m_position.x + m_size.x, m_position.y + m_size.y};

            // Set text position
            if ( isStad ) // Positioning in a stadium shape requires unique vertical displacement 
                m_label.setPosition( midpoint.x - m_label.getGlobalBounds().width/2.f, midpoint.y - m_label.getGlobalBounds().height/2.f - m_shape.getOutlineThickness() - (0.75*diffY) );
            else 
                m_label.setPosition( midpoint.x - m_label.getGlobalBounds().width/2.f, midpoint.y - m_label.getGlobalBounds().height/2.f - m_shape.getOutlineThickness() - diffY );
            break;
        case TextAlignment::Top:
            /// TODO: Align at top
            break;
        case TextAlignment::Right:
            /// TODO: Align at right
            break;
        case TextAlignment::Bottom:
            /// TODO: Align at bottom
            break;
        case TextAlignment::Left:
            /// TODO: Align at left
            break;
    }
    
}

template <typename _Shape>
void Button<_Shape>::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.texture = &m_texture;
    
    if ( m_drawShape )
        target.draw(m_shape, states);
    if ( !m_label.getString().isEmpty() )
        target.draw(m_label);
}




////////////////////////////////////////////////////////
/// @brief Explicit template class instantiations 
////////////////////////////////////////////////////////

template class LEAFY_API Button<typename sf::RectangleShape>;
template class LEAFY_API Button<typename sf::CircleShape>;
template class LEAFY_API Button<typename sf::PolygonShape>;
template class LEAFY_API Button<typename sf::RoundedRectangleShape>;
template class LEAFY_API Button<typename sf::StadiumShape>;

}