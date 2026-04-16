#pragma once

#include <entities/Player.hpp>


class Human : public Player {
    private:
        std::string path;
        float speed;
        float ballBounce;

    public:
        Human( const sf::Sprite& spr, bool id );

        void update( const sf::Time& dt );
};
