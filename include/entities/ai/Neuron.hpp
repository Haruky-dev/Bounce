#pragma once

#include <SFML/System/Time.hpp>

#include <string>
#include <utility>


class Neuron {
    friend class Computer;

    private:
        std::string path;

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