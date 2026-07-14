#include <engine/layers/EndLayer.hpp>

#include <tools/Tool.hpp>

#include <iostream>


EndLayer::EndLayer() : Layer(), UI() {
    this->UI.configure( std::nullopt );
}

void EndLayer::Load() {
    std::cout << "[EndLayer] Loading..\n";

    this->accTime = sf::Time::Zero;

    this->form_request();

    std::cout << "[EndLayer] Loaded!\n";
}

void EndLayer::Update( const sf::Time& dt ) {
    this->UI.update( dt );
    accTime+=dt;

    if (accTime.asSeconds() >= 2.f) {
        std::cout << "[GameOver]\n";

        accTime = sf::Time::Zero;
    }
}

void EndLayer::Render( sf::RenderWindow& win ) const {
    win.draw( this->UI.bg );
    win.draw( this->UI.winner );
    win.draw( this->UI.scores.at(0) );
    win.draw( this->UI.scores.at(1) );
}

void EndLayer::form_request() {
    // Keyboard requests
    this->requests.emplace_back( sf::Keyboard::Key::Enter, Action::dropOverlap );
    this->requests.emplace_back( sf::Keyboard::Key::Escape, Action::raiseMain );

    // Mouse requests
    this->requests.emplace_back(
            sf::Mouse::Button::Left, Action::dropOverlap
        ).require( Constraint::bounds( this->UI.bounds.at(EndUI::BTNS::QUIT) ) );
    this->requests.emplace_back(
            sf::Mouse::Button::Left, Action::raiseMain
        ).require( Constraint::bounds( this->UI.bounds.at(EndUI::BTNS::RESTART) ) );
}

bool EndLayer::animated() const { return true; }
bool EndLayer::popable() const { return this->UI.animation.finished(); }
void EndLayer::exit() {
    Tool::P1_SCORE = Tool::P2_SCORE = 0;
}

Layer::Type EndLayer::type() const { return Layer::Type::GameOver; }
