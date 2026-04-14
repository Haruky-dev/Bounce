#pragma once

#include <SFML/Graphics.hpp>

#include <engine/Layer.hpp>
#include <engine/features/Progressive.hpp>

#include <thread>
#include <atomic>


class LoadLayer : public Layer, public Progressive {
    private:
        sf::Font fnt;
        sf::Text txt;
        sf::Text progTxt;
        sf::RectangleShape bg;
        std::thread loader;

        std::atomic<int> loadCost {1}; // total n of work units (avoid /0)
        std::atomic<int> currUnit {0}; // track curr n of work units
        
        Action feature() const override;

    public:
        // Add into total work units
        void addTotal( int units ) override {
            loadCost += units;
        }

        // increment the curr counter of work units
        void incCount( int units=1 ) override {
            currUnit += units;
        }

    public:
        LoadLayer();

        void Load() override;
        void Update(sf::Time &dt) override;
        void Render(sf::RenderWindow &win) const override;

        Layer::Type getType() const override;

        std::atomic<bool> loadDone {false};

        ~LoadLayer();
};