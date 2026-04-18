#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include <cache/TextureCache.hpp>
#include <engine/visuals/BaseUI.hpp>
#include <engine/features/Progressive.hpp>


class PauseUI : public BaseUI {
    friend class PauseLayer;

    private:
        sf::Sprite bg;
        sf::Sprite shad;
        sf::Color shadClr; // tweak opacity
        sf::Color bgClr;

        float bg_initY;

    private:
        PauseUI();
        ~PauseUI() = default;

        void update( const sf::Time& ) override {}
        void configure( const std::optional<Progressive*>& ) override;
};
