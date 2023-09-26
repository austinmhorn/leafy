//
//  PolygonShape.hpp
//  leafy
//
//  Copyright © 2023 Austin Horn. All rights reserved.
//

#ifndef PolygonShape_hpp
#define PolygonShape_hpp

#include <SFML/Graphics/Shape.hpp>

#include <leafy/Config.hpp>

namespace sf
{
    class LEAFY_API PolygonShape : public sf::Shape
    {
    public:

        explicit PolygonShape(const sf::Vector2f& radius = sf::Vector2f(0.f, 0.f), float pointCount = 30.f);
        
        void setRadius(const sf::Vector2f& radius);
        void setPointCount(float pointCount);
        
        const sf::Vector2f& getRadius() const;
        virtual std::size_t getPointCount() const;
        virtual sf::Vector2f getPoint(std::size_t index) const;

    private:

        sf::Vector2f m_radius;
        float        m_pointCount;
    };
}

#endif /* PolygonShape_hpp */
