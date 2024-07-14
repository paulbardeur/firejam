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

    #define DEFAULT_WINDOW sf::VideoMode(800, 600), "Firejam"
    #define DEFAULT_VIEW sf::FloatRect(0, 0, 800, 600)

    #define VIEW_DELTA_X 300

    #define SCORE_FONT "assets/stocky.ttf"
    #define SCORE "Score: "
    #define SCORE_POSITION 12, 12
    #define SCORE_SIZE 28
    #define ONE_POINT 1

namespace Firejam {

    class Game {

        public:

            Game();

            int run();

        private:

            int initGame();

            int processInput();
            int update(sf::Time delta);
            int updateScore();
            int render();

            Player _player;
            sf::RenderWindow _window;

            sf::View _view;

            bool _isRunning;

            size_t _score;
            sf::Font _scoreFont;
            sf::Text _scoreText;

            std::vector<std::shared_ptr<Gem>> _gems;
            std::vector<std::shared_ptr<Obstacle>> _obstacles;
            std::vector<std::shared_ptr<Environment>> _environments;

    };

;}

#endif /* !GAME_HPP_ */
