#include <engine/layers/EndLayer.hpp>

#include <tools/Constants.hpp>


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
    // Keyboard requests
    this->requests.emplace_back( sf::Keyboard::Key::Enter, Process::Action::dropOverlap );
    this->requests.emplace_back( sf::Keyboard::Key::Escape, Process::Action::raiseMain );

    // Mouse requests
    this->requests.emplace_back(
            sf::Mouse::Button::Left, Process::Action::dropOverlap
        ).require( Constraint::bounds( this->UI.bounds.at(EndUI::BTNS::QUIT) ),
                Constraint::predicate( [this]() { return this->UI.animation.finished(); })
        );
    this->requests.emplace_back(
            sf::Mouse::Button::Left, Process::Action::raiseMain
        ).require( Constraint::bounds( this->UI.bounds.at(EndUI::BTNS::RESTART) ),
                Constraint::predicate( [this]() { return this->UI.animation.finished(); })
        );
}

bool EndLayer::animated() const { return true; }
bool EndLayer::popable() const { return this->UI.animation.finished(); }
void EndLayer::exit() {
    Constants::P1_SCORE = Constants::P2_SCORE = 0;
}

Layer::Type EndLayer::type() const { return Layer::Type::GameOver; }
