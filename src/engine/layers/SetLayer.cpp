#include <engine/layers/SetLayer.hpp>


#include <tools/Tool.hpp>
#include <tools/Math.hpp>

    
SetLayer::SetLayer() : Layer(), Animation()
    {
        this->UI.configure( std::nullopt );
}

void SetLayer::Load() {
    this->setRequest({
        { sf::Keyboard::Key::Enter, Action::dropOverlap }
    });
    this->setRequest({
        { sf::Mouse::Button::Left, Action::dropOverlap, this->UI.bounds.at( SetUI::BTNS::EXIT ) },
        { sf::Mouse::Button::Left, Action::incMaxScr, this->UI.bounds.at( SetUI::BTNS::SCR_ARW_INC) },
        { sf::Mouse::Button::Left, Action::decMaxScr, this->UI.bounds.at( SetUI::BTNS::SCR_ARW_DEC) },
        { sf::Mouse::Button::Left, Action::incDiff, this->UI.bounds.at( SetUI::BTNS::DIF_ARW_INC) },
        { sf::Mouse::Button::Left, Action::decDiff, this->UI.bounds.at( SetUI::BTNS::DIF_ARW_DEC) },
    });
}

void SetLayer::Update( const sf::Time& dt ) {
    this->UI.update( dt );
}

void SetLayer::Render( sf::RenderWindow& win ) const {
    win.draw( this->UI.shadow );
    win.draw( this->UI.bg );

    win.draw( this->UI.modes_spr.at(
        (Tool::MODE=="hard")? 2
        : (Tool::MODE=="even")? 1
        : (Tool::MODE=="easy")? 0 : 2
    ) );
}

bool SetLayer::animated() const { return true; }

void SetLayer::exit() { this->UI.exit_animation(); }

bool SetLayer::popable() const { return this->UI.anim_finished(); }

Layer::Type SetLayer::type() const { return Layer::Type::Setting; }