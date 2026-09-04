#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>

#include <tools/Constants.hpp>
#include <tools/Flags.hpp>


class Player : public sf::Drawable {
    friend class PlayLayer;

    protected:
        sf::Sprite bar;
        int direction;

    protected:
        explicit Player( const sf::Sprite& spr, const bool id )
        : id(id), direction(0), bar(spr)
            {
                this->bar.setOrigin( this->bar.getLocalBounds().getCenter() );
        }

        virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const override { target.draw( this->bar, states ); }

    public:
        bool id; // 0: human, 1: computer

    public:
        virtual void refresh() = 0;
        virtual void reset() = 0;
        virtual sf::Vector2<float> position() { return this->bounds().position; }

        const bool ready() const {
            const float y_pos = this->bar.getPosition().y;
            static const float bar_height = this->bar.getLocalBounds().size.y; // hitbox

            return ( y_pos > Constants::W_CTR.y - bar_height) && (y_pos < Constants::W_CTR.y + bar_height);
        }
        sf::Rect<float> bounds() { return this->bar.getGlobalBounds(); } // return this->hitBox;
};