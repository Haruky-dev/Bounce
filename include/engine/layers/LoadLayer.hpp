#pragma once

#include <SFML/Graphics.hpp>

#include <engine/Layer.hpp>
#include <engine/visuals/LoadUI.hpp>
#include <engine/features/Progressive.hpp>

#include <thread>


class LoadLayer : public Layer, public Progressive {
    private:
        LoadUI UI;
        std::thread loader;

        Action feature() const override;

    public:
        LoadLayer();

        void Load() override;
        void Update(const sf::Time &dt) override;
        void Render(sf::RenderWindow &win) const override;

        Layer::Type type() const override;

        ~LoadLayer();
};