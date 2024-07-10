/*
** EPITECH PROJECT, 2024
** Firejam
** File description:
** Player
*/

#ifndef PLAYER_HPP_
    #define PLAYER_HPP_

    #include <SFML/Graphics.hpp>

namespace Firejame {

    enum PlayerState { FIRE, ICE };

    class Player {

        public:

            Player() = default;

            void collectGem(PlayerState gemType);
            void move(sf::Time delta);
            void jump();

            PlayerState getState() const;
            sf::FloatRect getBounds() const;
            sf::Sprite getSprite() const;

        private:

            void updateSprite();

            PlayerState _state;
    
            sf::Sprite _sprite;
            sf::Texture _fireTexture;
            sf::Texture _iceTexture;
    
            sf::Vector2f _velocity;
    
            bool _isJumping;

    };

;}

#endif /* !PLAYER_HPP_ */
