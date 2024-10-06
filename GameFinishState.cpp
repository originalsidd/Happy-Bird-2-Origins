#include <sstream>
#include "GameFinishState.hpp"
#include "DEFINITIONS.hpp"
#include "GameState.hpp"

#include <fstream>
#include <iostream>

namespace Cosmic
{
    GameFinishState::GameFinishState(GameDataRef data, int score) : GameOverState(data, score)
    {
    }

    void GameFinishState::Init()
    {
        std::ifstream readFile;
        readFile.open(SCORE_SAVE_FILEPATH);
        
        
        if (readFile.is_open())
        {
            while (!readFile.eof())
            {
                readFile >> _highScore;
            }
        }
        
        readFile.close();
        
        std::ofstream writeFile(SCORE_SAVE_FILEPATH, std::ios::app);
        
        if (writeFile.is_open())
        {
            if (_score > _highScore)
            {
                _highScore = _score;
                
                writeFile << _highScore << std::endl;
            }
        }
        
        writeFile.close();
        
        
        _data->assets.LoadTexture("Game Over Background 2", GAME_OVER_BACKGROUND2_FILEPATH);
        _data->assets.LoadTexture("Game Over Title 2", GAME_OVER_TITLE2_FILEPATH);
        _data->assets.LoadTexture("Game Over Body", GAME_OVER_BODY_FILEPATH);
        _data->assets.LoadTexture("Bronze Medal", BRONZE_MEDAL_FILEPATH);
        _data->assets.LoadTexture("Silver Medal", SILVER_MEDAL_FILEPATH);
        _data->assets.LoadTexture("Gold Medal", GOLD_MEDAL_FILEPATH);
        _data->assets.LoadTexture("Platinum Medal", PLATINUM_MEDAL_FILEPATH);
        
        _background.setTexture(_data->assets.GetTexture("Game Over Background 2"));
        _gameOverContainer.setTexture(_data->assets.GetTexture("Game Over Body"));
        _gameOverTitle.setTexture(_data->assets.GetTexture("Game Over Title 2"));
        _retryButton.setTexture(_data->assets.GetTexture("Game Play Button"));
        
        _gameOverContainer.setPosition((_data->window.getSize().x / 2) - (_gameOverContainer.getGlobalBounds().width / 2), (_data->window.getSize().y / 2) - (_gameOverContainer.getGlobalBounds().height / 2));
        _gameOverTitle.setPosition((_data->window.getSize().x / 2) - (_gameOverTitle.getGlobalBounds().width / 2), _gameOverContainer.getPosition().y - (_gameOverTitle.getGlobalBounds().height * 1.2));
        _retryButton.setPosition((_data->window.getSize().x / 2) - (_retryButton.getGlobalBounds().width / 2), _gameOverContainer.getPosition().y + _gameOverContainer.getGlobalBounds().height + (_retryButton.getGlobalBounds().height * 0.2));
        
        _scoreText.setFont(_data->assets.GetFont("Flappy Font"));
        _scoreText.setString(std::to_string(_score));
        _scoreText.setCharacterSize(56);
        _scoreText.setFillColor(sf::Color::White);
        _scoreText.setOrigin(_scoreText.getGlobalBounds().width / 2, _scoreText.getGlobalBounds().height / 2);
        _scoreText.setPosition(_data->window.getSize().x * 0.725, _data->window.getSize().y / 2.15);
        
        _highScoreText.setFont(_data->assets.GetFont("Flappy Font"));
        _highScoreText.setString(std::to_string(_highScore));
        _highScoreText.setCharacterSize(56);
        _highScoreText.setFillColor(sf::Color::White);
        _highScoreText.setOrigin(_highScoreText.getGlobalBounds().width / 2, _highScoreText.getGlobalBounds().height / 2);
        _highScoreText.setPosition(_data->window.getSize().x * 0.725, _data->window.getSize().y / 1.78);
        
        _medal.setTexture(_data->assets.GetTexture("Platinum Medal"));
        _medal.setPosition(175, 465);
    }
}
