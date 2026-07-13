#include <engine/input/InputManager.hpp>


Action InputManager::verifyInput(const std::vector<Request>& reqs, const Context& context ) {
    // [KEYBOARD]============================================
    if ( context.input.keyb.clicked ) {
        for ( const Request& request : reqs ) {
            // is the current request has a Keyboard::Key trigger
            if ( request.trigger.index() )
                continue;

            if ( // Does the inputed Keyboard::Key matches the request' trigger
                ( std::get<sf::Keyboard::Key>( request.trigger ) == context.input.keyb.key )
                && ( request.allowed(context) ) // and the request isn't stopped by any Constraint
            )
                return request.act;
        }
    }

    // [MOUSE]============================================
    if ( context.input.mouse.clicked ) {
        for ( const Request& request : reqs ) {
            // is the current request has a Mouse::Button trigger
            if ( !(request.trigger.index()) )
                continue;

            if ( // Does the inputed Mouse::Button matches the request' trigger
                ( std::get<sf::Mouse::Button>( request.trigger ) == context.input.mouse.btn )
                && ( request.allowed(context) ) // and the request isn't stopped by any Constraint
            )
                return request.act;
        }
    }

    return Action::None;
}