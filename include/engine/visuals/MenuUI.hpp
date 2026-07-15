#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>

#include <array>
#include <unordered_map>

#include <cache/TextureCache.hpp>
#include <engine/visuals/BaseUI.hpp>
#include <tools/Tool.hpp>


class MenuUI : public BaseUI {
    friend class MenuLayer;

    private:
        enum class BTNS {
            PLAY,
            MENU,
            QUIT
        };

        static constexpr int BTN_COUNT = 3;
        std::array<sf::Sprite, BTN_COUNT> btns;
        std::unordered_map<MenuUI::BTNS, sf::Rect<int>> bounds;

        sf::Sprite bg, credit, version;
        sf::Rect<int> bg_rect;

    private:
        MenuUI();
        ~MenuUI() = default;

        void update( const sf::Time& ) override {}
        void configure() override;

    protected:
        // helper initializer for 'btns' (std::array<sf::Sprite>)
        static std::array< sf::Sprite, BTN_COUNT > __make_btns() {
            TextureCache& inst = TextureCache::inst();

            return {
                sf::Sprite( inst.get("mm/btn/play") ),
                sf::Sprite( inst.get("mm/btn/set") ),
                sf::Sprite( inst.get("mm/btn/q") )
            };
        }

        void __init_bounds();
};
