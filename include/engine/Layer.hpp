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
        void build_input_() const {
            this->keys_.clear();
            this->buttons_.clear();

            this->keys_.reserve( this->requests_.size() );
            this->buttons_.reserve( this->requests_.size() );
            
            for ( const Request& R : this->requests_ ) {
                if ( R.trigger_.index() )
                    this->buttons_.push_back( std::get<sf::Mouse::Button>(R.trigger_) );
                else
                    this->keys_.push_back( std::get<sf::Keyboard::Key>(R.trigger_) );
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
        std::vector<Request> requests_;
        mutable std::vector<sf::Keyboard::Key> keys_;
        mutable std::vector<sf::Mouse::Button> buttons_;
        mutable bool load_flag = false;

        explicit Layer() : requests_() {}

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

            for ( const Request& request : this->requests_ )
                if ( request.matches(context_f.input) && request.allowed(context_f) ) {
                    if ( request.buttonTriggered() )
                        SFX::inst().play(SFX::Type::CLICK);

                    return request.act_;
                }

            return Action::NONE;
        }

        // getters
        virtual Layer::Type type() const = 0;

        std::span<sf::Keyboard::Key> keys() const {
            if ( !load_flag ) {
                this->build_input_();
                this->load_flag = true;
            }

            return std::span( this->keys_.begin(), this->keys_.end() );
        }
        std::span<sf::Mouse::Button> buttons() const {
            if ( !load_flag ) {
                this->build_input_();
                this->load_flag = true;
            }

            return std::span( this->buttons_.begin(), this->buttons_.end() );
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