#pragma once

#include <SFML/Audio/Music.hpp>

#include <memory>

#include <engine/Layer.hpp>
#include <engine/visuals/PlayUI.hpp>
#include <engine/io/Action.hpp>

#include <entities/Player.hpp>
#include <entities/Human.hpp>
#include <entities/ai/Computer.hpp>

#include <entities/Ball.hpp>
#include <tools/FrameRate.hpp>


class PlayLayer : public Layer {
    private:
        PlayUI UI;

        mutable Human P1;
        mutable Computer P2;
        Ball ball;

        FrameRate FR;
        Constants::Sides norme;

        std::unique_ptr<sf::Music> music;

    private:
        Action feature() const override;
        void form_request() override;

        void updateEntities( const sf::Time& );
        void moveBall( const sf::Time& );
        void refinePlayers();
        void refineBall();

    public:
        PlayLayer();
        ~PlayLayer();

        void Load() override;
        void Update( const sf::Time& dt ) override;
        void Render( sf::RenderWindow& win ) const override;

        void resume() override;
        void exit() override;

        Layer::Type type() const override;
};