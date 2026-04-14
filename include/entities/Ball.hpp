#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <tools/Tool.hpp>

class Computer;


class Ball : public sf::Drawable {
    friend class GameLayer;
    friend class Computer;

    private:
        sf::Sprite spr;       

        sf::Vector2f unitDirec;
        sf::Vector2f velocity;

        sf::Time accTime;

        int speed;
        int MAXspeed;
        int accel;
        bool onStart;
        bool onMove;
        
    protected:
        virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;
        
    public:
        Ball( const sf::Sprite& spr );

        void launch();
        void move( const sf::Vector2f& position );
        void rotate( const sf::Time& dt );
        void reflect( const Tool::Sides side );
        void adjust( const Tool::Sides, const sf::Rect<float>& );
        void reset();

        sf::Rect<float> bounds() const;
};