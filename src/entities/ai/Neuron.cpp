#include <entities/ai/Neuron.hpp>

#include <tools/Json.hpp>
#include <tools/Math.hpp>
#include <tools/Constants.hpp>

#include <print>


Neuron::Neuron() :
    returnDur(Json::Float( "computer.returnDuration" )),
    returnTime(Json::Float( "computer.returnTime" )),
    deadZone(Json::Float( "computer.deadZone" )),
    speed(Json::Float( "computer.speed" )),
    accel(Json::Float( "computer.accel")),
    delay_timer(sf::Time::Zero),
    allowed(false),
    delayPivot(Json::Int( "computer.delayPivot" )),
    errorPivot(Json::Int( "computer.errorPivot" ))
    {
        this->refresh();
    }


void Neuron::refresh() {
    this->error = this->errorPivot + Math::randi( 0, this->errorPivot * Constants::offsetPercent, true ); // needs to generate neg values
    this->delay = this->delayPivot + Math::randi( 0, this->delayPivot * Constants::offsetPercent, true );
    this->speed = std::min( this->speed+this->accel, this->speed*Constants::stretchPercent );

    assert( (this->delay >= 0) );

    std::println("error={}, delay={}, speed={}", this->error, this->delay, this->speed);
    this->reset();
}

void Neuron::reset() {
    this->allowed = false;
    this->delay_timer = sf::Time::Zero;
}

void Neuron::update( const sf::Time& dt, const bool waiting ) {
    if ( waiting || this->allowed ) return;

    if ( this->delay_timer.asMilliseconds() >= this->delay ) {
        this->allowed = true;
    } else {
        this->delay_timer += dt;
    }
}