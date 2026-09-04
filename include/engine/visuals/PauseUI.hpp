#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>

#include <array>
#include <unordered_map>

#include <engine/visuals/BaseUI.hpp>
#include <engine/features/Animation.hpp>
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
        void configure() override;

        void exit_animation();

    protected:
        static std::array<sf::Sprite, BTN_COUNT> make_btns_() {
            const TextureCache& inst = TextureCache::inst();

            return {
                sf::Sprite( inst.get("pause/btn/quit") ),
                sf::Sprite( inst.get("pause/btn/resume") )
            };
        }

        void move_btns_();
};
