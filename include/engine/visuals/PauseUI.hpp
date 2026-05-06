#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>

#include <array>

#include <engine/visuals/BaseUI.hpp>
#include <engine/features/Animation.hpp>
#include <engine/features/Progressive.hpp>
#include <cache/TextureCache.hpp>


class PauseUI : public BaseUI {
    friend class PauseLayer;

    private:
        static constexpr int BTN_COUNT = 2;
        sf::Sprite bg, shadow;

        std::array<sf::Sprite, BTN_COUNT> buttons;
        std::array<sf::Rect<int>, BTN_COUNT> bounds;

        Animation animation;

        float bg_init_y;

    private:
        PauseUI();
        ~PauseUI() = default;

        void update( const sf::Time& ) override;
        void configure( const std::optional<Progressive*>& ) override;

        const sf::Rect<int>& btn_bound( const int id ) const;

        void exit_animation();
        const bool anim_finished() const;

    protected:
        static std::array<sf::Sprite, BTN_COUNT> __make_btns() {
            const TextureCache& inst = TextureCache::inst();

            return {
                sf::Sprite( inst.get("pause/btn/resume") ),
                sf::Sprite( inst.get("pause/btn/quit") )
            };
        }
        void __move_btns();
};
