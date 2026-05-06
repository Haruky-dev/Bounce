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
}

void SetLayer::Update( const sf::Time& dt ) {
    this->UI.update( dt );
}

void SetLayer::Render( sf::RenderWindow& win ) const {
    win.draw( this->UI.shadow );
    win.draw( this->UI.bg );
}

bool SetLayer::animated() const { return true; }

void SetLayer::exit() { this->UI.exit_animation(); }

bool SetLayer::popable() const { return this->UI.anim_finished(); }

Layer::Type SetLayer::type() const { return Layer::Type::Setting; }