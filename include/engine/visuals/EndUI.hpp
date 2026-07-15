#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Color.hpp>

#include <array>

#include <engine/visuals/BaseUI.hpp>

#include <engine/features/Animation.hpp>


class EndUI : public BaseUI {
    friend class EndLayer;

    private:
        enum class BTNS {
            QUIT,
            RESTART
        };
        static constexpr int BTN_COUNT = 2;
        sf::Sprite bg, shadow, winner;
        sf::Rect<int> bg_rect;

        std::unordered_map<EndUI::BTNS, sf::Rect<int>> bounds;
        std::array<sf::Text, 2> scores;

        Animation animation;

    private:
         std::array<sf::Text, 2> __init_scores();

    public:
        EndUI();
        ~EndUI() = default;

        void update( const sf::Time& ) override;
        void configure() override;
};
