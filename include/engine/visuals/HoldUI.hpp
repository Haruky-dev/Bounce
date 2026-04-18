#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include <engine/visuals/BaseUI.hpp>
#include <engine/features/Progressive.hpp>


class HoldUI : BaseUI {
    friend class HoldLayer;

    private:
        sf::Sprite bg;

    private:
        HoldUI();
        ~HoldUI() = default;
        
        void update( const sf::Time& ) override {}
        void configure( const std::optional<Progressive*>& ) override;
};