#include <engine/layers/PauseLayer.hpp>

#include <tools/Math.hpp>
#include <engine/input/Process.hpp>


PauseLayer::PauseLayer() : Layer()
    {
        this->UI.configure();
}

void PauseLayer::Load() {
    this->form_request();
}

void PauseLayer::Update( const sf::Time& dt ) {
    this->UI.update( dt );
}

void PauseLayer::Render( sf::RenderWindow& win ) const {
    win.draw( this->UI.shadow );
    win.draw( this->UI.bg );
    for ( int i = 0; i < this->UI.BTN_COUNT; i++ )
        win.draw( this->UI.buttons.at( i ) );
}

void PauseLayer::form_request() {
    // Keyboard __requests
    this->__requests.emplace_back( sf::Keyboard::Key::Enter, Process::Action::dropOverlap );
    this->__requests.emplace_back( sf::Keyboard::Key::Escape, Process::Action::raiseMain );

    // Mouse __requests
    this->__requests.emplace_back(
            sf::Mouse::Button::Left, Process::Action::dropOverlap
        ).require( Constraint::bounds( this->UI.bounds.at(PauseUI::BTNS::RESUME) ),
            Constraint::predicate( [this]() { return this->UI.animation.finished(); })
    );
    this->__requests.emplace_back(
            sf::Mouse::Button::Left, Process::Action::raiseMain
        ).require( Constraint::bounds( this->UI.bounds.at(PauseUI::BTNS::QUIT) ),
            Constraint::predicate( [this]() { return this->UI.animation.finished(); })
    );
}

bool PauseLayer::animated() const { return true; }

void PauseLayer::exit() { this->UI.exit_animation(); }

bool PauseLayer::popable() const { return this->UI.animation.finished(); }

Layer::Type PauseLayer::type() const { return Layer::Type::Pause; }
