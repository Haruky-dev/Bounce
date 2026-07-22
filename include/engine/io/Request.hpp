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

    std::variant<sf::Keyboard::Key, sf::Mouse::Button> __trigger;
    std::vector<std::unique_ptr<Constraint>> __constraints;
    Action __act;

    public:
        Request( sf::Keyboard::Key K, Action A )
            : __trigger(K), __act(A) , __constraints() {}

        Request( sf::Mouse::Button B, Action A )
            : __trigger(B), __act(A), __constraints() {}

        template <typename... Cs>
        void require( Cs&&... cs ) {
            ( __constraints.emplace_back(std::forward<Cs>(cs)), ...);
        }

        bool allowed( const Context& context ) const {
            for ( auto& C : this->__constraints )
                if ( !(C->satisfied(context)) )
                    return false;

            return true;
        }

        bool matches( const Input& in ) const {
            if ( this->__trigger.index() ) { // Mouse button __trigger
                return in.mouse.clicked && ( in.mouse.btn == std::get<sf::Mouse::Button>(this->__trigger) );
            } else { // Keyboard button __trigger
                return in.keyb.clicked && ( in.keyb.key == std::get<sf::Keyboard::Key>(this->__trigger) );
            }
        }

        bool keyTriggered()    const { return !this->__trigger.index(); }
        bool buttonTriggered() const { return this->__trigger.index(); }
};