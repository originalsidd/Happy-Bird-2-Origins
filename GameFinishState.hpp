#pragma once

#include <SFML/Graphics.hpp>
#include "GameOverState.hpp"
#include "Game.hpp"

namespace Cosmic
{
    class GameFinishState : public GameOverState
    {
    public:
        GameFinishState(GameDataRef data, int score);
        
        void Init();
    };
}
