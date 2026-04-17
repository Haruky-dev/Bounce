#include <engine/visuals/GameUI.hpp>

#include <cache/TextureCache.hpp>
#include <cache/SoundCache.hpp>
#include <cache/FontCache.hpp>
#include <tools/Tool.hpp>
#include <tools/Json.hpp>


GameUI::GameUI() :
    _cdTime(sf::Time::Zero),

    bg(TextureCache::inst().get("play/bg")),
    pad(TextureCache::inst().get("play/pad")),
    ball(TextureCache::inst().get("play/ball")),

    countD(FontCache::RASTER, "3"),
    score_1(FontCache::KA, std::to_string(Tool::P1_SCORE)),
    score_2(score_1.getFont(), std::to_string(Tool::P2_SCORE)),

    paddleSFX( SoundCache::paddleBUF ),
    wallSFX( SoundCache::wallBUF )
    {}


void GameUI::configure( const std::optional<Progressive*>& prog ) {
    if ( prog.has_value() ) (*prog)->add_to_total( 10 );

    // scores conf
    this->score_1.setOrigin( this->score_1.getLocalBounds().getCenter() );
    this->score_1.setPosition( {Tool::WIDTH /4.f, Tool::HEIGHT /4.f} );
    this->score_1.setFillColor( sf::Color(241, 233, 219, 100) );
    this->score_1.setScale( {2.f, 2.f} );

    this->score_2.setOrigin( this->score_2.getLocalBounds().getCenter() );
    this->score_2.setPosition({ sf::Vector2f(Tool::WIDTH, Tool::HEIGHT) - this->score_1.getPosition() });
    this->score_2.setFillColor( this->score_1.getFillColor() );
    this->score_2.setScale( this->score_1.getScale() );

    // countdown sprite conf
    this->countD.setOrigin( this->countD.getLocalBounds().getCenter() );
    this->countD.setPosition( {Tool::W_CTR.x, Tool::W_CTR.y /2.f} );
    this->countD.setFillColor( sf::Color( 12, 32, 36, 150 ));
    this->countD.setScale( {1.5f, 1.5f} );

    if ( prog.has_value() )  (*prog)->increment_by( 10 );
}

void GameUI::update( const sf::Time& dt ) {
    if ( Tool::goalScored ) {
        Tool::goalScored = false;
        this->_cdTime = sf::Time::Zero;
        Tool::CD = 0;

        this->score_1.setString( std::to_string(Tool::P1_SCORE) );
        this->score_2.setString( std::to_string(Tool::P2_SCORE) );
    }

    if ( Tool::CD >= Tool::maxCD ) {
        this->_cdTime = sf::Time::Zero;
        Tool::CD = -1;

        this->countD.setString( std::to_string( Tool::maxCD ) );

    } else if ( Tool::CD != -1 ) {
        // only update when both players are on center, both ready
        Tool::CD = static_cast<int>( this->_cdTime.asSeconds() );
        this->countD.setString( std::to_string( Tool::maxCD - Tool::CD ) );
        this->_cdTime += dt;
    }
}
