#include <SFML/System/Angle.hpp>
#include <cassert>
#include <entities/Ball.hpp>

#include <entities/Player.hpp>

#include <tools/Tool.hpp>
#include <tools/Math.hpp>
#include <tools/Json.hpp>

#include <cache/SoundCache.hpp>

#include <math.h>
#include <print>


Ball::Ball( const sf::Sprite& spr ) :
    spr(spr), onStart(false), onMove(false),
    accTime(sf::Time::Zero),
    speed(Json::Float("ball.speed")), accel(Json::Float("ball.accel")),
    MAXspeed(Json::Float("ball.MAXspeed"))
    {
        // !! Math::rand( min, max )
        srand(time(NULL));

        this->spr.setOrigin( this->spr.getLocalBounds().getCenter() );

        this->reset();
}

void Ball::launch() {
    //= Target point
    sf::Vector2f targetPt;

        // tp.x
    switch ( Tool::ballOrient ) {
        case '1': targetPt.x = 0.0f; break;
        case '2': targetPt.x = Tool::WIDTH;        break;

        default:
            throw std::runtime_error("Invalid [orient] given for 'ball.launch'!");
    }
        // tp.y
    //  1st Half=0      2nd Half=1
    // [ 0,  200 ]  U  [ 250,  Tool::HEIGHT ]
    if ( Math::randi() ) {
        targetPt.y = Math::randi( 250, Tool::HEIGHT );
    } else {
        targetPt.y = Math::randi( 0, 200 );
    }

    // direction = targetPos - currPos;
    this->unitDirec = Math::Normalize( targetPt - this->spr.getPosition() );
    this->velocity = this->unitDirec * static_cast<float>(this->speed);

    this->onMove = true;
}

void Ball::draw( sf::RenderTarget& target, sf::RenderStates states ) const  {
    target.draw(spr, states);
}

void Ball::adjust( const Tool::Sides side, const sf::Rect<float>& padBounds) {
    sf::Vector2f newBallPos = spr.getPosition();
    int ballR = std::floor( this->spr.getGlobalBounds().size.x / 2.0f );

    switch ( side ) {
        case Tool::Sides::TOP:
            newBallPos.y = ballR + Tool::W_EDGE + 1.0f;
            break;
        case Tool::Sides::BOTTOM:
            newBallPos.y = Tool::HEIGHT - (ballR + Tool::W_EDGE + 1.0f);
            break;
        case Tool::Sides::LEFT:
            newBallPos.x = padBounds.position.x + padBounds.size.x + ballR + 1.0f;
            break;
        case Tool::Sides::RIGHT:
            newBallPos.x = padBounds.position.x - (ballR + 1.0f);
            break;
    }

    this->speed = std::min( this->speed + this->accel, this->MAXspeed );
    this->velocity = this->unitDirec * static_cast<float>(this->speed);

    this->spr.setPosition( newBallPos );
}

void Ball::reset() {
    this->onStart = true;
    this->onMove = false;
    this->speed = Json::Float("ball.speed");
    
    this->unitDirec = this->velocity = sf::Vector2<float>( 0.0f, 0.0f );

    this->spr.setPosition( Tool::W_CTR );
    this->spr.setRotation( sf::Angle( sf::degrees( 0.0f )) );
}

void Ball::rotate( const sf::Time& dt ) {
    if ( this->onMove ) {
        if ( this->accTime.asMilliseconds() >= Json::Float("ball.rot.delay") ) {
            this->accTime = sf::Time::Zero;

            int direc = (unitDirec.x > 0)? 1 : -1;
            this->spr.rotate( sf::Angle( sf::degrees(0.05f * this->speed * direc) ));

        } else this->accTime+= dt;
    }
}

void Ball::move( const sf::Vector2f& position ) { this->spr.move( position ); }

void Ball::reflect( const Tool::Sides side ) {
    const sf::Vector2f N = Math::Normalize( Tool::Norms[(int) side] );
    const float DP = Math::Dot( this->unitDirec, Tool::Norms[(int) side] );

    if (
        (N.x == 0.0f && N.y == 0.0f)
        || DP == 0.0f
    ) return;

    this->unitDirec -= 2.0f * DP * N;
    this->velocity = this->unitDirec * static_cast<float>(this->speed);
}

sf::Rect<float> Ball::bounds() const { return this->spr.getGlobalBounds(); }