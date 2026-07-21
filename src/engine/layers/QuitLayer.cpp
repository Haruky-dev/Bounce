#include <engine/layers/QuitLayer.hpp>


QuitLayer::QuitLayer() : Layer(), accTime(sf::Time::Zero), T(std::chrono::seconds(2)) {
    this->UI.configure();
}

void QuitLayer::Load() {
    this->__requests.emplace_back(
        sf::Keyboard::Key::C, Process::Action::dropOverlap, SFX::Type::WHOOSH
    );
    this->__requests.emplace_back( 
        sf::Mouse::Button::Left, Process::Action::dropOverlap, SFX::Type::WHOOSH
    ).require( Constraint::bounds( this->UI.bounds.at(QuitUI::BTNS::CANCEL)) );
}

void QuitLayer::Update( const sf::Time& dt ) {
    this->UI.update(dt);

    if ( this->UI.animation.finished() )
        this->accTime += dt;
}

void QuitLayer::Render( sf::RenderWindow& win ) const {
    win.draw( this->UI.shadow );
    win.draw( this->UI.bg );
}

Process QuitLayer::feature() const {
    if ( this->accTime.asSeconds() >= this->T.count() )
        return Process(Process::Action::Quit);

    return Process();
}
bool QuitLayer::animated() const { return true; }
bool QuitLayer::popable()  const { return this->UI.animation.finished(); }
void QuitLayer::exit()           { this->UI.exit_animation(); }

Layer::Type QuitLayer::type() const { return Layer::Type::Quit; }