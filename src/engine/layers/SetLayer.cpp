#include <engine/layers/SetLayer.hpp>


#include <tools/Constants.hpp>
#include <tools/Flags.hpp>
#include <tools/Math.hpp>

    
SetLayer::SetLayer() : Layer()
    {
        this->UI.configure();
}

void SetLayer::Load() {
    this->form_request();
}

void SetLayer::Update( const sf::Time& dt ) {
    this->UI.update( dt );
}

void SetLayer::Render( sf::RenderWindow& win ) const {
    win.draw( this->UI.shadow );
    win.draw( this->UI.bg );

    win.draw( this->UI.modes_spr.at(this->UI.modes_i.at(Constants::MODE.at(0))) );
    win.draw( this->UI.max_score );

    if (Flags::musicON) win.draw( this->UI.marks_spr.at(0) );
    if (Flags::sfxON) win.draw( this->UI.marks_spr.at(1) );
}

void SetLayer::form_request() {
    // Keyboard __requests
    this->__requests.emplace_back( sf::Keyboard::Key::Enter, Action::dropOverlap );

    // Mouse __requests
    this->__requests.emplace_back(
            sf::Mouse::Button::Left, Action::dropOverlap
        ).require( Constraint::bounds( this->UI.bounds.at(SetUI::BTNS::EXIT) ) );
    this->__requests.emplace_back(
            sf::Mouse::Button::Left, Action::incMaxScr
        ).require( Constraint::bounds( this->UI.bounds.at(SetUI::BTNS::SCR_ARW_INC)),
                Constraint::cooldown(Constants::DELAY_t) );
    this->__requests.emplace_back(
            sf::Mouse::Button::Left, Action::decMaxScr
        ).require( Constraint::bounds( this->UI.bounds.at(SetUI::BTNS::SCR_ARW_DEC) ),
                Constraint::cooldown(Constants::DELAY_t) );
    this->__requests.emplace_back(
            sf::Mouse::Button::Left, Action::incDiff
        ).require( Constraint::bounds( this->UI.bounds.at(SetUI::BTNS::DIF_ARW_INC)),
                Constraint::cooldown(Constants::DELAY_t) );
    this->__requests.emplace_back(
            sf::Mouse::Button::Left, Action::decDiff
        ).require( Constraint::bounds( this->UI.bounds.at(SetUI::BTNS::DIF_ARW_DEC)),
                Constraint::cooldown(Constants::DELAY_t) );
    this->__requests.emplace_back(
            sf::Mouse::Button::Left, Action::toggleMusic
        ).require( Constraint::bounds(this->UI.bounds.at(SetUI::BTNS::MUSIC_MARK)),
                Constraint::cooldown(Constants::DELAY_t) );
    this->__requests.emplace_back(
            sf::Mouse::Button::Left, Action::toggleSFX
        ).require( Constraint::bounds(this->UI.bounds.at(SetUI::BTNS::SFX_MARK)),
                Constraint::cooldown(Constants::DELAY_t) );
}
bool SetLayer::animated() const { return true; }

void SetLayer::enter() { SFX::inst().play(SFX::Type::WHOOSH); }
void SetLayer::exit() { this->UI.exit_animation(); }

bool SetLayer::popable() const { return this->UI.animation.finished(); }

Layer::Type SetLayer::type() const { return Layer::Type::Setting; }