#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include <engine/visuals/BaseUI.hpp>
#include <engine/features/Animation.hpp>
#include <engine/features/Progressive.hpp>


class PauseUI : public BaseUI {
    friend class PauseLayer;

    private:
        sf::Sprite bg;
        sf::Sprite shadow;
        sf::Color shadow_clr; // tweak opacity
        sf::Color bg_clr;

        Animation animation;

        float bg_init_y;

    private:
        PauseUI();
        ~PauseUI() = default;

        void update( const sf::Time& ) override;
        void configure( const std::optional<Progressive*>& ) override;

        void exit_animation();
        const bool anim_finished() const;
};
