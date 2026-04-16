#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>

#include <tools/Tool.hpp>
#include <tools/Math.hpp>


class Player : public sf::Drawable {
    friend class GameLayer;

    protected:
        sf::Sprite bar;
        int direction;
        
    protected:
        explicit Player( const sf::Sprite& spr, const bool id )
        : id(id), direction(0), bar(spr)
            {
                this->bar.setOrigin( this->bar.getLocalBounds().getCenter() );
        }

        virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const override {     target.draw( this->bar, states ); }

    public:
        bool id; // 0: human, 1: computer

    public:
        // virtual void update() = 0;

        virtual bool ready() { // total BS
            return Math::isBetween(
                this->bar.getPosition().y, Tool::HEIGHT / 3.0f, 2.0f/3.0f * Tool::HEIGHT
            );
        }
        virtual sf::Rect<float> bounds() { return this->bar.getGlobalBounds(); } // return this->hitBox;
        virtual sf::Vector2<float> position() { return this->bounds().position; }
};