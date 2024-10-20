#include <sstream>
#include "GameState.hpp"
#include "DEFINITIONS.hpp"
#include "GameOverState.hpp"
#include "GameFinishState.hpp"

#include <iostream>

namespace Cosmic
{
    GameState::GameState(GameDataRef data) : _data(data)
    {
        _isNight = false;
    }

    void GameState::Init()
    {
        if (!_hitSoundBuffer.loadFromFile(HIT_SOUND_FILEPATH))
        {
            std::cout << "Error loading Hit Sound Effect" << std::endl;
        }
        
        if (!_wingSoundBuffer.loadFromFile(WING_SOUND_FILEPATH))
        {
            std::cout << "Error loading Wing Sound Effect" << std::endl;
        }
        
        if (!_pointSoundBuffer.loadFromFile(POINT_SOUND_FILEPATH))
        {
            std::cout << "Error loading Point Sound Effect" << std::endl;
        }
        
        if (!_ostSoundBuffer.loadFromFile(OST_SOUND_FILEPATH))
        {
            std::cout << "Error loading Point Sound Effect" << std::endl;
        }
        
        _hitSound.setBuffer(_hitSoundBuffer);
        _wingSound.setBuffer(_wingSoundBuffer);
        _pointSound.setBuffer(_pointSoundBuffer);
        _ostSound.setBuffer(_ostSoundBuffer);
        
        _data->assets.LoadTexture("Game Background", GAME_BACKGROUND_FILEPATH);
        _data->assets.LoadTexture("Game Background 2", GAME_BACKGROUND2_FILEPATH);
        _data->assets.LoadTexture("Pipe Up", PIPE_UP_FILEPATH);
        _data->assets.LoadTexture("Pipe Down", PIPE_DOWN_FILEPATH);
        _data->assets.LoadTexture("Land", LAND_FILEPATH);
        _data->assets.LoadTexture("Bird Frame 1", BIRD_FRAME_1_FILEPATH);
        _data->assets.LoadTexture("Bird Frame 2", BIRD_FRAME_2_FILEPATH);
        _data->assets.LoadTexture("Bird Frame 3", BIRD_FRAME_3_FILEPATH);
        _data->assets.LoadTexture("Bird Frame 4", BIRD_FRAME_4_FILEPATH);
        _data->assets.LoadTexture("Scoring Pipe", SCORING_PIPE_FILEPATH);
        _data->assets.LoadFont("Flappy Font", FLAPPY_FONT_FILEPATH);
        
        pipe = new Pipe(_data);
        land = new Land(_data);
        bird = new Bird(_data);
        flash = new Flash(_data);
        hud = new HUD(_data);
        
        _background.setTexture(_data->assets.GetTexture("Game Background"));
        
        _score = 0;
        hud->UpdateScore(_score);
        
        _ostSound.setLoop(true);
        _ostSound.play();
        
        _gameState = GameStates::eReady;
        
    }

    void GameState::HandleInput()
    {
        sf::Event event;
        
        while (_data->window.pollEvent(event))
        {
            if (sf::Event::Closed == event.type)
            {
                _data->window.close();
            }
            
            if (_data->input.isSpriteClicked(_background, sf::Mouse::Left, _data->window))
//                || _data->input.isSpriteClicked(sf::Keyboard::Space)
//                || _data->input.isSpriteClicked(sf::Keyboard::Up))
            {
                if (GameStates::eGameOver != _gameState)
                {
                    _gameState = GameStates::ePlaying;
                    bird->Tap();
                    
                    _wingSound.play();
                }
            }
        }
    }

    void GameState::Update(float dt)
{
        if (GameStates::eGameOver != _gameState)
        {
            bird->Animate(dt);
            land->MoveLand(dt);
        }
        
        if (GameStates::ePlaying == _gameState)
        {
            pipe->MovePipes(dt);
            
            if (_clock.getElapsedTime().asSeconds() > PIPE_SPAWN_FREQUENCY && _score < 99)
            {
                pipe->RandomisePipeOffset();
                
                int rand1 = rand(), rand2 = rand();
                
                if (rand1 % 13) {
                    pipe->SpawnBottomPipe(_score);
                }
                if (rand2 % 7) {
                    pipe->SpawnTopPipe(_score);
                }
                pipe->SpawnScoringPipe();
                _clock.restart();
            }
            bird->Update(dt);
            
            std::vector<sf::Sprite> landSprites = land->GetSprites();
            
            for (int i = 0; i < landSprites.size(); i++)
            {
                if (collision.checkSpriteCollisionForScore(bird->GetSprite(), 0.8f, landSprites.at(i), 1.0f))
                {
                    _gameState = GameStates::eGameOver;
                    
                    _clock.restart();
                    
                    _hitSound.play();
                }
            }
            
            std::vector<sf::Sprite> pipeSprites = pipe->GetSprites();
            
            for (int i = 0; i < pipeSprites.size(); i++)
            {
                if (_score == WIN_SCORE) {
                    _gameState = GameStates::eGameOver;
                    
                    _clock.restart();
                }
                
                if (collision.checkSpriteCollision(bird->GetSprite(), 0.8f, pipeSprites.at(i), 1.0f))
                {
                    _gameState = GameStates::eGameOver;
                    
                    _clock.restart();
                    
                    _hitSound.play();
                }
            }
            
            if (GameStates::ePlaying == _gameState)
            {
                std::vector<sf::Sprite> &scoringSprites = pipe->GetScoringSprites();
                
                for (int i = 0; i < scoringSprites.size(); i++)
                {
                    if (collision.checkSpriteCollisionForScore(bird->GetSprite(), 0.1f, scoringSprites.at(i), 1.0f))
                    {
                        _score++;
                        
                        hud->UpdateScore(_score);
                        
                        scoringSprites.erase(scoringSprites.begin() + i);
                        
                        _pointSound.play();
                        
                        if (_score % 20 == 0) {
                            toggleScenary();
                        }
                    }
                }
            }
        }
        
        if (GameStates::eGameOver == _gameState)
        {
            flash->Show(dt);
            _ostSound.stop();
            
            if (_clock.getElapsedTime().asSeconds() > TIME_BEFORE_GAME_OVER_APPEARS)
            {
                if (_score == WIN_SCORE) {
                    _data->machine.AddState(StateRef(new GameFinishState(_data, _score)), true);
                } else {
                    _data->machine.AddState(StateRef(new GameOverState(_data, _score)), true);
                }
            }
        }
    }

    void GameState::Draw(float dt)
    {
        _data->window.clear();
        
        _data->window.draw(_background);
        
        pipe->DrawPipes();
        land->DrawLand();
        bird->Draw();
        
        flash->Draw();
        
        hud->Draw();
        
        _data->window.display();
    }

    void GameState::toggleScenary() {
        if (!_isNight) {
            _background.setTexture(_data->assets.GetTexture("Game Background 2"));
            _isNight = true;
        } else {
            _background.setTexture(_data->assets.GetTexture("Game Background"));
            _isNight = false;
        }
    }
}
