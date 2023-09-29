//
//  RoundedRectangleShape.hpp
//  leafy
//
//  Created by Austin Horn.
//  Copyright © 2023 Austin Horn. All rights reserved.
//

#pragma once

#include <SFML/Graphics/Shape.hpp>

#include <leafy/Config.hpp>

#include <cmath>

namespace sf 
{
    class LEAFY_API RoundedRectangleShape : public sf::Shape
    {
        
    public:
        
        explicit RoundedRectangleShape(const sf::Vector2f& size = {0.f, 0.f}, float radius = 5, unsigned int cornerPointCount = 5);

        void setSize(const sf::Vector2f& size);
        const sf::Vector2f& getSize() const;

        void setCornersRadius(float radius);
        float getCornersRadius() const;

        void setCornerPointCount(unsigned int count);
        unsigned int getCornerPointCount();
        
        virtual std::size_t getPointCount() const;
        virtual sf::Vector2f getPoint(std::size_t index) const;

    private:
        
        sf::Vector2f m_size;
        float        m_cornersRadius;
        unsigned int m_cornerPointCount;
    };
}