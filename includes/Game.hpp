/*
** EPITECH PROJECT, 2024
** Firejam
** File description:
** Game
*/

#ifndef GAME_HPP_
    #define GAME_HPP_

    #include <vector>
    #include <SFML/Graphics.hpp>

    #include "Gem.hpp"
    #include "Player.hpp"
    #include "Obstacle.hpp"
    #include "Environment.hpp"

namespace Firejame {

    class Game {

        public:

            Game() = default;

            void run();

        private:

            void initGame();

            void processInput();
            void update(sf::Time delta);
            void render();

            Player _player;
            sf::RenderWindow _window;

            bool _isRunning;

            std::vector<Gem> _gems;
            std::vector<Obstacle> _obstacles;
            std::vector<Environment> _environments;

    };

;}

#endif /* !GAME_HPP_ */
