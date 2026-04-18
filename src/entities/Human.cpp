#include <entities/Human.hpp>

#include <entities/Ball.hpp>
#include <tools/Tool.hpp>
#include <tools/Math.hpp>
#include <tools/Json.hpp>

#include <math.h>


Human::Human(const sf::Sprite &spr, bool id ) :
    Player(spr, id),
    path( "modes." + Tool::MODE + "player." ),
    speed( Json::Float( path + "speed" ) ),
    accel( Json::Float( path + "accel" ) ),
    ballBounce( Json::Float( path + "ballBounce" ) )
    {

    this->bar.setPosition( {Tool::WIDTH - 20.f, Tool::W_CTR.y - 100.0f} );
}

void Human::update( const sf::Time& dt ) {
    assert( this->id == 0 );

    double Y_pos = bar.getPosition().y;
    double halfHeight = this->bounds().size.y / 2.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        if (Y_pos - halfHeight > Tool::W_EDGE)
            bar.move({0, -this->speed * dt.asSeconds()});

        this->direction = 1;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        if (Y_pos + halfHeight < Tool::HEIGHT - Tool::W_EDGE)
            bar.move({0, this->speed * dt.asSeconds()});

        this->direction = -1;
    } else if ( this->direction ) { this->direction = 0; }
}

void Human::refresh() {
    this->speed += this->accel;
}

const bool Human::ready() const {
    const float y_pos = this->bar.getPosition().y;
    const float bar_height = this->bar.getLocalBounds().size.y; // hitbox

    return ( y_pos > Tool::W_CTR.y - bar_height) && (y_pos < Tool::W_CTR.y + bar_height);
}

const float Human::bounce_acceleration() const { return this->ballBounce; }