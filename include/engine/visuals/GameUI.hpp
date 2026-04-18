 #pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/System/Time.hpp>

#include <engine/visuals/BaseUI.hpp>
#include <engine/features/Progressive.hpp>


class GameUI : public BaseUI {
    friend class GameLayer;

    private:
        sf::Sprite bg;
        sf::Sprite pad;
        sf::Sprite ball;

        sf::Text countD;
        sf::Text score_1;
        sf::Text score_2;

        sf::Sound paddleSFX;
        sf::Sound wallSFX;

    protected:
        sf::Time _cdTime;
        bool P1_ready, P2_ready;

    private:
        GameUI();
        ~GameUI() = default;

        void update( const sf::Time& dt ) override;
        void configure( const std::optional<Progressive*>& ) override;
        void set_players_ready( const bool, const bool );
};