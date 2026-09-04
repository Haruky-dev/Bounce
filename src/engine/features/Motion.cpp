#include <engine/features/Motion.hpp>

#include <math.h>


Motion::Motion() :
    duration_(sf::seconds(1.0f)), elapsed_(sf::Time::Zero),
    direction_(1), active_(false)
    {}

void Motion::reset() {
    this->elapsed_ = sf::Time::Zero;
    this->active_ = false;
}
