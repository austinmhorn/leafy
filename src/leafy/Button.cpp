//
//  Button.cpp
//  Leafly
//
//  Created by Austin Horn on 1/29/23.
//  Copyright © 2023 Austin Horn. All rights reserved.
//

#include <leafy/Button.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <cassert>

#ifndef _PI
#define _PI 3.14159265358979323846
#endif

Button::Button(const sf::Vector2f& radius, float pointCount)
    : m_radius(radius)
    , m_pointCount(pointCount)
    , m_clicked(false)
{
    Shape::update();
}
Button::Button(const sf::Shape& shape)
    : m_radius(sf::Vector2f{shape.getGlobalBounds().width, shape.getGlobalBounds().height})
    , m_pointCount(shape.getPointCount())
    , m_clicked(false)
{
    Shape::update();
}
void Button::setRadius(const sf::Vector2f& radius)
{
    m_radius = radius;
    Shape::update();
}
void Button::setPointCount(float pointCount)
{
    m_pointCount = pointCount;
    Shape::update();
}
const sf::Vector2f& Button::getRadius() const
{
    return m_radius;
}
const bool Button::contains(const sf::Vector2f& mousePos) const
{
    return Button::getGlobalBounds().contains(mousePos);
}
const bool Button::clicked() const
{
    return m_clicked;
}
std::size_t Button::getPointCount() const
{
    return m_pointCount;
}
sf::Vector2f Button::getPoint(std::size_t index) const
{
    float angle = index * 2 * _PI / getPointCount() - _PI / 2;
    float x = std::cos(angle) * m_radius.x;
    float y = std::sin(angle) * m_radius.y;
    return sf::Vector2f(m_radius.x + x, m_radius.y + y);
}
void Button::mouseOver()
{
    Button::setFillColor({Button::getFillColor().r, Button::getFillColor().g, Button::getFillColor().b, 100});
}
void Button::mouseLeave()
{
    Button::setFillColor({Button::getFillColor().r, Button::getFillColor().g, Button::getFillColor().b, 255});
}
void Button::handleEvent(sf::RenderWindow &window, sf::Event event)
{
    sf::Vector2f mouse_move = window.mapPixelToCoords({event.mouseMove.x, event.mouseMove.y});;
    sf::Vector2f mouse_btn = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});;
    
    switch (event.type)
    {
        case sf::Event::MouseMoved:
            
            contains(mouse_move) ? mouseOver() : mouseLeave();
            
            break;
        case sf::Event::MouseButtonReleased:
                        
            if (contains(mouse_btn))
                m_clicked = !m_clicked;
            
            break;
            
        default:
            break;
    }
}






////////////////////////////////////////////////////////////
void Button::setTexture(const sf::Texture* texture, bool resetRect)
{
    if (texture)
    {
        // Recompute the texture area if requested, or if there was no texture & rect before
        if (resetRect || (!m_texture && (m_textureRect == sf::IntRect())))
            setTextureRect(sf::IntRect({0, 0}, sf::Vector2i(texture->getSize())));
    }

    // Assign the new texture
    m_texture = texture;
}


////////////////////////////////////////////////////////////
const sf::Texture* Button::getTexture() const
{
    return m_texture;
}


////////////////////////////////////////////////////////////
void Button::setTextureRect(const sf::IntRect& rect)
{
    m_textureRect = rect;
    Shape::update();
}


////////////////////////////////////////////////////////////
const sf::IntRect& Button::getTextureRect() const
{
    return m_textureRect;
}


////////////////////////////////////////////////////////////
void Button::setFillColor(const sf::Color& color)
{
    m_fillColor = color;
    Shape::update();
}


////////////////////////////////////////////////////////////
const sf::Color& Button::getFillColor() const
{
    return m_fillColor;
}


////////////////////////////////////////////////////////////
void Button::setOutlineColor(const sf::Color& color)
{
    m_outlineColor = color;
    Shape::update();
}


////////////////////////////////////////////////////////////
const sf::Color& Button::getOutlineColor() const
{
    return m_outlineColor;
}


////////////////////////////////////////////////////////////
void Button::setOutlineThickness(float thickness)
{
    m_outlineThickness = thickness;
    Shape::update();
}


////////////////////////////////////////////////////////////
float Button::getOutlineThickness() const
{
    return m_outlineThickness;
}


////////////////////////////////////////////////////////////
sf::Vector2f Button::getGeometricCenter() const
{
    const auto count = getPointCount();

    switch (count)
    {
        case 0:
            assert(false && "Cannot calculate geometric center of shape with no points");
            return sf::Vector2f{};
        case 1:
            return getPoint(0);
        case 2:
            return (getPoint(0) + getPoint(1)) / 2.f;
        default: // more than two points
            sf::Vector2f centroid;
            float    twiceArea = 0;

            auto previousPoint = getPoint(count - 1);
            for (std::size_t i = 0; i < count; ++i)
            {
                const auto  currentPoint = getPoint(i);
                const float product      = cross(previousPoint, currentPoint);
                twiceArea += product;
                centroid += (currentPoint + previousPoint) * product;

                previousPoint = currentPoint;
            }

            if (twiceArea != 0.f)
            {
                return centroid / 3.f / twiceArea;
            }

            // Fallback for no area - find the center of the bounding box
            auto minPoint = getPoint(0);
            auto maxPoint = minPoint;
            for (std::size_t i = 1; i < count; ++i)
            {
                const auto currentPoint = getPoint(i);
                minPoint.x              = std::min(minPoint.x, currentPoint.x);
                maxPoint.x              = std::max(maxPoint.x, currentPoint.x);
                minPoint.y              = std::min(minPoint.y, currentPoint.y);
                maxPoint.y              = std::max(maxPoint.y, currentPoint.y);
            }
            return (maxPoint + minPoint) / 2.f;
    }
}


////////////////////////////////////////////////////////////
sf::FloatRect Button::getLocalBounds() const
{
    return m_bounds;
}


////////////////////////////////////////////////////////////
sf::FloatRect Button::getGlobalBounds() const
{
    return getTransform().transformRect(getLocalBounds());
}
