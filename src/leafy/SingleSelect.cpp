#include <leafy/SingleSelect.hpp>
#include <leafy/Engine/Resources.hpp>

static const float PADDING = 5.f;
static const float SPACING = 5.f;

SingleSelect::SingleSelect(float characterSize)
    : m_clicked(false)
    , m_activeColor({0, 100, 255, 255})
    , m_inactiveColor(sf::Color::White)
    , m_characterSize(characterSize)
{
    m_rect.setFillColor({73, 73, 73});
}
SingleSelect::~SingleSelect()
{
}
void SingleSelect::setPosition(const sf::Vector2f &position)
{
    m_rect.setPosition(position);
    updateGeometry();
}
void SingleSelect::addChoice(const std::string &choice)
{
    updateChoicesText(choice);
    resizeBox();
    updateGeometry();
}
const sf::Vector2f& SingleSelect::getSize() const
{
    return m_rect.getSize();
}
std::string SingleSelect::getSelection() const
{
    for ( auto & c: m_choices )
    {
        if ( c.first.getFillColor() == m_activeColor )
        {
            return c.second.getString();
        }
    }
    return "";
}
void SingleSelect::resizeBox()
{
    float widest = 0.f;

    for (int i = 0; i < m_choices.size(); i++)
    {
        // Get references to box & text members
        auto &box = m_choices.at(i).first;
        auto &text = m_choices.at(i).second;

        // Find longest [widest] choice string
        if ( text.getGlobalBounds().width > widest )
        {
            widest = text.getGlobalBounds().width;

            // Resize background rectangle
            m_rect.setSize( {widest + box.getGlobalBounds().width + (3.f * PADDING), (m_choices.size() * ((box.getGlobalBounds().height > text.getGlobalBounds().height) ? box.getGlobalBounds().height : text.getGlobalBounds().height)) + ((m_choices.size()+1) * PADDING) } );
        }
    }
}
void SingleSelect::updateChoicesText(const std::string &choice)
{
    // Create a new checkbox with text for the new choice
    auto text = sf::Text(choice, Resources::Sansation, m_characterSize);
    auto box = sf::RectangleShape({m_characterSize, m_characterSize});

    // Initially set to inactive color 
    box.setFillColor( m_inactiveColor );
    // Outline checkbox in black
    box.setOutlineThickness(1.f);
    box.setOutlineColor(sf::Color::Black);

    // Insert new pair into private vector data member
    m_choices.push_back(std::make_pair(box, text));
}

void SingleSelect::updateGeometry()
{
    auto rpos = m_rect.getPosition();
    
    for (int i = 0; i < m_choices.size(); i++)
    {
        auto &box = m_choices.at(i).first;
        auto &text = m_choices.at(i).second;

        box.setPosition(rpos.x + PADDING, rpos.y + PADDING + (i * box.getGlobalBounds().height) + (i * SPACING) );

        auto bpos = box.getPosition();

        text.setPosition(bpos.x + box.getGlobalBounds().width + PADDING, rpos.y + PADDING - m_characterSize/6.f + (i * box.getGlobalBounds().height) + (i * SPACING) );
    }

}
void SingleSelect::handleMouseButtonPressedEvent(sf::RenderWindow& window, sf::Event event)
{

}
void SingleSelect::handleMouseButtonReleasedEvent(sf::RenderWindow& window, sf::Event event)
{
    sf::Vector2f click_pos = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
    unsigned int numNotClicked = 0;
    std::string activeChoice = "";
    
    switch (event.mouseButton.button)
    {
        case sf::Mouse::Left:
            for (auto &c : m_choices)
            {
                // Track number of choices not clicked
                if ( !c.first.getGlobalBounds().contains(click_pos) )
                    numNotClicked++;

                // Check if this choice is currently active
                if ( c.first.getFillColor() == m_activeColor )
                    activeChoice = c.second.getString();

                if ( m_rect.getGlobalBounds().contains(click_pos) )
                {    
                    // Determine if a box was clicked and set fill color accordingly
                    if ( c.first.getGlobalBounds().contains(click_pos) )
                    {
                        // Invert fill color
                        if ( c.first.getFillColor() != m_activeColor )
                            c.first.setFillColor( m_activeColor );
                        else
                            c.first.setFillColor( m_inactiveColor );
                    }
                    else
                    {
                        // Set not clicked choice to inactive fill color
                        if ( c.first.getFillColor() == m_activeColor )
                            c.first.setFillColor( m_inactiveColor );
                    }
                }
            }

            // 
            if ( numNotClicked == m_choices.size() && !activeChoice.empty() )
                for (auto &c : m_choices)
                    if ( c.second.getString() == activeChoice )
                        c.first.setFillColor( m_activeColor );

            break;
                
        case sf::Mouse::Right:
            break;
                
        default:
            break;
    }
}
void SingleSelect::handleMouseMoveEvent(sf::RenderWindow& window, sf::Event event)
{
    sf::Vector2f mouse_move = window.mapPixelToCoords({event.mouseMove.x, event.mouseMove.y});
}
void SingleSelect::handleEvent(sf::RenderWindow& window, sf::Event event)
{
    switch (event.type)
    {            
        case sf::Event::MouseMoved:
            handleMouseMoveEvent(window, event);
            break;

        case sf::Event::MouseButtonPressed:
            handleMouseButtonPressedEvent(window, event);
            break;
            
        case sf::Event::MouseButtonReleased:
            handleMouseButtonReleasedEvent(window, event);
            break;
        
        case sf::Event::TextEntered:
            break;

        default:
            break;
    }
}
void SingleSelect::update(sf::Time delta_time)
{

}
void SingleSelect::mouseOver() 
{

}
void SingleSelect::mouseLeave() 
{

}
bool SingleSelect::clicked() const 
{
    return m_clicked;
}
bool SingleSelect::contains(sf::Vector2f point) const 
{
    return false;
}
void SingleSelect::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_rect);

    for (auto &c : m_choices)
    {
        target.draw(c.first);
        target.draw(c.second);
    }
}