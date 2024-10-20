#ifndef COLLISION_H
#define COLLISION_H

#include <SFML/Graphics.hpp>

namespace BetterCollision {
    bool pixelPerfectTest(const sf::Sprite& sprite1, const sf::Sprite& sprite2, sf::Uint8 alphaLimit = 0);

    bool singlePixelTest(const sf::Sprite& sprite, sf::Vector2f& mousePosition, sf::Uint8 alphaLimit);

    bool createTextureAndBitmask(sf::Texture &loadInto, const std::string& filename);

    bool circleTest(const sf::Sprite& sprite1, const sf::Sprite& sprite2);
 
    bool boundingBoxTest(const sf::Sprite& sprite1, const sf::Sprite& sprite2);
}

#endif
