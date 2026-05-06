#include <tools/FrameRate.hpp>

#include <cache/FontCache.hpp>

#include <tools/Json.hpp>
#include <tools/Tool.hpp>


FrameRate::FrameRate()
    : accTime(sf::Time::Zero), frames(0), fps(0),
    txt(FontCache::RASTER, ""), delay(Json::Float("setting.fps.delay")) {

        this->txt.setFillColor( sf::Color(241, 233, 219, 200) );
        this->adjTxt();
}

void FrameRate::update( const sf::Time& dt ) {
    this->accTime += dt;
    this->frames++;

    if ( this->accTime.asSeconds() >=  this->delay ) {
        fps = static_cast<int>( this->frames / this->accTime.asSeconds() );

        txt.setString( std::to_string(fps) );

        this->adjTxt();

        this->accTime = sf::Time::Zero;
        this->frames = 0;
    }
}

void FrameRate::adjTxt() {
    this->txt.setPosition( {Tool::W_CTR.x - this->txt.getGlobalBounds().size.x / 2.0f, 8.0f} );
    // txt.setPosition( {10.f, 10.f} );
}

void FrameRate::draw( sf::RenderTarget& target, sf::RenderStates states ) const {
    target.draw( this->txt, states );
}
