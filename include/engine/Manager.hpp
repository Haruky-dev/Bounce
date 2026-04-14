#pragma once

#include <SFML/Audio/Sound.hpp>
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <functional>
#include <memory>
#include <vector>

#include <engine/Layer.hpp>

enum class Action;


class Manager {
    private:
        // A storing unit that holds factory functions of layers
        std::unordered_map<
            Layer::Type, std::function<std::unique_ptr<Layer>()>
            > __register;

        std::vector<std::unique_ptr<Layer>> __stack;

    private:
        void pushLayer( Layer::Type T, bool overlapLast=false );
        void updateLayers( sf::Time& dt );
        void controlOut( const Action out );
        void renderLayers( sf::RenderWindow& win  ) const;

    public:
        Manager();
        ~Manager() = default;

    public:
        void Update( sf::Time& dt, sf::RenderWindow& win );
        void Render( sf::RenderWindow& win ) const;
};