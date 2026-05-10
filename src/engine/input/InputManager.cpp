#include <engine/input/InputManager.hpp>

#include <algorithm>
#include <functional>


Action InputManager::verifyInput( const Request& request, const Input& input ) {
    // [KEYBOARD]============================================
    if ( input.keyb.clicked ) {
        const auto& B = std::find_if(
            request.vitalKeys.begin(),
            request.vitalKeys.end(),
            [&]( const Request::kbBinding& B ) {
                return B.key == input.keyb.key;
            }
        );

        if ( B != request.vitalKeys.end() )
            return B->act;
    }

    // [MOUSE]==============================================
    if ( input.mouse.clicked ) {
        const auto& B = std::find_if(
            request.vitalButtons.begin(),
            request.vitalButtons.end(),
            [&]( const Request::msBinding& B ) {
                return ( B.btn == input.mouse.btn
                    && ( B.bounds->contains(input.mouse.pos) )
                );
            }
        );
        
        if ( B != request.vitalButtons.end() )
            return B->act;
    }

    return Action::None;
}