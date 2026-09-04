#include <engine/features/Animation.hpp>


Animation::Animation( const float sec ) :
    motion_() {
        this->motion_.duration_ = sf::seconds(sec);
        this->enter();
}

void Animation::update( const sf::Time& dt ) {
    if ( !(this->motion_.active_) ) return;

    this->motion_.elapsed_ += dt * (float) this->motion_.direction_;

    if ( this->motion_.elapsed_ >= this->motion_.duration_ ) {
        this->motion_.elapsed_ = this->motion_.duration_;
        this->motion_.active_  = false;
    } else if ( this->motion_.elapsed_ <= sf::Time::Zero ) {
        this->motion_.elapsed_ = sf::Time::Zero;
        this->motion_.active_  = false;
    }
}

void Animation::forward_() {
    this->motion_.direction_ = 1;
    this->motion_.active_    = true;
}
void Animation::backward_() {
    this->motion_.direction_ = -1;
    this->motion_.active_    = true;
}

void Animation::enter() { this->forward_(); }
void Animation::exit()  { this->backward_(); }

const double Animation::progress() const {
    assert( this->motion_.duration_ > sf::Time::Zero );
    return std::clamp(
        this->motion_.elapsed_ / this->motion_.duration_,
        0.0f, 1.0f );
}

const bool Animation::finished() const { return !(this->motion_.active_); }

const Animation::Status Animation::status() const {
    return ( this->motion_.direction_ == -1 )?
        Animation::Status::Out : Animation::Status::In;
}