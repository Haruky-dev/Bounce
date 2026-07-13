#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <engine/input/Input.hpp>


struct InputEv {
    public:
        static Input::kbProp
            keybClick( std::vector<sf::Keyboard::Key> keys ) {

                for ( const sf::Keyboard::Key& K : keys )
                    if ( sf::Keyboard::isKeyPressed( K ) )
                        return { K, true };
                    
                return {
                    sf::Keyboard::Key::Unknown, false
                };
        }

        static Input::msProp
            mouseClick( std::vector<sf::Mouse::Button> buttons, sf::RenderWindow& win ) {

                for ( const sf::Mouse::Button& B : buttons )
                    if ( sf::Mouse::isButtonPressed( B ) )
                        return {
                            sf::Mouse::getPosition( win ),
                            B, true
                        };

                return Input::msProp();
            }
};