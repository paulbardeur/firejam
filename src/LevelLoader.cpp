/*
** EPITECH PROJECT, 2024
** Firejam
** File description:
** LevelLoader
*/

#include <fstream>
#include <sstream>

#include "LevelLoader.hpp"

bool Firejam::LevelLoader::loadLevel(int levelNumber, Gems gems, Obstacles obstacles, Environments environments)
{
    std::ifstream file("level" + std::to_string(levelNumber) + ".txt");

    if (!file.is_open()) {
        return false;
    }

    std::string line;

    while (std::getline(file, line)) {

        std::stringstream ss(line);
        std::string type;

        ss >> type;

        if (type == "GEM") {

            float x, y;
            std::string gemType;

            ss >> x >> y >> gemType;
            Type type = (gemType == "FIRE") ? Type::FIRE : Type::ICE;
            gems.push_back(std::make_shared<Gem>(type, sf::Vector2f(x, y)));

        } 
        
        if (type == "OBSTACLE") {

            float x, y;
            bool end;

            ss >> x >> y >> end;
            obstacles.push_back(std::make_shared<Obstacle>(sf::Vector2f(x, y), end));

        }

        if (type == "ENVIRONMENT") {

            float x, y;
            std::string envType;

            ss >> x >> y >> envType;
            Type type = (envType == "FIRE") ? Type::FIRE : Type::ICE;
            environments.push_back(std::make_shared<Environment>(type, sf::Vector2f(x, y)));

        }

    }

    return true;
}
