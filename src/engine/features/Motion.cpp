    #include <engine/features/Motion.hpp>

#include <math.h>


Motion::Motion() :
    _duration(sf::seconds(1.0f)), _elapsed(sf::Time::Zero),
    _direction(1), _active(false)
    {}

void Motion::reset() {
    this->_elapsed = sf::Time::Zero;
    this->_active = false;
}