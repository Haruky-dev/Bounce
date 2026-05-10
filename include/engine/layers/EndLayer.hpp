#pragma once

#include <SFML/Graphics.hpp>

#include <engine/Layer.hpp>
#include <engine/visuals/EndUI.hpp>


class EndLayer : public Layer {
    private:
        EndUI UI;
        sf::Time accTime;

    public:
        EndLayer();

        void Load() override;
        void Update( const sf::Time& dt ) override;
        void Render( sf::RenderWindow& win ) const override;

        bool animated() const override;
        bool popable() const override;
        void exit() override;
        
        Layer::Type type() const override;

        ~EndLayer() = default;
};