#include <engine/layers/MenuLayer.hpp>

#include <engine/visuals/MenuUI.hpp>
#include <engine/request/Request.hpp>

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

    this->form_request();

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

    for ( const sf::Sprite& btn : this->UI.btns )
        win.draw( btn );

        win.draw( this->UI.credit );
        win.draw( this->UI.version );
}

void MenuLayer::form_request() {
    // Keyboard requests
    this->requests.emplace_back( sf::Keyboard::Key::P, Action::raisePlay );
    this->requests.emplace_back( sf::Keyboard::Key::M, Action::raiseSett );
    this->requests.emplace_back( sf::Keyboard::Key::Q, Action::raiseQuit );

    // Mouse requests
    this->requests.emplace_back(
            sf::Mouse::Button::Left, Action::raisePlay
        ).require( Constraint::bounds( this->UI.btn_bound(0) ) );
    this->requests.emplace_back(
            sf::Mouse::Button::Left, Action::raiseSett
        ).require( Constraint::bounds( this->UI.btn_bound(1) ) );
    this->requests.emplace_back(
            sf::Mouse::Button::Left, Action::raiseQuit
        ).require( Constraint::bounds( this->UI.btn_bound(2) ) );
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