/*
** EPITECH PROJECT, 2024
** Firejam
** File description:
** Menu
*/

#include <fstream>
#include <sstream>
#include <iostream>

#include "Menu.hpp"
#include "Game.hpp"

Firejam::Menu::Menu(): _window(sf::VideoMode(800, 600), "Menu principal"), _infiniteModeScore(0)
{
    _font.loadFromFile("assets/stocky.ttf");

    _backgroundTexture.loadFromFile("assets/background.png");
    _background.setTexture(_backgroundTexture);

    _titleText.setFont(_font);
    _titleText.setString("Selectionner un Niveau");
    _titleText.setCharacterSize(36);
    _titleText.setFillColor(sf::Color::White);
    _titleText.setPosition(155, 50);

    for (int i = 0; i < NB_LEVELS; i++) {
        sf::Text levelButton;
        levelButton.setFont(_font);
        levelButton.setString("Niveau " + std::to_string(i + 1));
        levelButton.setCharacterSize(24);
        levelButton.setFillColor(sf::Color::White);
        levelButton.setPosition(225, 120 + i * 40);
        _levelButtons.push_back(levelButton);
    }

    _infiniteModeButton.setFont(_font);
    _infiniteModeButton.setString("Mode Infini");
    _infiniteModeButton.setCharacterSize(24);
    _infiniteModeButton.setFillColor(sf::Color::White);
    _infiniteModeButton.setPosition(225, 120 + NB_LEVELS * 40);

    for (int i = 0; i < NB_LEVELS; i++) {
        _levelScores.push_back(NONE);
    }
    loadScores();
}

int Firejam::Menu::run()
{
    while (_window.isOpen()) {
        processInput();
        render();
    }

    saveScores();

    return SUCCESS;
}

int Firejam::Menu::processInput()
{
    sf::Event event;

    while (_window.pollEvent(event)) {

        if (event.type == sf::Event::Closed) {
            _window.close();
        }

        if (event.type == sf::Event::MouseButtonPressed) {

            for (int i = 0; i < NB_LEVELS; ++i) {

                if (_levelButtons[i].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {

                    Firejam::Game game(i + 1);

                    int score = game.run(_window);
                    if (score > _levelScores[i]) {
                        _levelScores[i] = score;
                    }

                }

            }

            if (_infiniteModeButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                Firejam::Game game(NONE);

                int score = game.run(_window);
                if (score > _infiniteModeScore) {
                    _infiniteModeScore = score;
                }

            }

        }
    }

    return SUCCESS;
}

int Firejam::Menu::render()
{
    _window.clear();

    _window.draw(_background);
    _window.draw(_titleText);

    drawLevelButtons();
    drawInfiniteModeButton();

    _window.display();

    return SUCCESS;
}

int Firejam::Menu::loadScores()
{
    std::ifstream file("scores.txt");

    if (!file.is_open()) {
        return SUCCESS;
    }

    std::string line;

    while (std::getline(file, line)) {

        std::stringstream ss(line);
        std::string label;
        int level;
        int score;

        ss >> label >> level >> score;

        if (level == NONE) {
            _infiniteModeScore = score;
            continue;
        }

        _levelScores[level - 1] = score;

    }

    return SUCCESS;
}

int Firejam::Menu::saveScores()
{
    std::ofstream file("scores.txt");

    for (int i = 0; i < NB_LEVELS; i++) {
        file << "Level " << i + 1 << " " << _levelScores[i] << std::endl;
    }

    file << "Level 0 " << _infiniteModeScore << std::endl;

    return SUCCESS;
}

int Firejam::Menu::drawLevelButtons()
{
    for (int i = 0; i < NB_LEVELS; i++) {

        sf::RectangleShape rectangle;

        rectangle.setFillColor(sf::Color::Black);
        rectangle.setOutlineThickness(3);
        rectangle.setOutlineColor(sf::Color::White);
        rectangle.setSize(sf::Vector2f(360, 30));
        rectangle.setPosition(220, 120 + i * 40);

        _window.draw(rectangle);

        _window.draw(_levelButtons[i]);
        sf::Text scoreText;
        scoreText.setFont(_font);
        scoreText.setString(std::to_string(_levelScores[i]) + " sur 20");
        scoreText.setCharacterSize(24);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setPosition(450, 120 + i * 40);
        _window.draw(scoreText);

    }

    return SUCCESS;
}

int Firejam::Menu::drawInfiniteModeButton()
{
    sf::RectangleShape rectangle;

    rectangle.setFillColor(sf::Color::Black);
    rectangle.setOutlineThickness(3);
    rectangle.setOutlineColor(sf::Color::White);
    rectangle.setSize(sf::Vector2f(280, 30));
    rectangle.setPosition(220, 120 + NB_LEVELS * 40);

    _window.draw(rectangle);

    _window.draw(_infiniteModeButton);

    sf::Text scoreText;

    scoreText.setFont(_font);
    scoreText.setString(std::to_string(_infiniteModeScore));
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(450, 120 + NB_LEVELS * 40);
    _window.draw(scoreText);

    return SUCCESS;
}
