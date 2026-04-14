#include <entities/Computer.hpp>

#include <math.h>

#include <tools/Tool.hpp>
#include <tools/Json.hpp>
#include <tools/Math.hpp>


Computer::Computer( const sf::Sprite& bar, const bool id ) : Player( bar, id ),
    centerTime(0.0f), delayTime(0.0f), actAllowed(false),
    deadZone(Json::Float("ai.deadZone")),
    retTime(Json::Float("ai.returnTime")),
    retDur(Json::Float("ai.returnDuration")) {

    this->speed   = Json::Float("ai.speed");
    this->b_speed = Json::Float("ai.ballAccelOnReflect");

    this->bar.setPosition( {20.f, Tool::W_CTR.y} );
    this->bar.setRotation( sf::Angle(sf::degrees(180.f)) );

    this->updateImperfection();
}

void Computer::update( const sf::Time& dt, const Ball& ball ) {
    const sf::Vector2<float> ballPos = ball.spr.getPosition();
    const sf::Vector2<float> compPos = this->bar.getPosition();

    const float takenTime  = std::abs(
        (ballPos.x - compPos.x) / ball.velocity.x
    );
    const float estimatedY = this->correct_estimation(
        ballPos.y + ball.velocity.y * takenTime
    ) + this->error;

    const float diffrenceY = estimatedY - compPos.y;


    //---------------------- [DELAY] logic
    if ( ball.onStart) {
        this->actAllowed = false;
        this->delayTime = 0.0f;
    } else {
        if ( this->delayTime >= this->delay )
            this->actAllowed = true;

        else this->delayTime += dt.asSeconds();
    }

    //---------------------- [SET] flags
    const bool onTracking  = ball.onMove // you can ditch this condition since 'actAllowed' does guarentee ball.onMove==true
                            && (ball.unitDirec.x <= 0)
                            && (std::abs(diffrenceY) > this->deadZone)
                            && this->actAllowed;
    const bool onCentering = !(ball.onMove) || ( (ball.unitDirec.x > 0)
                            && (this->centerTime <= this->retTime) );

    const float mov = this->speed * dt.asSeconds();

    //---------------------- [Tracking]
    if ( onTracking ) {
        const float step = std::clamp( diffrenceY, -mov, mov );

        this->bar.move( {0.0f, step} );
        
    //---------------------- [Return-To-Center] logic
    } else if ( onCentering ) {
        this->centerTime += dt.asSeconds();

        const float K       = std::clamp( this->centerTime / this->retDur, 0.0f, 1.0f );
        const float targetY = Math::Lerp( compPos.y, Tool::W_CTR.y, Math::easeInOut(K) );
        const float step    = std::clamp( targetY - compPos.y, -mov, mov );

        this->bar.move( {0.0f, step} );
    }

    const bool resettable = ((ball.unitDirec.x < 0.0f) || Tool::goalScored) && ( this->centerTime != 0.0f);

    if ( resettable && (this->centerTime != 0.0f) )
        this->centerTime = 0.0f;
}

float Computer::correct_estimation( float y ) const {
    if ( !(std::isfinite(y)) ) return Tool::W_CTR.y;

    int maxBounces{5};

    while ( ((y < 0) || (y > Tool::HEIGHT)) && (maxBounces-- > 0)) {
        if ( y < 0 )
            y = -y;
        else
            y = Tool::HEIGHT * 2.0f - y;
    }

    assert(
        ( y >= 0 ) && ( y <= Tool::HEIGHT )
    );

    return y;
}

void Computer::updateImperfection() {
    this->error = Math::randi(
        Json::Int("ai.predictionError.min"),
        Json::Int("ai.predictionError.max")
    );
    this->delay = Math::randf(
        Json::Float("ai.reactionDelay.min"),
        Json::Float("ai.reactionDelay.max")
    );

    this->delayTime = 0.0f;
    this->actAllowed = false;
}