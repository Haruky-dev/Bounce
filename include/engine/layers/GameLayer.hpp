#pragma once

#include <SFML/Audio/Music.hpp>

#include <memory>

#include <engine/Layer.hpp>
#include <cache/visuals/GameUI.hpp>
#include <engine/input/Action.hpp>
#include <engine/features/Transition.hpp>

#include <entities/Player.hpp>
#include <entities/Human.hpp>
#include <entities/ai/Computer.hpp>

#include <entities/Ball.hpp>
#include <tools/FrameRate.hpp>


class GameLayer : public Layer, public Transition {
    private:
        GameUI UI;

        Human P1;
        Computer P2;
        Ball ball;

        FrameRate FR;
        Tool::Sides norme;

        std::unique_ptr<sf::Music> music;

        Action feature() const override;
        void updateBall( const sf::Time& dt );

    public:
        GameLayer();
        ~GameLayer();
        void Load() override;
        void Update( sf::Time& dt ) override;
        void Render( sf::RenderWindow& win ) const override;

        void pause() override;
        void resume() override;
        void exit() override;

        Layer::Type getType() const override;
};