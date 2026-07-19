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
#include <span>


class Layer { 
    private:
        virtual Process::Action feature() const { return Process::Action::NONE; }
        virtual void form_request() {}
        void __build_input() const {
            this->__keys.clear();
            this->__buttons.clear();

            this->__keys.reserve( this->__requests.size() );
            this->__buttons.reserve( this->__requests.size() );
            
            for ( const Request& R : this->__requests ) {
                if ( R.__trigger.index() )
                    this->__buttons.push_back( std::get<sf::Mouse::Button>(R.__trigger) );
                else
                    this->__keys.push_back( std::get<sf::Keyboard::Key>(R.__trigger) );
            }
        }

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
        std::vector<Request> __requests;
        mutable std::vector<sf::Keyboard::Key> __keys;
        mutable std::vector<sf::Mouse::Button> __buttons;
        mutable bool load_flag = false;

        explicit Layer() : __requests() {}

    public:
        virtual void   Load() = 0;
        virtual void   Update( const sf::Time& dt ) = 0;
        virtual void   Render( sf::RenderWindow& win ) const = 0; 
        Process Read( const Context& context ) const {
            Process::Action A = this->feature();

            if ( A != Process::Action::NONE )
                return Process( A ); // if later on a Layer::feature had an sfx attached to it, this line should change

            for ( const Request& request : this->__requests )
                if ( request.matches(context.input) && request.allowed(context) )
                    return request.__process;

            return Process();
        }

        // getters
        virtual Layer::Type type() const = 0;

        std::span<sf::Keyboard::Key> keys() const {
            if ( !load_flag ) {
                this->__build_input();
                this->load_flag = true;
            }

            return std::span( this->__keys.begin(), this->__keys.end() );
        }
        std::span<sf::Mouse::Button> buttons() const {
            if ( !load_flag ) {
                this->__build_input();
                this->load_flag = true;
            }

            return std::span( this->__buttons.begin(), this->__buttons.end() );
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