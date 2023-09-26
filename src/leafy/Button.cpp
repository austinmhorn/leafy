#include <leafy/Button.hpp>

namespace leafy
{

template <typename T>
Button<T>::Button(const T& shape)
    : m_shape( shape )
    , m_text( "", Resources::Sansation, 30 )
    , m_drawShape( true )
    , m_translucentHover( true )
    , m_alignment( TextAlignment::Centered )
{
    // Verify T is a derived sf::Shape object; required [even if not drawing shape] to deduce T
    static_assert(std::is_base_of<sf::Shape, typename std::remove_reference<T>::type>::value, "T must be a derived class of sf::Shape.");

    // Reset function map
    m_funcs.clear();

    // Extract size & position from shape parameter
    m_size = sf::Vector2f{shape.getGlobalBounds().width, shape.getGlobalBounds().height};
    m_position = m_shape.getPosition();
}

template <typename T>
bool Button<T>::contains(const sf::Vector2f& point) const
{
    return ( m_drawShape ) 
        ? m_shape.getGlobalBounds().contains(point) 
        : m_text.getGlobalBounds().contains(point);
}

template <typename T>
void Button<T>::mouseClick() 
{
    // Only call if assigned
    if ( clicked() && m_funcs[Function::ClickedOn] )
        m_funcs[Function::ClickedOn]();
    else if ( !clicked() && m_funcs[Function::ClickedOff] )
        m_funcs[Function::ClickedOff]();
}

template <typename T>
void Button<T>::mouseEnter()
{
    // Only call if assigned
    if ( m_funcs[Function::MouseEnter] ) 
         m_funcs[Function::MouseEnter]();
    
    // Halve the current fill color's alpha value 
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
    switch (event.type)
    {
        case sf::Event::MouseMoved:
            refreshBase(window, event);
            //std::cout << event.mouseMove.x << ", " << event.mouseMove.y << std::endl;
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

template <typename T>
void Button<T>::setPosition(const sf::Vector2f& position)
{
    m_position = position;
    m_shape.setPosition(position);
    updateAlignment();
}

template <typename T>
const sf::Vector2f& Button<T>::getPosition() const
{
    return m_shape.getPosition();
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
    updateAlignment();
}

template <typename T>
void Button<T>::setTextString(const std::string& string)
{
    m_text.setString(string);
    updateAlignment();
}

template <typename T>
void Button<T>::setNumberTextLines(unsigned int lines)
{
}

template <typename T>
void Button<T>::setTextFillColor(const sf::Color& color)
{
    m_text.setFillColor(color);
}

template <typename T>
void Button<T>::setMouseEnterFunction(std::function<void()> function)
{
    m_funcs[Function::MouseEnter] = function;
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
const sf::Vector2f& Button<T>::getPolygonRadius() const
{
    return UIElement::getPolygonRadius();
}

template <typename T>
void Button<T>::updateAlignment()
{    
    // Downsize from default text character size if shape's height < 60
    if ( 0.f < m_size.y && m_size.y < 60.f )
        m_text.setCharacterSize( m_size.y/2.f );

    // Difference between text rectangle height and character pixel size 
    const float diffY = m_text.getCharacterSize() - m_text.getGlobalBounds().height;
    // Contains the global coordinate center point for the shape
    sf::Vector2f midpoint;

    // Provides the member typedef type which is the type referred to by T. Otherwise type is T.
    using type_t = typename std::remove_reference<T>::type;

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
                m_text.setPosition( midpoint.x - m_text.getGlobalBounds().width/2.f, midpoint.y - m_text.getGlobalBounds().height/2.f - m_shape.getOutlineThickness() - (0.75*diffY) );
            else 
                m_text.setPosition( midpoint.x - m_text.getGlobalBounds().width/2.f, midpoint.y - m_text.getGlobalBounds().height/2.f - m_shape.getOutlineThickness() - diffY );
            break;
        case TextAlignment::Top:
            break;
        case TextAlignment::Right:
            break;
        case TextAlignment::Bottom:
            break;
        case TextAlignment::Left:
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
    UIElement::setSize( size );
    m_shape.setSize( m_size );
    updateAlignment();
}
template <>
void Button<sf::RoundedRectangleShape>::setSize(const sf::Vector2f& size)
{
    UIElement::setSize( size );
    m_shape.setSize( m_size );
    updateAlignment();
}
template <>
void Button<sf::StadiumShape>::setSize(const sf::Vector2f& size)
{
    UIElement::setSize( size );
    m_shape.setSize( m_size );
    updateAlignment();
}

template <>
void Button<sf::CircleShape>::setRadius(float radius)
{
    UIElement::setRadius( radius );
    m_shape.setRadius( m_size.x );
    updateAlignment();
}

template <>
void Button<sf::PolygonShape>::setPolygonRadius(const sf::Vector2f& radius)
{
    UIElement::setPolygonRadius( radius );
    m_shape.setRadius( m_size );
    updateAlignment();
}

template <>
const sf::Vector2f& Button<sf::RectangleShape>::getSize() const
{
    return UIElement::getSize();
}
template <>
const sf::Vector2f& Button<sf::RoundedRectangleShape>::getSize() const
{
    return UIElement::getSize();
}
template <>
const sf::Vector2f& Button<sf::StadiumShape>::getSize() const
{
    return UIElement::getSize();
}

template <>
float Button<sf::CircleShape>::getRadius() const
{
    return UIElement::getRadius();
}

template <>
const sf::Vector2f& Button<sf::PolygonShape>::getPolygonRadius() const
{
    return UIElement::getPolygonRadius();
}

//////////////////////////////////////////////////
/// @brief Explicit template class instantiations
//////////////////////////////////////////////////

template class LEAFY_API Button<sf::RectangleShape>;
template class LEAFY_API Button<sf::CircleShape>;
template class LEAFY_API Button<sf::PolygonShape>;
template class LEAFY_API Button<sf::RoundedRectangleShape>;
template class LEAFY_API Button<sf::StadiumShape>;

}
