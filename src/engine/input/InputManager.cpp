#include <engine/input/InputManager.hpp>

#include <algorithm>
#include <functional>


Action InputManager::verifyInput( const Request& request, const Input& input ) {
    // [KEYBOARD]============================================
    std::function<bool( const Request::kbBinding& )> p1
        = [&]( const Request::kbBinding& B ) {
        return input.keyb.key == B.key;
    };
    const auto& A = std::find_if(
        request.vitalKeys.begin(),
        request.vitalKeys.end(),
        p1
    );

    if ( A != request.vitalKeys.end() ) {
        return A->act;
    } else return Action::None;

    // [MOUSE]==============================================
    std::function<bool( const Request::msBinding& )> p2
        = [&]( const Request::msBinding& B ) {
            return ( input.mouse.btn == B.btn )
                && ( B.bounds->contains(input.mouse.pos) );
        };
    const auto& B = std::find_if(
        request.vitalButtons.begin(),
        request.vitalButtons.end(),
        p2
    );

    if ( B != request.vitalButtons.end() ) {
        return B->act;
    } else return Action::None;
}