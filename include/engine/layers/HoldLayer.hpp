/* A mini loader layer represent a bridge in layer switching, heavy loading.. */
#pragma once

#include <engine/Layer.hpp>
#include <engine/visuals/HoldUI.hpp>
#include <engine/features/Animated.hpp>
#include <engine/features/Progressive.hpp>


#include <thread>


class HoldLayer : public Layer, public Progressive {
    private:
        HoldUI UI;

        std::thread loader;

        Action feature() const override;

    public:
        HoldLayer();
        ~HoldLayer();

        void Load() override;
        void Update( const sf::Time& ) override;
        void Render( sf::RenderWindow& ) const override;

        Layer::Type type() const override;
};