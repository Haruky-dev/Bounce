/* Base class that define shape of all derived layers */
#pragma once

#include <SFML/Window/Window.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include <engine/input/Input.hpp>
#include <engine/input/Action.hpp>
#include <engine/input/Request.hpp>
#include <engine/input/InputManager.hpp>

#include <initializer_list>


class StateManager;


class Layer { 
    private:
        virtual Action feature() const { return Action::None; }

    public:
        enum class Type {
            Loading,
            Holding,
            MainMenu,
            Setting,
            Play,
            Pause,
            GameOver,
            Quit
        };

    protected:
        Request request;

        explicit Layer() : request() {}

    public:
        virtual void   Load() = 0;
        virtual void   Update( const sf::Time& dt ) = 0;
        virtual void   Render( sf::RenderWindow& win ) const = 0; 

        virtual Action Read( const Input& input ) const {
            Action act = this->feature();

            if ( act == Action::None )
                act = InputManager::verifyInput( this->request, input );

            return act;
        }

        // getters
        virtual Layer::Type type() const = 0;

        virtual void setRequest( const std::initializer_list< Request::kbBinding >& that ) {
            for ( const Request::kbBinding& K : that )
                this->request.vitalKeys.push_back( K );
        }
        virtual void setRequest( const std::initializer_list< Request::msBinding >& that ) {
            for ( const Request::msBinding& B : that )
                this->request.vitalButtons.push_back( B );
        }

        virtual std::vector<sf::Keyboard::Key> keys() const {
            std::vector<sf::Keyboard::Key> keys;
            keys.reserve( this->request.vitalKeys.size() );

            for ( const Request::kbBinding& B : this->request.vitalKeys )
                keys.push_back( B.key );

            return keys;
        }

        virtual std::vector<sf::Mouse::Button> buttons() const {
            std::vector<sf::Mouse::Button> buttons;
            buttons.reserve( this->request.vitalButtons.size() );

            for ( const Request::msBinding& B : this->request.vitalButtons )
                buttons.push_back( B.btn );

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