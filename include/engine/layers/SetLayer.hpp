#pragma once

#include <SFML/Graphics.hpp>

#include <engine/Layer.hpp>
#include <cache/visuals/SetUI.hpp>
#include <engine/features/Animated.hpp>


class SetLayer : public Layer, public Animated {
    private:
        SetUI UI;

    public:
        SetLayer();
        void Load() override;
        void Update( sf::Time& dt ) override;
        void Render( sf::RenderWindow& win ) const override;

        void exit() override;
        bool popable() const override;

        Layer::Type getType() const override;

        ~SetLayer() = default;
};