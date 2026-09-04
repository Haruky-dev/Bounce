#include <Game.hpp>

#include <tools/Constants.hpp>
#include <tools/Json.hpp>

#include <span>


Game::Game() {
    this->window_ = std::make_unique<sf::RenderWindow>(
        sf::VideoMode( sf::Vector2u(Constants::WIDTH, Constants::HEIGHT) ),
        Json::String("win.title", Json::Type::SET ),
        sf::Style::Default & ~sf::Style::Resize
    );
    window_->setPosition(
        ( sf::Vector2i(sf::VideoMode::getDesktopMode().size) -
          sf::Vector2i(Constants::WIDTH, Constants::HEIGHT) )
        / 2 );
}

void Game::run() {
    while ( this->window_->isOpen() ) {
        this->pollEvents_();

        if ( this->onFocus_ )
            this->manager_.Update(
                this->clock_.restart(), std::span<sf::Event>(this->events_)
            );

        if ( this->manager_.quit_flag ) this->window_->close();

        this->window_->clear();

        this->manager_.Render( *this->window_ );

        this->window_->display();
    }

}

void Game::pollEvents_() {
    this->events_.clear();

    while ( const std::optional<sf::Event> ev = this->window_->pollEvent() ) {
        if ( ev->is<sf::Event::FocusGained>() ) this->onFocus_ = true;
        else if ( ev->is<sf::Event::FocusLost>() ) this->onFocus_ = false;

        if ( this->onFocus_ )
            this->events_.push_back( *ev );
    }
}