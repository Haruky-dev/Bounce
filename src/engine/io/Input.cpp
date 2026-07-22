#include <engine/io/Input.hpp>


Input::mouseBind Input::validateButtons( std::span<sf::Mouse::Button> buttons, std::span<const sf::Event> events ) {
    for ( const sf::Event& E : events )
        if ( const auto& b = E.getIf<sf::Event::MouseButtonPressed>() )
            for ( const sf::Mouse::Button B : buttons )
                if ( b->button == B )
                    return { b->position, B, true };

    return mouseBind();
}

Input::keyboardBind Input::validateKeys( std::span<sf::Keyboard::Key> keys, std::span<const sf::Event> events ) {
    for ( const sf::Event& E : events )
        if ( const auto& k = E.getIf<sf::Event::KeyPressed>() )
            for ( const sf::Keyboard::Key K : keys )
                if ( k->code == K )
                    return { K, true };

    return keyboardBind();
}