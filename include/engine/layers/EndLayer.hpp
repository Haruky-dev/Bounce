#pragma once

#include <SFML/Graphics.hpp>

#include <engine/Layer.hpp>


class EndLayer : public Layer {
    private:
        sf::CircleShape bg;
        sf::Time accTime;

    public:
        EndLayer();
        
        void Load() override;
        void Update( sf::Time& dt ) override;
        void Render( sf::RenderWindow& win ) const override;

        void exit() override;
        Layer::Type getType() const override;

        ~EndLayer() = default;
};