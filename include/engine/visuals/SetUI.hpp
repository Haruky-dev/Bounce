#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Text.hpp>

#include <map>
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
        sf::Rect<int> bg_rect;
        std::array<sf::Sprite, 2> marks_spr;
        std::array<sf::Sprite, 3> modes_spr;
        std::unordered_map< SetUI::BTNS, sf::Rect<int> > bounds;
        std::map<char, int> modes_i;

        sf::Text max_score;

        Animation animation;

        float bg_init_y;

    private:
        std::array<sf::Sprite, 3> __init_modes() const;
        std::array<sf::Sprite, 2> __init_marks() const;
        void __init_bounds();
        void __move_elements();

    private:
        SetUI();
        ~SetUI() = default;

        void update( const sf::Time& ) override;
        void configure( const std::optional<Progressive*>& ) override;

        void exit_animation();
};