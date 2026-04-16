#include <entities/Player.hpp>

#include <entities/Ball.hpp>
#include <tools/Tool.hpp>
#include <tools/Math.hpp>
#include <tools/Json.hpp>

#include <math.h>


Player::Player(const sf::Sprite &spr, bool id )
    : bar(spr), id(id), direction(0)
    {

    this->bar.setOrigin( this->bar.getLocalBounds().getCenter() );
}

void Player::update( const sf::Time& dt ) {
    assert( this->id == 0 );

    double Y_pos = bar.getPosition().y;
    double halfHeight = this->bounds().size.y / 2.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        if (Y_pos - halfHeight > Tool::W_EDGE)
            bar.move({0, -speed * dt.asSeconds()});

        this->direction = 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        if (Y_pos + halfHeight < Tool::HEIGHT - Tool::W_EDGE)
            bar.move({0, speed * dt.asSeconds()});

        this->direction = -1;
    }
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(bar, states);
}

sf::FloatRect Player::bounds() const { return this->bar.getGlobalBounds(); }
sf::Vector2f Player::getPos()  const { return this->bar.getPosition(); }