#include <engine/request/Constraint.hpp>

#include <engine/request/constraints/Bounds.hpp>
#include <engine/request/constraints/Cooldown.hpp>
#include <engine/request/constraints/Predicate.hpp>

std::unique_ptr<Bounds> Constraint::bounds( const sf::Rect<int>& B ) {
    return std::make_unique<Bounds>( B );
}
std::unique_ptr<Cooldown> Constraint::cooldown( int ms ) {
    return std::make_unique<Cooldown>( ms );
}
std::unique_ptr<Predicate> Constraint::predicate( std::function<bool ()> func ) {
    return std::make_unique<Predicate>( std::move(func) );
}