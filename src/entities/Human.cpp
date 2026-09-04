#include <entities/Human.hpp>

#include <entities/Ball.hpp>
#include <tools/Constants.hpp>
#include <tools/Variables.hpp>
#include <tools/Math.hpp>
#include <tools/Json.hpp>

#include <math.h>


Human::Human(const sf::Sprite &spr, bool id ) :
    Player(spr, id),
    speed( Json::Float( "player.speed" ) ),
    accel( Json::Float( "player.accel" ) )
    {

    this->bar.setPosition( {Constants::WIDTH - 20.f, Constants::W_CTR.y} );
}

void Human::update( const sf::Time& dt ) {
    assert( this->id == 0 );

    if ( Flags::freeze.first ) {
        this->direction = 0;
        return;
    }

    const double Y  = bar.getPosition().y;
    const double H  = this->bounds().size.y / 2.0f;
    const bool up   = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up);
    const bool down = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down);

    int mvDirection = (up)? -1 : (down)? 1 : 0;
    if ( Flags::invert.first ) mvDirection *= -1;

    this->direction = -mvDirection;

    const float dy = mvDirection * this->speed * dt.asSeconds();

    if ( dy < 0 ) {
        if ( Y - H > Constants::W_EDGE ) this->bar.move({ 0, dy });
    } else if ( dy > 0 ) {
        if ( Y + H < Constants::HEIGHT - Constants::W_EDGE ) this->bar.move({ 0, dy });
    }
}

void Human::refresh() {
    this->speed = std::min( this->speed+this->accel, this->speed*Variables::stretchPercent);
}

void Human::reset() {
    this->speed = Json::Float("player.speed");
}