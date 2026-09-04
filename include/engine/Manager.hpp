#pragma once

#include <SFML/Audio/Sound.hpp>
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <functional>
#include <memory>
#include <vector>

#include <engine/Layer.hpp>


class Manager {
    friend class Dispatcher;

    private:
        struct State {
            std::unique_ptr<Layer> layer;
            bool onOverlap = false; // handle overlapping layers
            bool onFreeze  = false; // Do not update frozen layers
            bool onExit    = false; // Do not pop 'exiting' layers until flagged as 'popable'
            bool Loaded    = false;
        };

        // A storing unit that holds factory functions of layers
        std::unordered_map<
            Layer::Type, std::function<std::unique_ptr<Layer>()>
            > register_;

        std::vector<State> stack_;

    private:
        void pushLayer_( Layer::Type, bool overlapping=false, bool freezeLast=false );
        void updateLayers_( const sf::Time& );
        void controlAction_( const Action );
        void controlExit_( std::span<const sf::Event> );
        void renderLayers_( sf::RenderWindow&  ) const;

    public:
        bool quit_flag;

    public:
        Manager();
        ~Manager() = default;

        void Update( const sf::Time&, std::span<const sf::Event> );
        void Render( sf::RenderWindow& ) const;
};
