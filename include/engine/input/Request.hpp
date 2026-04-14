//= What?
    // A simple "instruction sheet" that each game state sends to the StateManager
    // It tells the StateManager:
    //  "Hey, when the player presses THESE keys → you should do THIS action"
//= How?
    // Each unique State forms its unique request by calling (its parent) State::setRequest
    // State (the parent), gets the 'when' using "InputEv" from State::Read("Input"),
    // and manipulates it to return "Output" which "StateManager" does understand
#pragma once

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <vector>

#include <engine/input/Action.hpp>


class Request {
    friend class InputManager; // More of a Boss that is it of a friend LOL
    friend class Layer;

    struct msBinding {
        const sf::Rect<int>* bounds;
        sf::Mouse::Button btn;
        Action act;

        msBinding( sf::Mouse::Button B, Action A, const sf::Rect<int>& bound )
            : btn(B), act(A), bounds(&bound) {}
    };
    struct kbBinding {
        sf::Keyboard::Key key;
        Action act;

        kbBinding( sf::Keyboard::Key K, Action A ) : key(K), act(A) {}
    };

    std::vector< kbBinding > vitalKeys;
    std::vector< msBinding > vitalButtons;

    Action getAction( sf::Keyboard::Key K ) const {
        int size = this->vitalKeys.size();

        for ( int i = 0; i<size; i++ )
            if ( this->vitalKeys.at( i ).key == K )
                return this->vitalKeys.at( i ).act;

        return Action::None;
    }

    Action getAction( sf::Mouse::Button B, const sf::Rect<int>& loc ) const {
        int size = this->vitalButtons.size();

        for ( const msBinding& curr : this->vitalButtons )
            if (( curr.btn == B )
                && ( *(curr.bounds) == loc ))
                    return curr.act;

        return Action::None;
    }

    
    public:
        Request() = default;       
};