#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>

#include <array>
#include <unordered_map>

#include <engine/visuals/BaseUI.hpp>
#include <engine/features/Animation.hpp>
#include <engine/features/Progressive.hpp>
#include <cache/TextureCache.hpp>


class PauseUI : public BaseUI {
    friend class PauseLayer;

    private:
        enum class BTNS {
          QUIT,
          RESUME
        };
        sf::Sprite bg, shadow;
        static const int BTN_COUNT = 2;

        std::array<sf::Sprite, BTN_COUNT> buttons;
        std::unordered_map<PauseUI::BTNS, sf::Rect<int>> bounds;

        sf::Rect<int> bg_rect;

        Animation animation;

        float bg_init_y;

    private:
        PauseUI();
        ~PauseUI() = default;

        void update( const sf::Time& ) override;
        void configure( const std::optional<Progressive*>& ) override;

        void exit_animation();
        const bool anim_finished() const;

    protected:
        static std::array<sf::Sprite, BTN_COUNT> __make_btns() {
            const TextureCache& inst = TextureCache::inst();

            return {
                sf::Sprite( inst.get("pause/btn/quit") ),
                sf::Sprite( inst.get("pause/btn/resume") )
            };
        }

        void __move_btns();
};
