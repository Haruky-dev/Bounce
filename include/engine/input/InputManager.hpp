#pragma once

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include <engine/request/Request.hpp>
#include <engine/request/Context.hpp>
#include <engine/input/Input.hpp>
#include <engine/input/Action.hpp>

#include <vector>


class InputManager {
    public:
        static Action verifyInput( const std::vector<Request>&, const Context& context );
        // static Action verifyInput( const Request& request, const Input& input );
};
