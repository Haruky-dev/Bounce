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
        float accel;
        float ballBounce;

        float delay;
        int error;
        std::pair<float, float> delayRange;
        std::pair<int, int> errorRange;

    public:
        void refresh();

        Neuron();
        ~Neuron() = default;
};