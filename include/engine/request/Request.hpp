#pragma once

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include <engine/input/Input.hpp>
#include <engine/input/Action.hpp>
#include <engine/request/Constraint.hpp>

#include <variant>
#include <vector>
#include <memory>


class Request {
    friend class Layer;

    std::variant<sf::Keyboard::Key, sf::Mouse::Button> trigger;
    std::vector<std::unique_ptr<Constraint>> constraints;
    Action act;

    public:
        Request( sf::Keyboard::Key K, Action A )
            : trigger(K), act(A) , constraints() {}

        Request( sf::Mouse::Button B, Action A)
            : trigger(B), act(A), constraints() {}

        template <typename... Cs>
        void require( Cs&&... cs ) {
            ( constraints.emplace_back(std::forward<Cs>(cs)), ...);
        }

        bool allowed( const Context& context ) const {
            for ( auto& C : this->constraints )
                if ( !(C->satisfied(context)) )
                    return false;

            return true;
        }

        bool matches( const Input& in ) const {
            if ( this->trigger.index() ) { // Mouse button trigger
                return in.mouse.clicked && ( in.mouse.btn == std::get<sf::Mouse::Button>(this->trigger) );
            } else { // Keyboard button trigger
                return in.keyb.clicked && ( in.keyb.key == std::get<sf::Keyboard::Key>(this->trigger) );
            }
        }

        Action action() const { return this->act; }
};