#include <engine/layers/EndLayer.hpp>

#include <tools/Tool.hpp>

#include <iostream>


EndLayer::EndLayer() : Layer() {}

void EndLayer::Load() {
    std::cout << "[EndLayer] Loading..\n";

    this->accTime = sf::Time::Zero;

    this->bg.setRadius( 100.f );
    this->bg.setFillColor( sf::Color::White );
    this->bg.setOutlineColor( sf::Color::Black );
    this->bg.setOutlineThickness( 10.f );
    this->bg.setOrigin( {this->bg.getRadius(), this->bg.getRadius()} );
    this->bg.setPosition( Tool::W_CTR );

    std::cout << "[EndLayer] Loaded!\n";

    this->setRequest({
        { sf::Keyboard::Key::Enter, Action::dropOverlap },
        { sf::Keyboard::Key::Escape, Action::raiseMain }
    });
}

void EndLayer::Update( const sf::Time& dt ) {
    accTime+=dt;

    if (accTime.asSeconds() >= 2.f) {
        std::cout << "[GameOver]\n";

        accTime = sf::Time::Zero;
    }
}

void EndLayer::Render( sf::RenderWindow& win ) const { win.draw( bg ); }

void EndLayer::exit() {
    std::cout << "reseted\n\n";
    Tool::P1_SCORE = Tool::P2_SCORE = 0;
}

Layer::Type EndLayer::type() const { return Layer::Type::GameOver; }