#include <engine/input/InputManager.hpp>


Action InputManager::verifyInput( const Request& request, const Input& input ) {
    Action out;

    // [KEYBOARD]
    if ( input.keyb.clicked )
        for ( const auto& binding : request.vitalKeys )
            if ( binding.key == input.keyb.key ) {
                // out = binding.act;
                out = request.getAction( binding.key );
                break;
            }


    // [MOUSE]
    if ( input.mouse.clicked )
        for ( const auto& binding : request.vitalButtons )
            if (( binding.btn == input.mouse.btn )
                && ( binding.bounds->contains( input.mouse.pos ))) {
                    // out = binding.act;
                    out = request.getAction( binding.btn, *(binding.bounds) );
                    break;
                }

    return out;
}