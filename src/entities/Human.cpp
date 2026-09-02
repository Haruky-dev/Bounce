#include <entities/Human.hpp>

#include <entities/Ball.hpp>
#include <tools/Constants.hpp>
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

    double Y_pos = bar.getPosition().y;
    double halfHeight = this->bounds().size.y / 2.0f;

    if ( Flags::PlayerFrozen ) {
        this->direction = 0;
        return;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        if (Y_pos - halfHeight > Constants::W_EDGE)
            bar.move({0, -this->speed * dt.asSeconds()});

        this->direction = 1;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        if (Y_pos + halfHeight < Constants::HEIGHT - Constants::W_EDGE)
            bar.move({0, this->speed * dt.asSeconds()});

        this->direction = -1;
    } else if ( this->direction ) { this->direction = 0; }
}

void Human::refresh() {
    this->speed = std::min( this->speed+this->accel, this->speed*Constants::stretchPercent);
}