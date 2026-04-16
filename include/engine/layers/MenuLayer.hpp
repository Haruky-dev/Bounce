#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio/Music.hpp>

#include <engine/Layer.hpp>
#include <cache/visuals/MenuUI.hpp>

#include <memory>


class MenuLayer : public Layer {
    private:
        MenuUI UI;
        std::unique_ptr<sf::Music> music; // should be a ref as well, held by 'SoundCache'
        sf::Time accTime;

    public:
        MenuLayer();
        void Load() override;
        void Update( sf::Time& dt ) override;
        void Render( sf::RenderWindow& win ) const override;

        void enter() override;
        void pause() override;
        void exit() override;

        Layer::Type getType() const override;

        ~MenuLayer() = default;
};