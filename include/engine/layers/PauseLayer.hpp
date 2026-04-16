#pragma once

#include <SFML/Graphics.hpp>

#include <SFML/Graphics/Color.hpp>
#include <engine/Layer.hpp>
#include <engine/features/Animated.hpp>
#include <cache/visuals/PauseUI.hpp>


class PauseLayer : public Layer, public Animated {
    private:
        PauseUI UI;
        sf::Time accTime;

    public:
        PauseLayer();

        void Load() override;
        void Update( sf::Time& dt ) override;
        void Render( sf::RenderWindow& win ) const override;

        void exit() override;
        bool popable() const override;

        Layer::Type getType() const override;

        ~PauseLayer() = default;
};