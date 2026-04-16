#include <engine/layers/MenuLayer.hpp>

#include <cache/UICache.hpp>
#include <cache/visuals/MenuUI.hpp>
#include <engine/input/Request.hpp>

#include <cache/SoundCache.hpp>

#include <iostream>


MenuLayer::MenuLayer() :
    Layer(),
    UI( UICache::inst().deploy<MenuUI>() )
{}

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
        { sf::Keyboard::Key::Q, Action::raiseQuit }
    });
    this->setRequest({
        { sf::Mouse::Button::Left, Action::raisePlay, UI.btnBound( 0 ) },
        { sf::Mouse::Button::Left, Action::raiseSett, UI.btnBound( 1 ) },
        { sf::Mouse::Button::Left, Action::raiseQuit, UI.btnBound( 2 ) }
    });

    std::cout << "[MenuLayer] Loaded!\n";
}

void MenuLayer::Update( sf::Time& dt ) {
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
    win.draw( UI.bg );

    for (int i = 0; i < UI.nBtns(); i++)
        win.draw( UI.btns.at( i ) );

    win.draw( UI.author );
    win.draw( UI.version );
}

Layer::Type MenuLayer::getType() const { return Layer::Type::MainMenu; }

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