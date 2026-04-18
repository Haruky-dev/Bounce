#pragma once

#include <SFML/Audio/Music.hpp>

#include <memory>

#include <engine/Layer.hpp>
#include <engine/visuals/GameUI.hpp>
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
        void refresh_entities();
        // match player.direction with ball.direction
            // same-> inc ball.speed
            // diff-> dec ball.speed
            // (player.direction == 0)-> NOOP
        const int guide_direcion( const int id ) const;

    public:
        GameLayer();
        ~GameLayer();
        void Load() override;
        void Update( const sf::Time& dt ) override;
        void Render( sf::RenderWindow& win ) const override;

        void pause() override;
        void resume() override;
        void exit() override;

        Layer::Type type() const override;
};