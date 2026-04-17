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
        void Update( const sf::Time& dt ) override;
        void Render( sf::RenderWindow& win ) const override;

        void exit() override;
        Layer::Type type() const override;

        ~EndLayer() = default;
};