#include <engine/layers/PauseLayer.hpp>

#include <tools/Math.hpp>
#include <engine/io/Action.hpp>


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
    // Keyboard requests_
    this->requests_.emplace_back( sf::Keyboard::Key::Enter, Action::dropOverlap );
    this->requests_.emplace_back( sf::Keyboard::Key::Escape, Action::raiseMain );

    // Mouse requests_
    this->requests_.emplace_back(
            sf::Mouse::Button::Left, Action::dropOverlap
        ).require( Constraint::bounds( this->UI.bounds.at(PauseUI::BTNS::RESUME) ) );
    this->requests_.emplace_back(
            sf::Mouse::Button::Left, Action::raiseMain
        ).require( Constraint::bounds( this->UI.bounds.at(PauseUI::BTNS::QUIT) ) );
}

bool PauseLayer::animated() const { return true; }

void PauseLayer::enter() { SFX::inst().play(SFX::Type::WHOOSH); }
void PauseLayer::exit() { this->UI.exit_animation(); }

bool PauseLayer::popable() const { return this->UI.animation.finished(); }

Layer::Type PauseLayer::type() const { return Layer::Type::Pause; }
