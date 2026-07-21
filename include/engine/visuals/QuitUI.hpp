#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include <cache/TextureCache.hpp>
#include <engine/visuals/BaseUI.hpp>
#include <engine/features/Animation.hpp>

#include <unordered_map>


class QuitUI : public BaseUI {
    friend class QuitLayer;
    enum class BTNS { CANCEL };

    private:
        sf::Sprite bg, shadow;
        static const int BTN_COUNT = 2;
        Animation animation;

        std::unordered_map<QuitUI::BTNS, sf::Rect<int>> bounds;

    private:
        QuitUI();
        ~QuitUI() = default;

        void update( const sf::Time& ) override;
        void configure() override;

        void exit_animation();
};
