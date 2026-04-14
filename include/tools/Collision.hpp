#pragma once

#include <SFML/Graphics/Rect.hpp>

#include <entities/Ball.hpp>
#include <entities/Player.hpp>
#include <entities/Computer.hpp>

#include <tools/Tool.hpp>


class Collision {
    public:
        static bool wall( const sf::Rect<float>&, Tool::Sides& );
        static bool player( const sf::Rect<float>&, const sf::Rect<float>&, Tool::Sides& );
        static bool computer( const sf::Rect<float>&, const sf::Rect<float>&, Tool::Sides& );
};