#include <engine/request/Constraint.hpp>

#include <engine/request/constraints/Bounds.hpp>
#include <engine/request/constraints/Cooldown.hpp>

std::unique_ptr<Bounds> Constraint::bounds( const sf::Rect<int>& B ) {
    return std::make_unique<Bounds>( B );
}
std::unique_ptr<Cooldown> Constraint::cooldown( int ms ) {
    return std::make_unique<Cooldown>( ms );
}