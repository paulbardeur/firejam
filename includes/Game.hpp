/*
** EPITECH PROJECT, 2024
** Firejam
** File description:
** Game
*/

#ifndef GAME_HPP_
    #define GAME_HPP_

    #include <vector>
    #include <memory>
    #include <SFML/Graphics.hpp>

    #include "Gem.hpp"
    #include "Player.hpp"
    #include "Obstacle.hpp"
    #include "Environment.hpp"

    #define DEFAULT_VIEW sf::FloatRect(0, 0, 800, 600)

    #define VIEW_DELTA_X 300

    #define SCORE_FONT "assets/stocky.ttf"
    #define BACKGROUND_ASSET "assets/background.png"
    #define SCORE "Score: "
    #define SCORE_POSITION 12, 12
    #define SCORE_SIZE 28
    #define ONE_POINT 1

namespace Firejam {

    class Game {

        public:

            Game(int nbLevel);

            int run(sf::RenderWindow &window);
            int loadLevel();
            int startInfiniteMode();

        private:

            int processInput(sf::RenderWindow &window);
            int update(sf::Time delta, sf::RenderWindow &window);
            int updateScore();
            int render(sf::RenderWindow &window);

            int generateInfiniteElements();

            std::shared_ptr<Player> _player;

            sf::View _view;

            bool _isRunning;

            int _score;
            int _currentLevel;
            bool _infiniteMode;

            float _lastGemPosition;
            float _lastObstaclePosition;
            float _lastEnvironmentPosition;

            sf::Font _scoreFont;
            sf::Text _scoreText;

            sf::Sprite _background;
            sf::Texture _backgroundTexture;

            std::vector<std::shared_ptr<Gem>> _gems;
            std::vector<std::shared_ptr<Obstacle>> _obstacles;
            std::vector<std::shared_ptr<Environment>> _environments;

    };

;}

#endif /* !GAME_HPP_ */
