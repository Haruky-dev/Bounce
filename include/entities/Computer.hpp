#pragma once

#include <SFML/Graphics.hpp>

#include <entities/Player.hpp>
#include <entities/Ball.hpp>


class Computer : public Player {
    friend class GameLayer;

    private:
        float retDur; // return duration
        float retTime;
        float delayTime;
        float centerTime;
        float deadZone;
        float delay;
        int error;
        bool actAllowed; // guardian flag of delay logic

    private:
        // correcten the Y values where the ball is estimated to land on
        float correct_estimation( float ) const;
        // randomize imperfections flags. Used each Player<Human> ball reflect
        void updateImperfection();

    public:
        Computer( const sf::Sprite& spr, const bool );
        void update( const sf::Time& dt, const Ball& );
};