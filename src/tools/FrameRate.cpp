#include <tools/FrameRate.hpp>

#include <cache/FontCache.hpp>

#include <tools/Json.hpp>
#include <tools/Constants.hpp>


FrameRate::FrameRate()
    : accTime(sf::Time::Zero), frames(0), fps(0),
    txt(FontCache::RASTER, ""), delay(Json::Float("setting.fps.delay", Json::Type::SET)) {

        this->txt.setFillColor( sf::Color(241, 233, 219, 200) );
        this->txt.setScale( {0.7f, 0.7f} );
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
    this->txt.setPosition( {
        Constants::W_CTR.x - this->txt.getGlobalBounds().size.x / 2.0f,
        Constants::HEIGHT - 30.f
    } );
}

void FrameRate::draw( sf::RenderTarget& target, sf::RenderStates states ) const {
    target.draw( this->txt, states );
}
