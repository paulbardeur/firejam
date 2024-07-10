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

            Player player;

            bool isRunning;
    
            sf::RenderWindow window;

            std::vector<Gem> gems;
            std::vector<Obstacles> obstacles;
            std::vector<Environment> environments;

    };

;}

#endif /* !GAME_HPP_ */
