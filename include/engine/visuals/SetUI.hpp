#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include <engine/visuals/BaseUI.hpp>
#include <engine/features/Progressive.hpp>


class SetUI : public BaseUI {
    friend class SetLayer;

    private:
        sf::Sprite bg;
        sf::Sprite shad;
        sf::Color shadClr;

        float bg_initY;

    private:
        SetUI();
        ~SetUI() = default;

        void update( const sf::Time& dt ) override {}
        void configure( const std::optional<Progressive*>& ) override;
};
