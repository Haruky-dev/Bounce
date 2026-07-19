#pragma once

#include <SFML/Graphics/Rect.hpp>

#include <engine/io/Context.hpp>

#include <memory>
#include <functional>

class Bounds;
class Cooldown;
class Predicate;


class Constraint {
    public:
        virtual bool satisfied( const Context& context ) const = 0;

        Constraint() = default;
        virtual ~Constraint() = default;

    public:
        // factory functions for individual Constraints
        static std::unique_ptr<Bounds> bounds( const sf::Rect<int>& );
        static std::unique_ptr<Cooldown> cooldown( int );
        static std::unique_ptr<Predicate> predicate( std::function<bool()> );
};