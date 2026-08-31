#include <entities/ai/Computer.hpp>

#include <math.h>

#include <tools/Constants.hpp>
#include <tools/Flags.hpp>
#include <tools/Json.hpp>
#include <tools/Math.hpp>


Computer::Computer( const sf::Sprite& bar, const bool id ) : Player( bar, id ), neuron(),
    centerTimer(0.0f) {

        this->bar.setPosition( {20.f, Constants::W_CTR.y} );
        this->bar.setRotation( sf::Angle(sf::degrees(180.f)) );
}

void Computer::update( const sf::Time& dt, const Ball& ball ) {
    const sf::Vector2<float> ballPos = ball.spr.getPosition();
    const sf::Vector2<float> compPos = this->bar.getPosition();

    const float takenTime  = std::abs(
        (ballPos.x - compPos.x) / ball.velocity.x
    );
    const float estimatedY = this->correct_estimation(
        ballPos.y + ball.velocity.y * takenTime
    ) + this->neuron.error;

    const float diffrenceY = estimatedY - compPos.y;

    this->neuron.update( dt, ball.onStart || (ball.unitDirec.x>=0) );

    //---------------------- [SET] flags
    const bool onTracking  = ball.onMove
                            && (ball.unitDirec.x <= 0)
                            && (std::abs(diffrenceY) > this->neuron.deadZone)
                            && this->neuron.allowed;
    const bool onCentering = !(ball.onMove) || ( (ball.unitDirec.x > 0)
                            && (this->centerTimer <= this->neuron.returnTime) );

    const float mov = this->neuron.speed * dt.asSeconds();

    //---------------------- [Tracking]
    if ( onTracking ) {
        const float step = std::clamp( diffrenceY, -mov, mov );

        if ( step > 0 ) {
            this->direction = -1;
        } else if ( step < 0 ) this->direction = 1;

        this->bar.move( {0.0f, step} );

    //---------------------- [Return-To-Center] logic
    } else if ( onCentering ) {
        this->centerTimer += dt.asSeconds();

        const float K       = std::clamp( this->centerTimer / this->neuron.returnDur, 0.0f, 1.0f );
        const float targetY = Math::Lerp( compPos.y, Constants::W_CTR.y, Math::easeInOut(K) );
        const float step    = std::clamp( targetY - compPos.y, -mov, mov );

        this->bar.move( {0.0f, step} );

    //---------------------- [IDLE] Not moving (excluding the case where the ball isn't comming towards AI)
    } else if ( this->direction ) { this->direction = 0; }

    const bool resettable = ((ball.unitDirec.x < 0.0f) || Flags::goalScored) && ( this->centerTimer != 0.0f);

    if ( resettable && (this->centerTimer != 0.0f) )
        this->centerTimer = 0.0f;
}

float Computer::correct_estimation( float y ) const {
    if ( !(std::isfinite(y)) ) return Constants::W_CTR.y;

    int maxBounces{5};

    while ( ((y < 0) || (y > Constants::HEIGHT)) && (maxBounces-- > 0)) {
        if ( y < 0 )
            y = -y;
        else
            y = Constants::HEIGHT * 2.0f - y;
    }

    assert( ( y >= 0 ) && ( y <= Constants::HEIGHT ) );

    return y;
}

void Computer::refresh() { this->neuron.refresh(); }