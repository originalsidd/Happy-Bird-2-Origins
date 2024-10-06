#include "InputManager.hpp"
#include <iostream>

namespace Cosmic
{
    bool InputManager::isSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow &window)
    {
        if (sf::Mouse::isButtonPressed(button))
        {
            sf::IntRect tempRect(object.getPosition().x, object.getPosition().y, object.getGlobalBounds().width, object.getGlobalBounds().height);
            
            if (tempRect.contains(sf::Mouse::getPosition(window)))
            {
                return true;
            }
        }
        return false;
    }

    bool InputManager::isSpriteClicked(sf::Keyboard::Key key)
    {
        return sf::Keyboard::isKeyPressed(key);
    }

    sf::Vector2i InputManager::GetMousePosition(sf::RenderWindow &window)
    {
        return sf::Mouse::getPosition(window);
    }
}
