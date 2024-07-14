/*
** EPITECH PROJECT, 2024
** Firejam
** File description:
** Menu
*/

#ifndef MENU_HPP_
    #define MENU_HPP_

    #include <SFML/Graphics.hpp>

    #include <vector>
    #include <string>

    #define NB_LEVELS 10

    #define SUCCESS 0
    #define ERROR 84

namespace Firejam {

    class Menu {

        public:

            Menu();

            int run();

        private:

            int processInput();
            int render();
            int loadScores();
            int saveScores();
            int drawLevelButtons();
            int drawInfiniteModeButton();

            sf::RenderWindow _window;
            sf::Font _font;
            sf::Text _titleText;

            sf::Sprite _background;
            sf::Texture _backgroundTexture;

            std::vector<sf::Text> _levelButtons;
            sf::Text _infiniteModeButton;

            std::vector<int> _levelScores;
            int _infiniteModeScore;

    };

;}

#endif /* !MENU_HPP_ */
