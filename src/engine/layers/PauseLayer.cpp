#include <engine/features/Animated.hpp>
#include <engine/layers/PauseLayer.hpp>

#include <tools/Math.hpp>
#include <engine/input/Action.hpp>

#include <iostream>


PauseLayer::PauseLayer() : Layer(), Animated()
    {
        this->UI.configure( std::nullopt );
}

void PauseLayer::Load() {
    std::cout << "[Pause] Loading..\n";

    this->accTime = sf::Time::Zero;

    this->setRequest({
        { sf::Keyboard::Key::Enter, Action::dropOverlap },
        { sf::Keyboard::Key::Escape, Action::raiseMain }
    });

    std::cout << "[Pause] Loaded!\n";
}

void PauseLayer::Update( const sf::Time& dt ) {
    this->animation.update( dt );

    accTime+=dt;
    if (accTime.asSeconds() > 2.0f) {
        std::cout << "[Pause]\n";
        accTime = sf::Time::Zero;
    }

    if ( !(this->isExited()) )
        this->animation.forward();

    // CONF
    float y = Math::Lerp(
        this->UI.bg_initY,
        Tool::W_CTR.y,
        Math::easeOut( animation.prog() )
    );
    this->UI.shadClr.a = static_cast<std::uint8_t>(
        180 * Math::easeInOut( this->animation.prog() )
    );
    this->UI.bgClr.a = static_cast<std::uint8_t>(
        255 * Math::easeInOut( this->animation.prog() )
    );

    // SET
    this->UI.bg.setPosition( {this->UI.bg.getPosition().x, y} );
    this->UI.bg.setColor( this->UI.bgClr );
    this->UI.shad.setColor( this->UI.shadClr );

    // ANIM END
    if ( this->animation.finished()
        && this->animation.onReverse() ) {
            this->setDone( true );
    }
}

void PauseLayer::Render( sf::RenderWindow& win ) const {
    win.draw( this->UI.shad );
    win.draw( this->UI.bg );
}

bool PauseLayer::animated() const { return true; }

void PauseLayer::exit() {
    this->setExit( true );
    this->animation.backward();
}

bool PauseLayer::popable() const {
    return this->isDone();
}

Layer::Type PauseLayer::type() const { return Layer::Type::Pause; }