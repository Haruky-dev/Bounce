#pragma once

#include <SFML/Graphics/Rect.hpp>

#include <entities/Ball.hpp>
#include <entities/Player.hpp>
#include <entities/ai/Computer.hpp>

#include <tools/Constants.hpp>


namespace Collision {
    bool wall( const sf::Rect<float>&, Constants::Sides& );
    bool player( const sf::Rect<float>&, const sf::Rect<float>&, Constants::Sides& );
    bool computer( const sf::Rect<float>&, const sf::Rect<float>&, Constants::Sides& );
};