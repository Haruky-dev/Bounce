#pragma once

#include <SFML/System/Time.hpp>


class Motion {
    friend class Animation;

    Motion();
    ~Motion() = default;

    void reset();

    sf::Time _duration, _elapsed;
    int _direction; // 1==forward, -1==backward
    bool _active;
};
