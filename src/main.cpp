#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <engine/Manager.hpp>
#include <tools/Tool.hpp>
#include <tools/Json.hpp>

#include <memory>


int main( void ) {

    std::unique_ptr<sf::RenderWindow> win;
    win = std::make_unique<sf::RenderWindow>(
        sf::VideoMode( sf::Vector2u(Tool::WIDTH, Tool::HEIGHT) ),
        Json::String("win.title"),
        sf::Style::Default & ~sf::Style::Resize
    );

    // center win
    win->setPosition(
        ( sf::Vector2i(sf::VideoMode::getDesktopMode().size) -
          sf::Vector2i({Tool::WIDTH, Tool::HEIGHT}) )
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
                else if ( ev->is<sf::Event::KeyPressed>() ) {
                    if ( ev->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Q ) 
                        win->close();

                // DBG: refresh conf.json
                    else if ( ev->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::R )
                        Json::reLoad();
                }
            }
        }

        if (onFocus) manager.Update( dt, *win );

        win->clear();

        manager.Render( *win );

        win->display();
    }

    return 0; 
}