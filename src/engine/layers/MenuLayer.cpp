#include <engine/layers/MenuLayer.hpp>

#include <engine/visuals/MenuUI.hpp>
#include <engine/input/Request.hpp>

#include <cache/SoundCache.hpp>

#include <iostream>


MenuLayer::MenuLayer() : Layer() {

    this->UI.configure( std::nullopt );
}

void MenuLayer::Load() {
    std::cout << "[MenuLayer] Loading..\n";

    this->accTime = sf::Time::Zero;

    this->music = std::make_unique<sf::Music>();
    if (!(this->music->openFromFile( "assets/musics/Yoshis_Story-Games_of_Happiness.ogg" )))
        throw std::runtime_error("Failure");

    this->music->setLooping( true );
    this->music->setVolume(20);

    this->setRequest({
        { sf::Keyboard::Key::P, Action::raisePlay },
        { sf::Keyboard::Key::M, Action::raiseSett },
        { sf::Keyboard::Key::Q, Action::raiseQuit },

        { sf::Keyboard::Key::H, Action::raiseHold }
    });
    this->setRequest({
        { sf::Mouse::Button::Left, Action::raisePlay, UI.btn_bound( 0 ) },
        { sf::Mouse::Button::Left, Action::raiseSett, UI.btn_bound( 1 ) },
        { sf::Mouse::Button::Left, Action::raiseQuit, UI.btn_bound( 2 ) }
    });

    std::cout << "[MenuLayer] Loaded!\n";
}

void MenuLayer::Update( const sf::Time& dt ) {
    if (this->music->getStatus() != sf::Music::Status::Playing) {
        this->music->play();
    }

    this->accTime+=dt;
    if (accTime.asSeconds() >= 2.0f) {
        std::cout << "[MenuLayer]\n";
        accTime = sf::Time::Zero;
    }
}

void MenuLayer::Render( sf::RenderWindow& win ) const {
    win.draw( this->UI.bg );

    for (int i = 0; i < this->UI.BTN_COUNT; i++)
        win.draw( this->UI.btns.at( i ) );

    win.draw( this->UI.credit );
    win.draw( this->UI.version );
}

Layer::Type MenuLayer::type() const { return Layer::Type::MainMenu; }

void MenuLayer::enter() {
    Tool::P1_SCORE = Tool::P2_SCORE = 0;
}

void MenuLayer::exit() {
    this->music.reset();
}

void MenuLayer::pause() {
    if ( this->music->getStatus() != sf::Music::Status::Stopped )
        this->music->setVolume( 40.f );
}
