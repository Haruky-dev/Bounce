#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include <cache/visuals/BaseUI.hpp>
#include <engine/features/Progressive.hpp>


class SetUI : public BaseUI {
    friend class SetLayer;

    private:
        sf::Sprite bg;
        sf::Sprite shad;
        sf::Color shadClr;

        float bg_initY;

    public:
        SetUI();
        ~SetUI() = default;

        void configure( Progressive& ) override;
};
