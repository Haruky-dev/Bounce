/* Base class that define shape of all derived layers */
#pragma once

#include <SFML/Window/Window.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include <engine/io/Input.hpp>
#include <engine/io/Action.hpp>
#include <engine/io/Request.hpp>
#include <engine/io/Constraint.hpp>

#include <engine/io/constraints/Bounds.hpp>
#include <engine/io/constraints/Cooldown.hpp>
#include <engine/io/constraints/Predicate.hpp>

#include <cache/SFX.hpp>

#include <vector>
#include <span>


class Layer { 
    private:
        virtual Action feature() const { return Action::NONE; }
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
        Action Read( const Context& context ) const {
            Action A = this->feature();

            if ( A != Action::NONE )
                return A;

            Context context_f = context; // filtered context, to make Request dis-allow mouse interactions-
                // -for animated layers when their animation has not finished yet
            if ( this->animated() && !this->popable() )
                context_f.input.mouse.clicked = false; // white lie lol

            for ( const Request& request : this->__requests )
                if ( request.matches(context_f.input) && request.allowed(context_f) ) {
                    if ( request.buttonTriggered() )
                        SFX::inst().play(SFX::Type::CLICK);

                    return request.__act;
                }

            return Action::NONE;
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