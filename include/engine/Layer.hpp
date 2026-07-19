/* Base class that define shape of all derived layers */
#pragma once

#include <SFML/Window/Window.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include <engine/input/Input.hpp>
#include <engine/input/Process.hpp>
#include <engine/request/Request.hpp>
#include <engine/request/Constraint.hpp>

#include <engine/request/constraints/Bounds.hpp>
#include <engine/request/constraints/Cooldown.hpp>
#include <engine/request/constraints/Predicate.hpp>

#include <vector>


class Layer { 
    private:
        virtual Process::Action feature() const { return Process::Action::NONE; }
        virtual void form_request() {}

    public:
        enum class Type {
            Loading,
            MainMenu,
            Setting,
            Play,
            Pause,
            GameOver,
            Quit
        };

    protected:
        std::vector<Request> requests;

        explicit Layer() : requests() {}

    public:
        virtual void   Load() = 0;
        virtual void   Update( const sf::Time& dt ) = 0;
        virtual void   Render( sf::RenderWindow& win ) const = 0; 
        virtual Process Read( const Context& context ) const {
            Process::Action A = this->feature();

            if ( A != Process::Action::NONE )
                return Process( A ); // if later on a Layer::feature had an sfx attached to it, this line should change

            for ( const Request& request : this->requests )
                if ( request.matches(context.input) && request.allowed(context) )
                    return request.__process;

            return Process();
        }

        // getters
        virtual Layer::Type type() const = 0;

        virtual std::vector<sf::Keyboard::Key> keys() const {
            std::vector<sf::Keyboard::Key> keys;
            keys.reserve( this->requests.size() );

            for ( const Request& R : this->requests )
                if ( !(R.__trigger.index()) )
                    keys.push_back( std::get<sf::Keyboard::Key>(R.__trigger) );

            return keys;
        }

        virtual std::vector<sf::Mouse::Button> buttons() const {
            std::vector<sf::Mouse::Button> buttons;
            buttons.reserve( this->requests.size() );

            for ( const Request& R : this->requests )
                if ( R.__trigger.index() )
                    buttons.push_back( std::get<sf::Mouse::Button>(R.__trigger) );

            return buttons;
        }

        // actions
        virtual void enter() {}
        virtual void pause() {}
        virtual void resume() {}
        virtual void exit() {} // leave
        virtual bool popable() const { return false; }
        virtual bool animated() const { return false; }

        virtual ~Layer() = default;
};