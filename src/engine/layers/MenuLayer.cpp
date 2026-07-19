#include <engine/layers/MenuLayer.hpp>

#include <engine/visuals/MenuUI.hpp>
#include <engine/request/Request.hpp>
#include <tools/Flags.hpp>



MenuLayer::MenuLayer() : Layer() {
    this->UI.configure();
}

void MenuLayer::Load() {
    this->music = std::make_unique<sf::Music>();
    if (!(this->music->openFromFile( "assets/musics/Yoshis_Story-Games_of_Happiness.ogg" )))
        throw std::runtime_error("Failure");

    this->music->setLooping( true );
    this->music->setVolume(100);

    this->form_request();
}

void MenuLayer::Update( const sf::Time& dt ) {
    if ( this->music->getStatus() != sf::Music::Status::Playing || !(Flags::musicON) ) {
        this->music->play();
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
    this->requests.emplace_back( sf::Keyboard::Key::P, Process::Action::raisePlay );
    this->requests.emplace_back( sf::Keyboard::Key::M, Process::Action::raiseSett );
    this->requests.emplace_back( sf::Keyboard::Key::Q, Process::Action::raiseQuit );

    // Mouse requests
    this->requests.emplace_back(
            sf::Mouse::Button::Left, Process::Action::raisePlay
        ).require( Constraint::bounds( this->UI.bounds.at(MenuUI::BTNS::PLAY) ) );
    this->requests.emplace_back(
            sf::Mouse::Button::Left, Process::Action::raiseSett
        ).require( Constraint::bounds( this->UI.bounds.at(MenuUI::BTNS::MENU) ) );
    this->requests.emplace_back(
            sf::Mouse::Button::Left, Process::Action::raiseQuit
        ).require( Constraint::bounds( this->UI.bounds.at(MenuUI::BTNS::QUIT) ) );
}

Layer::Type MenuLayer::type() const { return Layer::Type::MainMenu; }

void MenuLayer::enter() {
    // Constants::P1_SCORE = Constants::P2_SCORE = 0;
    // Constants::CD = 0; // wtf? should perhaps be on GameLayer::exit() or something
}

void MenuLayer::exit() {
    this->music.reset();
}

void MenuLayer::pause() {
    if ( this->music->getStatus() != sf::Music::Status::Stopped )
        this->music->setVolume( 40.f );
}