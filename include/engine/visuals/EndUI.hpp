#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Color.hpp>

#include <array>

#include <engine/visuals/BaseUI.hpp>
#include <engine/features/Progressive.hpp>

#include <engine/features/Animation.hpp>


class EndUI : public BaseUI {
    friend class EndLayer;

    private:
        static constexpr int BTN_COUNT = 2;
        sf::Sprite bg, winner;

        std::array<sf::Rect<int>, BTN_COUNT> bounds;
        std::array<sf::Text, 2> scores;

        Animation animation;

    private:
         sf::Vector2<float>      __normalize( const sf::Vector2<int>& ) const;
         std::array<sf::Text, 2> __init_scores() const;

    public:
        EndUI();
        ~EndUI() = default;

        void update( const sf::Time& ) override;
        void configure( const std::optional<Progressive*>& ) override;
};
