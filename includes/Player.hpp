/*
** EPITECH PROJECT, 2024
** Firejam
** File description:
** Player
*/

#ifndef PLAYER_HPP_
    #define PLAYER_HPP_

    #include <SFML/Graphics.hpp>

    #define FIRE_TEXTURE "assets/fire.png"
    #define ICE_TEXTURE "assets/ice.png"

    #define INITIAL_POSITION 100, 500

    #define GRAVITY 981
    #define GROUND_LEVEL 500
    #define JUMP_FORCE -500.0f

    #define DEFAULT_SPEED 200

    #define NONE 0

namespace Firejam {

    enum Type { FIRE, ICE };

    class Player {

        public:

            Player();

            int collectGem(Type type);
            int move(sf::Time delta);
            int jump();

            bool handleCollision(const sf::FloatRect &bounds);

            Type getState() const { return _state; };
            sf::Sprite getSprite() const { return _sprite; };
            sf::FloatRect getBounds() const;

        private:

            int updateSprite();

            Type _state;
    
            sf::Sprite _sprite;
            sf::Texture _fireTexture;
            sf::Texture _iceTexture;
    
            float _speed;
            sf::Vector2f _velocity;
    
            bool _isJumping;
            bool _onGround;
            bool _onObstacle;

    };

;}

#endif /* !PLAYER_HPP_ */
