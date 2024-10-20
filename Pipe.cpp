#include "Pipe.hpp"
#include "DEFINITIONS.hpp"
#include <iostream>

namespace Cosmic
{
    Pipe::Pipe(GameDataRef data) : _data(data)
    {
        _landHeight = _data->assets.GetTexture("Land").getSize().y;
        _pipeSpawnYOffset = 0;
    }

    void Pipe::SpawnBottomPipe(int score)
    {
        sf::Sprite sprite(_data->assets.GetTexture("Pipe Up"));
        
        Pipe::Spawn(sprite, _data->window.getSize().x, _data->window.getSize().y - sprite.getGlobalBounds().height - _pipeSpawnYOffset, score);
    }

    void Pipe::SpawnTopPipe(int score)
    {
        sf::Sprite sprite(_data->assets.GetTexture("Pipe Down"));
        
        Pipe::Spawn(sprite, _data->window.getSize().x, -_pipeSpawnYOffset, score);
    }

    void Pipe::Spawn(sf::Sprite sprite, float posX, float posY, int score)
    {
        sprite.setPosition(posX, posY);
        
        int randInt = rand();
        int randIntSign = randInt%2 ==0 ? score : -score;
        randIntSign = randIntSign / 10;
        sprite.rotate(randIntSign);
        
        pipeSprites.push_back(sprite);
    }

    void Pipe::SpawnScoringPipe()
    {
        sf::Sprite sprite(_data->assets.GetTexture("Scoring Pipe"));
        
        sprite.setPosition(_data->window.getSize().x, 0);
        
        scoringPipes.push_back(sprite);
    }

    void Pipe::MovePipes(float dt)
    {
        float movement = PIPE_MOVEMENT_SPEED * dt;
    
        for (unsigned short int i = 0; i < pipeSprites.size(); i++)
        {
            if (pipeSprites.at(i).getPosition().x < 0 - pipeSprites.at(i).getGlobalBounds().width)
            {
                pipeSprites.erase(pipeSprites.begin() + i);
            }
            else
            {
                pipeSprites.at(i).move(-movement, 0);
            }
        }
        
        for (unsigned short int i = 0; i < scoringPipes.size(); i++)
        {
            if (scoringPipes.at(i).getPosition().x < 0 - scoringPipes.at(i).getGlobalBounds().width)
            {
                scoringPipes.erase(scoringPipes.begin() + i);
            }
            else
            {
                scoringPipes.at(i).move(-movement, 0);
            }
        }
    }

    void Pipe::DrawPipes()
    {
        for (unsigned short int i = 0; i < pipeSprites.size(); i++)
        {
            _data->window.draw(pipeSprites.at(i));
        }
    }

    void Pipe::RandomisePipeOffset()
    {
        _pipeSpawnYOffset = rand() % (_landHeight + 1);
    }

    const std::vector<sf::Sprite> &Pipe::GetSprites() const
    {
        return pipeSprites;
    }

    std::vector<sf::Sprite> &Pipe::GetScoringSprites()
    {
        return scoringPipes;
    }
}
