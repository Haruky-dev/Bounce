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
        std::unique_ptr<sf::RenderWindow> window_;
        std::vector<sf::Event> events_;
        sf::Clock clock_;
        Manager manager_;
        bool onFocus_;

    private:
        void update_( const sf::Time& );
        void pollEvents_();
        void render_() const;

    public:
        Game();
        void run();
};