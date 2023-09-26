//
//  StadiumShape.hpp
//  leafy
//
//  Created by Austin Horn on 12/1/22.
//  Copyright © 2022 Austin Horn. All rights reserved.
//

#ifndef StadiumShape_hpp
#define StadiumShape_hpp

#include <SFML/Graphics/Shape.hpp>
#pragma once

#include <leafy/Config.hpp>

////////////////////////////////////////////////////////////
/// @class StadiumShape
///
/// @brief Draws a Stadium Shape; i.e. PillShape, OblongShape, etc.
////////////////////////////////////////////////////////////
namespace sf {

    class LEAFY_API StadiumShape : public sf::Shape {
    public:
            
        ////////////////////////////////////////////////////////////
        /// @brief Default constructor
        ///
        /// @param radius Radius for each rounded corner
        ////////////////////////////////////////////////////////////
        StadiumShape(const sf::Vector2f& size = {0.f, 0.f}, float cornerRadius = 0.f);
        
        ////////////////////////////////////////////////////////////
        /// @brief Calls private Shape function Shape::update()
        ///
        /// @see sf::Shape::update()
        ////////////////////////////////////////////////////////////
        void update();
        
        ////////////////////////////////////////////////////////////
        /// @brief Set the size of the rounded rectangle
        ///
        /// @param size New size of the rounded rectangle
        ///
        /// @see getSize
        ////////////////////////////////////////////////////////////
        void setSize(const sf::Vector2f& size);
        
        ////////////////////////////////////////////////////////////
        /// @brief Set the radius of the rounded corners
        ///
        /// @param radius Radius of the rounded corners
        ///
        /// @see getCornersRadius
        ////////////////////////////////////////////////////////////
        void setCornersRadius(float radius);
        
        ////////////////////////////////////////////////////////////
        /// @brief Set the number of points of each corner
        ///
        /// @param antialiasing New number of points of the rounded rectangle
        ///
        /// @see getPointCount
        ////////////////////////////////////////////////////////////
        void setAntialiasing(unsigned int antialiasing);
        
        ////////////////////////////////////////////////////////////
        /// @brief Get the size of the rounded rectangle
        ///
        /// @return Size of the rounded rectangle
        ///
        /// @see setSize
        ////////////////////////////////////////////////////////////
        const sf::Vector2f& getSize() const;
        
        ////////////////////////////////////////////////////////////
        /// @brief Get the radius of the rounded corners
        ///
        /// @returns Radius of the rounded corners
        ///
        /// @see setCornersRadius
        ////////////////////////////////////////////////////////////
        float getCornersRadius() const;
        
        ////////////////////////////////////////////////////////////
        /// @brief Get the antialiasing of the shape
        ///
        /// @returns Level of antialiasing 
        ///
        /// @see setAntialiasing
        ////////////////////////////////////////////////////////////
        unsigned int getAntialiasing() const;
        
        ////////////////////////////////////////////////////////////
        /// @brief Get the number of points defining the rounded rectangle
        ///
        /// @return Number of points of the rounded rectangle
        ////////////////////////////////////////////////////////////
        virtual std::size_t getPointCount() const override;
        
        ////////////////////////////////////////////////////////////
        /// @brief Get a point of the rounded rectangle
        /// The result is undefined if a index is out of the valid range.
        ///
        /// @param index Index of the point to get, in range [0 .. GetPointCount() - 1]
        ///
        /// @return Index-th point of the shape
        ////////////////////////////////////////////////////////////
        virtual sf::Vector2f getPoint(std::size_t index) const override;
        
    private:
        
        sf::Vector2f m_size;
        float        m_cornerRadius;
        unsigned     m_antialiasing;
        
    };

}


#endif /* StadiumShape_hpp */
