#pragma once

#include <SFML/Graphics.hpp>

#include <entities/ai/Neuron.hpp>
#include <entities/Player.hpp>
#include <entities/Ball.hpp>


class Computer : public Player {
    private:
        Neuron neuron;
        float centerTimer;
        float delayTimer;
        bool actAllowed; // guardian flag of delay logic

    private:
        // correcten the Y values where the ball is estimated to land on
        float correct_estimation( float ) const;

    public:
        Computer( const sf::Sprite& spr, const bool );

        void refresh() override;
        void update( const sf::Time& dt, const Ball& );
        
        const float bounce_acceleration() const;
};