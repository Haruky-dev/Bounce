#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Text.hpp>

#include <array>
#include <unordered_map>

#include <engine/visuals/BaseUI.hpp>
#include <engine/features/Animation.hpp>
#include <engine/features/Progressive.hpp>


class SetUI : public BaseUI {
    friend class SetLayer;

    private:
        enum class BTNS {
            DIF_ARW_INC,
            DIF_ARW_DEC,
            SCR_ARW_INC,
            SCR_ARW_DEC,
            MUSIC_MARK,
            SFX_MARK,
            EXIT
        };

        sf::Sprite bg, shadow;
        std::array<sf::Sprite, 2> marks_spr;
        std::array<sf::Sprite, 3> modes_spr;
        std::unordered_map< SetUI::BTNS, sf::Rect<int> > bounds;
        // std::array<sf::Rect<int>, 2>
        //     modes_arrow,
        //     score_arrow,
        //     marks_box;
        // sf::Rect<int> exit_btn;

        sf::Text max_score;

        Animation animation;

        float bg_init_y;

    private:
        sf::Vector2<int>        __normalize( const sf::Vector2<int>& ) const;
        std::array<sf::Sprite, 3> __init_modes() const;
        std::array<sf::Sprite, 2> __init_marks() const;
        void __init_bounds();

    private:
        SetUI();
        ~SetUI() = default;

        void update( const sf::Time& ) override;
        void configure( const std::optional<Progressive*>& ) override;

        void exit_animation();
        const bool anim_finished() const;
};
