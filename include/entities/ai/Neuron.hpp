#pragma once

#include <SFML/System/Time.hpp>


class Neuron {
    friend class Computer;

    private:
        float returnDur;
        float returnTime;
        float deadZone;

        float speed;
        float accel;

        int delay;
        int error;

        int delayPivot;
        int errorPivot;

        sf::Time delay_timer;

        bool allowed;

    public:
        void refresh();
        void reset();
        void update( const sf::Time&, const bool );

        Neuron();
        ~Neuron() = default;
};