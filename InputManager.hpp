#pragma once

#include <SFML/Graphics.hpp>

namespace Cosmic
{
    class InputManager
    {
    public:
        InputManager() {}
        ~InputManager() {}
        
        bool isSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow &window);
        bool isSpriteClicked(sf::Keyboard::Key key);
        
        sf::Vector2i GetMousePosition(sf::RenderWindow &window);
    };
}
