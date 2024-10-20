#pragma once

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include <vector>

namespace Cosmic
{
    class Pipe
    {
    public:
        Pipe(GameDataRef data);
        
        void SpawnBottomPipe(int sc);
        void SpawnTopPipe(int sc);
        void SpawnScoringPipe();
        void MovePipes(float dt);
        void DrawPipes();
        void RandomisePipeOffset();
        
        const std::vector<sf::Sprite> &GetSprites() const;
        std::vector<sf::Sprite> &GetScoringSprites();
        
    private:
        void Spawn(sf::Sprite sp, float posX, float posY, int sc);
        GameDataRef _data;
        std::vector<sf::Sprite> pipeSprites;
        std::vector<sf::Sprite> scoringPipes;
        
        int _landHeight;
        int _pipeSpawnYOffset;
    };
}
