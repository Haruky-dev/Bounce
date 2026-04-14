#include <algorithm>
#include <engine/features/Transition.hpp>

void Transition::initT( const int speed ) {
    this->targetSc = 0.f;
    this->speed = speed;
}

void Transition::resetT() {
    this->timeScale = this->targetSc = 1.f;
}

sf::Time Transition::tick( const sf::Time& dt ) {
    if ( this->timeScale != this->targetSc ) {
        const float step = this->speed * dt.asSeconds();
        
        if ( this->timeScale > this->targetSc )
            this->timeScale = std::min( this->targetSc, this->timeScale - step );
        else
            this->timeScale = std::max( this->targetSc, this->timeScale + step );
    }
    
    return dt * this->timeScale;
}

float Transition::scale() const { return this->timeScale; }
bool Transition::done()   const { return this->timeScale == this->targetSc; }