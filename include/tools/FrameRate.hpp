#pragma once

#include <SFML/Graphics.hpp>

class FrameRate : public sf::Drawable {
    sf::Text txt;

    sf::Time accTime;
    float delay;
    int frames, fps;

    void adjTxt();

    protected:
        virtual void draw( sf::RenderTarget&, sf::RenderStates ) const override;

    public:
        FrameRate();

        void update( sf::Time& );
};
