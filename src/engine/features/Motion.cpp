#include <engine/features/Motion.hpp>

#include <cassert>


Motion::Motion()
    : duration(1.f), elapsed(0.f), direction(1), active(false) {}
    
void Motion::forward() {
    this->direction = 1;
    this->active    = true;
}
void Motion::backward() {
    this->direction = -1;
    this->active    = true;
}

void Motion::update( const sf::Time& dt ) {
    if (!active) return;
    
    this->elapsed += this->direction * dt.asSeconds();
    
    if ( this->elapsed >= this->duration ) {
        this->elapsed = this->duration;
        this->active  = false;
    }
    
    if ( this->elapsed <= 0 ) {
        this->elapsed = 0.f;
        this->active  = false;
    }
}

float Motion::prog() const {
    return ( this->duration > 0.f )?
        this->elapsed / this->duration : 1.f;
}

bool Motion::finished() const { return !active; }
bool Motion::onReverse() const { return this->direction == -1; }