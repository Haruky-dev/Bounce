#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <engine/Manager.hpp>
#include <tools/Constants.hpp>
#include <tools/Json.hpp>

#include <memory>


int main( void ) {

    std::unique_ptr<sf::RenderWindow> win;
    win = std::make_unique<sf::RenderWindow>(
        sf::VideoMode( sf::Vector2u(Constants::WIDTH, Constants::HEIGHT) ),
        Json::String("win.title"),
        sf::Style::Default & ~sf::Style::Resize
    );

    // center win
    win->setPosition(
        ( sf::Vector2i(sf::VideoMode::getDesktopMode().size) -
          sf::Vector2i({Constants::WIDTH, Constants::HEIGHT}) )
        / 2);
    
    Manager manager{};

    sf::Clock clk{};
    sf::Time dt = sf::Time::Zero;

    bool onFocus = true;

    while ( win->isOpen() ) {
        dt = clk.restart();

        while ( const std::optional<sf::Event> ev = win->pollEvent() ) {
            if ( ev->is<sf::Event::FocusGained>() )
                onFocus = true;
            else if ( ev->is<sf::Event::FocusLost>() )
                onFocus = false;

            if (onFocus) {
                if ( ev->is<sf::Event::Closed>() )
                    win->close();
            }
        }

        if (onFocus) manager.Update( dt, *win );

        if ( manager.quit_flag ) win->close();

        win->clear();

        manager.Render( *win );

        win->display();
    }

    return 0; 
}