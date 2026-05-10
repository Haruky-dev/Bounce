#include <engine/features/Animation.hpp>


Animation::Animation() :
    motion() {
        this->forward();
    }

void Animation::update( const sf::Time& dt ) {
    if ( !(this->motion._active) ) return;

    this->motion._elapsed += dt * (float) this->motion._direction;

    if ( this->motion._elapsed >= this->motion._duration ) {
        this->motion._elapsed = this->motion._duration;
        this->motion._active  = false;
    } else if ( this->motion._elapsed <= sf::Time::Zero ) {
        this->motion._elapsed = sf::Time::Zero;
        this->motion._active  = false;
    }
}

void Animation::forward() {
    this->motion._direction = 1;
    this->motion._active    = true;
}
void Animation::backward() {
    this->motion._direction = -1;
    this->motion._active    = true;
}

void Animation::exit() { this->backward(); }

const double Animation::progress() const {
    assert( this->motion._duration > sf::Time::Zero );
    return std::clamp(
        this->motion._elapsed / this->motion._duration,
        0.0f, 1.0f );
}

const bool Animation::finished() const { return !(this->motion._active); }

const Animation::Status Animation::status() const {
    return ( this->motion._direction == -1 )?
        Animation::Status::Out : Animation::Status::In;
}

void Animation::set_duration( const float sec ) {
    assert( sec > 0.0f );

    this->motion._duration
        = sf::seconds( sec );
}
