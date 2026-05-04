#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Color.hpp>

#include <engine/visuals/BaseUI.hpp>
#include <engine/features/Progressive.hpp>


class EndUI : public BaseUI {
    friend class EndLayer;

    private:
        sf::Sprite bg, winner, menu_btn, replay_btn;
        sf::Text human_score, ai_score;
        // sf::Sprite shadow;
        // sf::Color shadow_clr;
        // 
    private:
        void relative_place( sf::Sprite&, const sf::Vector2<float>& );

    public:
        EndUI();
        ~EndUI() = default;

        void update( const sf::Time& ) override {}
        void configure( const std::optional<Progressive*>& ) override;
};