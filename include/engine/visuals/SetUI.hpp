#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include <engine/visuals/BaseUI.hpp>
#include <engine/features/Animation.hpp>
#include <engine/features/Progressive.hpp>


class SetUI : public BaseUI {
    friend class SetLayer;

    private:
        sf::Sprite bg, shadow;

        Animation animation;

        float bg_init_y;

    private:
        SetUI();
        ~SetUI() = default;

        void update( const sf::Time& ) override;
        void configure( const std::optional<Progressive*>& ) override;

        void exit_animation();
        const bool anim_finished() const;
};
