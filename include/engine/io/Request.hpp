#pragma once

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include <engine/io/Input.hpp>
#include <engine/io/Action.hpp>
#include <engine/io/Constraint.hpp>

#include <variant>
#include <vector>
#include <memory>


class Request {
    friend class Layer;

    std::variant<sf::Keyboard::Key, sf::Mouse::Button> trigger_;
    std::vector<std::unique_ptr<Constraint>> constraints_;
    Action act_;

    public:
        Request( sf::Keyboard::Key K, Action A )
            : trigger_(K), act_(A) , constraints_() {}

        Request( sf::Mouse::Button B, Action A )
            : trigger_(B), act_(A), constraints_() {}

        template <typename... Cs>
        void require( Cs&&... cs ) {
            ( constraints_.emplace_back(std::forward<Cs>(cs)), ...);
        }

        bool allowed( const Context& context ) const {
            for ( auto& C : this->constraints_ )
                if ( !(C->satisfied(context)) )
                    return false;

            return true;
        }

        bool matches( const Input& in ) const {
            if ( this->trigger_.index() ) { // Mouse button trigger_
                return in.mouse.clicked && ( in.mouse.btn == std::get<sf::Mouse::Button>(this->trigger_) );
            } else { // Keyboard button trigger_
                return in.keyb.clicked && ( in.keyb.key == std::get<sf::Keyboard::Key>(this->trigger_) );
            }
        }

        bool keyTriggered()    const { return !this->trigger_.index(); }
        bool buttonTriggered() const { return this->trigger_.index(); }
};