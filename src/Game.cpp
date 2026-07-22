#include <Game.hpp>

#include <tools/Constants.hpp>
#include <tools/Json.hpp>

#include <span>


Game::Game() {
    this->_window = std::make_unique<sf::RenderWindow>(
        sf::VideoMode( sf::Vector2u(Constants::WIDTH, Constants::HEIGHT) ),
        Json::String("win.title"),
        sf::Style::Default & ~sf::Style::Resize
    );
    _window->setPosition(
        ( sf::Vector2i(sf::VideoMode::getDesktopMode().size) -
          sf::Vector2i(Constants::WIDTH, Constants::HEIGHT) )
        / 2 );
}

void Game::run() {
    while ( this->_window->isOpen() ) {
        this->_pollEvents();

        if ( this->_onFocus )
            this->_manager.Update(
                this->_clock.restart(), std::span<sf::Event>(this->_events)
            );

        if ( this->_manager.quit_flag ) this->_window->close();

        this->_window->clear();

        this->_manager.Render( *this->_window );

        this->_window->display();
    }

}

void Game::_pollEvents() {
    this->_events.clear();

    while ( const std::optional<sf::Event> ev = this->_window->pollEvent() ) {
        if ( ev->is<sf::Event::FocusGained>() ) this->_onFocus = true;
        else if ( ev->is<sf::Event::FocusLost>() ) this->_onFocus = false;

        if ( this->_onFocus )
            this->_events.push_back( *ev );
    }
}
