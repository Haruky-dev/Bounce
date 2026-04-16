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
    ballBounce( Json::Float( path + "ballBounce" ) )
    {

    this->bar.setPosition( {Tool::WIDTH - 20.f, Tool::W_CTR.y} );
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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        if (Y_pos + halfHeight < Tool::HEIGHT - Tool::W_EDGE)
            bar.move({0, this->speed * dt.asSeconds()});

        this->direction = -1;
    }
}