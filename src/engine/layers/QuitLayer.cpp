#include <engine/layers/QuitLayer.hpp>


QuitLayer::QuitLayer() : Layer(), accTime(sf::Time::Zero), T(std::chrono::seconds(2)) {
    this->UI.configure();
}

void QuitLayer::Load() {}

void QuitLayer::Update( const sf::Time& dt ) {
    this->UI.update(dt);
    this->accTime += dt;
}

void QuitLayer::Render( sf::RenderWindow& win ) const {
    win.draw( this->UI.shadow );
    win.draw( this->UI.bg );
}

Action QuitLayer::feature() const {
    if ( this->accTime.asSeconds() >= this->T.count() )
        return Action::QUIT;

    return Action::None;
}
bool QuitLayer::animated() const { return true; }
bool QuitLayer::popable()  const { return this->UI.animation.finished(); }
void QuitLayer::exit()           { this->UI.animation.finished(); }

Layer::Type QuitLayer::type() const { return Layer::Type::Quit; }