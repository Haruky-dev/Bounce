#pragma once

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
        float ballBounce;

        float delay;
        int error;
        std::pair<float, float> delayRange;
        std::pair<int, int> errorRange;

    public:
        void refresh_imperfection();
        void general_refresh();

        Neuron();
        ~Neuron() = default;
};