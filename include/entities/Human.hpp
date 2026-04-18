#pragma once

#include <entities/Player.hpp>


class Human : public Player {
    private:
        std::string path;
        float speed, accel, ballBounce;

    public:
        Human( const sf::Sprite& spr, bool id );

        void update( const sf::Time& dt );
        void refresh() override;
        const bool ready() const override;

        const float bounce_acceleration() const;
};