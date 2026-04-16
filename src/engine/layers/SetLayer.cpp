#include <engine/layers/SetLayer.hpp>

#include <cstdint>

#include <tools/Tool.hpp>
#include <tools/Math.hpp>


SetLayer::SetLayer() : Layer(), Animated()
    {
        this->UI.configure( std::nullopt );
}

void SetLayer::Load() {
    this->setRequest({
        { sf::Keyboard::Key::Enter, Action::dropOverlap }
    });
}

void SetLayer::Update( sf::Time& dt ) {    
    animation.update( dt );
    
    if ( !(this->isExited()) )
        this->animation.forward();   

    float y = Math::Lerp(
        this->UI.bg_initY,
        Tool::W_CTR.y,
        Math::easeOut( this->animation.prog() )
    );
    this->UI.shadClr.a = static_cast<std::uint8_t>(
        255 * Math::easeInOut( this->animation.prog() )
    );

    this->UI.bg.setPosition( {this->UI.bg.getPosition().x, y} );
    this->UI.shad.setColor( this->UI.shadClr );

    if ( this->animation.finished()
        && this->animation.onReverse() ) {
            this->setDone( true );
    }
}

void SetLayer::Render( sf::RenderWindow& win ) const {
    win.draw( this->UI.shad );
    win.draw( this->UI.bg );
}

void SetLayer::exit() {
    this->setExit( true );
    this->animation.backward();
}

bool SetLayer::popable() const {
    return this->isDone();
}

Layer::Type SetLayer::getType() const { return Layer::Type::Setting; }