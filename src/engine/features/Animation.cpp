#include <engine/features/Animation.hpp>


Animation::Animation( const float sec ) :
    __motion() {
        this->__motion._duration = sf::seconds(sec);
        this->enter();
}

void Animation::update( const sf::Time& dt ) {
    if ( !(this->__motion._active) ) return;

    this->__motion._elapsed += dt * (float) this->__motion._direction;

    if ( this->__motion._elapsed >= this->__motion._duration ) {
        this->__motion._elapsed = this->__motion._duration;
        this->__motion._active  = false;
    } else if ( this->__motion._elapsed <= sf::Time::Zero ) {
        this->__motion._elapsed = sf::Time::Zero;
        this->__motion._active  = false;
    }
}

void Animation::__forward() {
    this->__motion._direction = 1;
    this->__motion._active    = true;
}
void Animation::__backward() {
    this->__motion._direction = -1;
    this->__motion._active    = true;
}

void Animation::enter() { this->__forward(); }
void Animation::exit()  { this->__backward(); }

const double Animation::progress() const {
    assert( this->__motion._duration > sf::Time::Zero );
    return std::clamp(
        this->__motion._elapsed / this->__motion._duration,
        0.0f, 1.0f );
}

const bool Animation::finished() const { return !(this->__motion._active); }

const Animation::Status Animation::status() const {
    return ( this->__motion._direction == -1 )?
        Animation::Status::Out : Animation::Status::In;
}