//
//  Button.hpp
//  Textbox
//
//  Created by Austin Horn on 1/29/23.
//  Copyright © 2023 Austin Horn. All rights reserved.
//

#ifndef Button_hpp
#define Button_hpp

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "Base/Interactable.hpp"

#include <algorithm>
#include <cmath>

static float length(const sf::Vector2f& normal)
{
    return std::sqrt(normal.x * normal.x + normal.y * normal.y);
}

static sf::Vector2f perpendicular(const sf::Vector2f& vector)
{
    return sf::Vector2f(-vector.y, vector.x);
}


static sf::Vector2f computeNormal(const sf::Vector2f& p1, const sf::Vector2f& p2)
{
    sf::Vector2f diff = p2 - p1;
    sf::Vector2f normal = perpendicular(diff);
    const float  len = length(normal);
    if (len != 0.f)
        normal /= len;
    return normal;
}

static float cross(const sf::Vector2f& lhs, const sf::Vector2f& rhs)
{
    return lhs.x * rhs.y - lhs.y * rhs.x;
}

class Button : public sf::Shape
{
public:
    
    Button(const sf::Vector2f& radius = {0.f, 0.f}, float pointCount = 30.f);
    explicit Button(const sf::Shape& shape);
    
    void setRadius(const sf::Vector2f& radius);
    void setPointCount(float pointCount);
    
    const sf::Vector2f&  getRadius() const;
    virtual std::size_t  getPointCount() const;
    virtual sf::Vector2f getPoint(std::size_t index) const;
    
    virtual void handleEvent(sf::RenderWindow& window, sf::Event event);
    
    void setTexture(const sf::Texture* texture, bool resetRect = false);
    void setTextureRect(const sf::IntRect& rect);
    void setFillColor(const sf::Color& color);
    void setOutlineColor(const sf::Color& color);
    void setOutlineThickness(float thickness);

    const sf::Texture* getTexture() const;
    const sf::IntRect& getTextureRect() const;
    const sf::Color& getFillColor() const;
    const sf::Color& getOutlineColor() const;
    float getOutlineThickness() const;
    sf::Vector2f getGeometricCenter() const;
    sf::FloatRect getLocalBounds() const;
    sf::FloatRect getGlobalBounds() const;

protected:
    
    const bool   contains(const sf::Vector2f& mousePos) const;
    const bool   clicked() const;
    virtual void mouseOver();
    virtual void mouseLeave();
    
private:

    sf::Vector2f       m_radius;
    std::size_t        m_pointCount;
    bool               m_clicked;
    sf::Color          m_fillColor;
    sf::Color          m_outlineColor;
    const sf::Texture* m_texture;          ///< Texture of the shape
    sf::IntRect        m_textureRect;      ///< Rectangle defining the area of the source texture to display
    float              m_outlineThickness; ///< Thickness of the shape's outline
    sf::VertexArray    m_vertices;         ///< Vertex array containing the fill geometry
    sf::VertexArray    m_outlineVertices;  ///< Vertex array containing the outline geometry
    sf::FloatRect      m_insideBounds;     ///< Bounding rectangle of the inside (fill)
    sf::FloatRect      m_bounds;           ///< Bounding rectangle of the whole shape (outline + fill)
};

#endif /* Button_hpp */
