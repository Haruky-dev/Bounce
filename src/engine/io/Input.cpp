#include <engine/io/Input.hpp>


Input::mouseBind Input::validateButtons( std::span<sf::Mouse::Button> buttons, const sf::RenderWindow& win) {
    for ( const sf::Mouse::Button B : buttons )
        if ( sf::Mouse::isButtonPressed(B) )
            return {
                sf::Mouse::getPosition( win ),
                B, true
            };

    return mouseBind();
}

Input::keyboardBind Input::validateKeys( std::span<sf::Keyboard::Key> keys ) {
    for ( const sf::Keyboard::Key K : keys )
        if ( sf::Keyboard::isKeyPressed(K) )
            return { K, true };

    return keyboardBind();
}