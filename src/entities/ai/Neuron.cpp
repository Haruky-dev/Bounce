#include <entities/ai/Neuron.hpp>

#include <tools/Json.hpp>
#include <tools/Math.hpp>
#include <tools/Tool.hpp>

#include <print>


Neuron::Neuron() :
    path( "modes." + Tool::MODE + "computer."),
    returnDur( Json::Float( path + "returnDuration" ) ),
    returnTime( Json::Float( path + "returnTime" ) ),
    deadZone( Json::Float( path + "deadZone" ) ),
    speed( Json::Float( path + "speed" ) ),
    accel( Json::Float( path + "accel") ),
    ballBounce( Json::Float( path + "ballBounce") ),

    errorRange({
        Json::Float( path + "predictionErr.min" ), 
        Json::Float( path + "predictionErr.max" )
        } ),
    delayRange({
        Json::Float( path + "reactDelay.min" ), 
        Json::Float( path + "reactDelay.max" )
        } )
    {
        this->refresh();
    }


void Neuron::refresh() {
    this->error = Math::randi(
        this->errorRange.first, this->errorRange.second
    );

    this->delay = Math::randi(
        this->delayRange.first, this->delayRange.second
    );

    std::println("refreshed [Computer]");

    this->speed += this->accel;
}

// void Neuron::general_refresh() {
//     // Neuron(); can you do something like this?? lol
// }