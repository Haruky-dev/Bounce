#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include <cache/TextureCache.hpp>
#include <engine/visuals/BaseUI.hpp>
#include <engine/features/Animation.hpp>


class QuitUI : public BaseUI {
    friend class QuitLayer;

    private:
        sf::Sprite bg, shadow;
        Animation animation;

    private:
        QuitUI();
        ~QuitUI() = default;

        void update( const sf::Time& ) override;
        void configure() override;

        void exit_animation();
};
