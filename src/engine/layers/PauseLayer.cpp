#include <engine/layers/PauseLayer.hpp>

#include <tools/Math.hpp>
#include <engine/input/Action.hpp>

#include <iostream>


PauseLayer::PauseLayer() : Layer(), Animation()
    {
        this->UI.configure( std::nullopt );
}

void PauseLayer::Load() {
    std::cout << "[Pause] Loading..\n";

    this->accTime = sf::Time::Zero;

    this->setRequest({
        { sf::Keyboard::Key::Enter, Action::dropOverlap },
        { sf::Keyboard::Key::Escape, Action::raiseMain },
    });
    this->setRequest({
        { sf::Mouse::Button::Left, Action::dropOverlap, this->UI.btn_bound(0) },
        { sf::Mouse::Button::Left, Action::raiseMain, this->UI.btn_bound(1) }

    });

    std::cout << "[Pause] Loaded!\n";
}

void PauseLayer::Update( const sf::Time& dt ) {
    this->UI.update( dt );

    accTime+=dt;
    if (accTime.asSeconds() > 2.0f) {
        std::cout << "[Pause]\n";
        accTime = sf::Time::Zero;
    }
}

void PauseLayer::Render( sf::RenderWindow& win ) const {
    win.draw( this->UI.shadow );
    win.draw( this->UI.bg );
    for ( int i = 0; i < this->UI.BTN_COUNT; i++ )
        win.draw( this->UI.buttons.at( i ) );
}

bool PauseLayer::animated() const { return true; }

void PauseLayer::exit() { this->UI.exit_animation(); }

bool PauseLayer::popable() const { return this->UI.animation.finished(); }

Layer::Type PauseLayer::type() const { return Layer::Type::Pause; }
