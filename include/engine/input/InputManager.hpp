#pragma once

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include <engine/input/Request.hpp>
#include <engine/input/Input.hpp>
#include <engine/input/Action.hpp>


class InputManager {
    public:
        static Action verifyInput( const Request& request, const Input& input );
};