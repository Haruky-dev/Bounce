#include <engine/layers/EndLayer.hpp>

#include <tools/Variables.hpp>


EndLayer::EndLayer() : Layer(), UI() {
    this->UI.configure();
}

void EndLayer::Load() {
    this->form_request();
}

void EndLayer::Update( const sf::Time& dt ) {
    this->UI.update( dt );
}

void EndLayer::Render( sf::RenderWindow& win ) const {
    win.draw( this->UI.shadow );
    win.draw( this->UI.bg );
    win.draw( this->UI.winner );
    win.draw( this->UI.scores.at(0) );
    win.draw( this->UI.scores.at(1) );
}

void EndLayer::form_request() {
    // Keyboard __requests
    this->__requests.emplace_back( sf::Keyboard::Key::Enter, Action::dropOverlap );
    this->__requests.emplace_back( sf::Keyboard::Key::Escape, Action::raiseMain );

    // Mouse __requests
    this->__requests.emplace_back(
            sf::Mouse::Button::Left, Action::dropOverlap
        ).require( Constraint::bounds( this->UI.bounds.at(EndUI::BTNS::QUIT) ) );
    this->__requests.emplace_back(
            sf::Mouse::Button::Left, Action::raiseMain
        ).require( Constraint::bounds( this->UI.bounds.at(EndUI::BTNS::RESTART) ) );
}

bool EndLayer::animated() const { return true; }
bool EndLayer::popable() const { return this->UI.animation.finished(); }
void EndLayer::enter() { SFX::inst().play(SFX::Type::WHOOSH); }
void EndLayer::exit() {
    Variables::P1_SCORE = Variables::P2_SCORE = 0;
}

Layer::Type EndLayer::type() const { return Layer::Type::GameOver; }