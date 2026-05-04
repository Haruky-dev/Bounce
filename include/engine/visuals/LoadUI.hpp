#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include <engine/visuals/BaseUI.hpp>
#include <engine/features/Progressive.hpp>


class LoadUI : BaseUI {
    friend class LoadLayer;

    private:
        sf::RectangleShape bg;
        sf::Font __font;
        sf::Text progressText;
        float v;

    private:
        LoadUI();
        ~LoadUI() = default;

        void update( const sf::Time& ) override;
        void configure( const std::optional<Progressive*>& ) override;
        void setValue( const float value ) { this->v = value; }
};