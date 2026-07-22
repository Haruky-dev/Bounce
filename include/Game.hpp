#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include <engine/Manager.hpp>

#include <memory>
#include <vector>


class Game {
    private:
        std::unique_ptr<sf::RenderWindow> _window;
        std::vector<sf::Event> _events;
        sf::Clock _clock;
        Manager _manager;
        bool _onFocus;

    private:
        void _update( const sf::Time& );
        void _pollEvents();
        void _render() const;

    public:
        Game();
        void run();
};