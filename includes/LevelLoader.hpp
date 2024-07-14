/*
** EPITECH PROJECT, 2024
** Firejam
** File description:
** LevelLoader
*/

#ifndef LEVEL_LOADER_HPP_
    #define LEVEL_LOADER_HPP_

    #include <vector>
    #include <string>
    #include <memory>

    #include "Gem.hpp"
    #include "Obstacle.hpp"
    #include "Environment.hpp"

namespace Firejam {

    class LevelLoader {

        using Gems = std::vector<std::shared_ptr<Gem>> &;
        using Obstacles = std::vector<std::shared_ptr<Obstacle>> &;
        using Environments = std::vector<std::shared_ptr<Environment>> &;

        public:

            static bool loadLevel(int levelNumber, Gems gems, Obstacles obstacles, Environments environments);

    };

;}

#endif /* !LEVEL_LOADER_HPP_ */
