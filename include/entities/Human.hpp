#pragma once

#include <entities/Player.hpp>


class Human : public Player {
    private:
        float speed, accel;

    public:
        Human( const sf::Sprite& spr, bool id );

        void update( const sf::Time& dt );
        void refresh() override;
        void reset()   override;
};