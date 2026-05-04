#pragma once

#include <SFML/Graphics.hpp>

#include <engine/Layer.hpp>
#include <engine/visuals/SetUI.hpp>
#include <engine/features/Animation.hpp>


class SetLayer : public Layer, public Animation {
    private:
        SetUI UI;

    public:
        SetLayer();
        void Load() override;
        void Update( const sf::Time& dt ) override;
        void Render( sf::RenderWindow& win ) const override;

        bool animated() const override;
        void exit() override;
        bool popable() const override;

        Layer::Type type() const override;

        ~SetLayer() = default;
};
