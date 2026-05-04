#include <engine/layers/EndLayer.hpp>

#include <tools/Tool.hpp>

#include <iostream>


EndLayer::EndLayer() : Layer(), UI() {
    this->UI.configure( std::nullopt );
}

void EndLayer::Load() {
    std::cout << "[EndLayer] Loading..\n";

    this->accTime = sf::Time::Zero;


    this->setRequest({
        { sf::Keyboard::Key::Enter, Action::dropOverlap },
        { sf::Keyboard::Key::Escape, Action::raiseMain }
    });

    std::cout << "[EndLayer] Loaded!\n";
}

void EndLayer::Update( const sf::Time& dt ) {
    accTime+=dt;

    if (accTime.asSeconds() >= 2.f) {
        std::cout << "[GameOver]\n";

        accTime = sf::Time::Zero;
    }
}

void EndLayer::Render( sf::RenderWindow& win ) const {
    win.draw( this->UI.bg );
    win.draw( this->UI.menu_btn );
    win.draw( this->UI.replay_btn );
    win.draw( this->UI.winner );
    // win.draw( this->UI.shadow );
}

void EndLayer::exit() {
    Tool::P1_SCORE = Tool::P2_SCORE = 0;
}

Layer::Type EndLayer::type() const { return Layer::Type::GameOver; }