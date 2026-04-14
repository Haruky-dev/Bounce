#pragma once

#include <entities/Player.hpp>


class Human : public Player {
    public:
        Human( const sf::Sprite& spr, bool id );

        void update( const sf::Time& dt );
};