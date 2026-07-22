#pragma once

#include <SFML/Graphics.hpp>

#include <engine/Layer.hpp>
#include <engine/visuals/QuitUI.hpp>
#include <engine/features/Animation.hpp>



class QuitLayer : public Layer {
    private:
        QuitUI UI;
        std::chrono::seconds T;
        sf::Time accTime;

    public:
        QuitLayer();
        void Load() override;
        void Update( const sf::Time& ) override;
        void Render( sf::RenderWindow& win ) const override;

        Action feature() const override;
        bool animated() const override;
        bool popable() const override;
        void exit() override;

        Layer::Type type() const override;

        ~QuitLayer() = default;
};