#pragma once

#include <engine/io/Constraint.hpp>

#include <SFML/Graphics/Rect.hpp>


class Bounds : public Constraint {
    private:
        sf::Rect<int> bounds;

    public:
        Bounds( const sf::Rect<int>& B ) : bounds(B) {}

        bool satisfied( const Context& context ) const override {
            return this->bounds.contains(
                context.input.mouse.pos
            );
        }
};