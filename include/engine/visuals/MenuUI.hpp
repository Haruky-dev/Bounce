#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>

#include <array>

#include <cache/TextureCache.hpp>
#include <engine/visuals/BaseUI.hpp>
#include <engine/features/Progressive.hpp>
#include <tools/Tool.hpp>

#define BTN_COUNT 3


class MenuUI : public BaseUI {
    friend class MenuLayer;

    private:
        // const int BTN_COUNT = 3;
        std::array<sf::Sprite, BTN_COUNT> btns;
        std::array<sf::Rect<int>, BTN_COUNT> bounds;

        sf::Sprite bg, credit, version;

    private:

        MenuUI();
        ~MenuUI() = default;

        void update( const sf::Time& ) override {}
        void configure( const std::optional<Progressive*>& ) override;

        const sf::Rect<int>& btnBound( const int id ) const; // constexpr?
        constexpr int nBtns() const { return BTN_COUNT; }

    protected:
        // helper initializer for 'btns' (std::array<sf::Sprite>)
        static std::array< sf::Sprite, BTN_COUNT > makeBtns() {
            TextureCache& inst = TextureCache::inst();

            return {
                sf::Sprite( inst.get("mm/btn/play") ),
                sf::Sprite( inst.get("mm/btn/set") ),
                sf::Sprite( inst.get("mm/btn/q") )
            };
        }

};
