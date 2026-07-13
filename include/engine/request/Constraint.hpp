#pragma once

#include <SFML/Graphics/Rect.hpp>

#include <engine/request/Context.hpp>

#include <memory>

class Bounds;
class Cooldown;


class Constraint {
    public:
        virtual bool satisfied( const Context& context ) const = 0;

        Constraint() = default;
        virtual ~Constraint() = default;

    public:
        // factory functions for individual Constraints
        static std::unique_ptr<Bounds> bounds( const sf::Rect<int>& );
        static std::unique_ptr<Cooldown> cooldown( int );
};