// A box containing different aspects of user input each frame.
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>


class Input {
    private:
        struct mouseBind {
            sf::Vector2i pos;
            sf::Mouse::Button btn;
            bool clicked = false;
    
            mouseBind( const sf::Vector2i& vect ={0, 0}, sf::Mouse::Button btn=sf::Mouse::Button::Extra1, bool click=false )
            : btn(btn), clicked(click) {
                this->pos.x = vect.x;
                this->pos.y = vect.y;
            }
        };
        struct keyboardBind {
            sf::Keyboard::Key key = sf::Keyboard::Key::Unknown;
            bool clicked = false;
    
            keyboardBind( sf::Keyboard::Key key=sf::Keyboard::Key::Unknown, bool click=false )
            : key(key), clicked(click) {}
    };

    public:
        mouseBind mouse;
        keyboardBind keyb;

    public:
        static Input::mouseBind    validateButtons( std::span<sf::Mouse::Button>, const sf::RenderWindow& );
        static Input::keyboardBind validateKeys( std::span<sf::Keyboard::Key> );
};