#include <engine/visuals/PlayUI.hpp>

#include <cache/TextureCache.hpp>
#include <cache/SFX.hpp>
#include <cache/FontCache.hpp>
#include <tools/Constants.hpp>
#include <tools/Flags.hpp>
#include <tools/Json.hpp>
#include <tools/Math.hpp>


PlayUI::PlayUI() :
    _cdTime(sf::Time::Zero),

    bg(TextureCache::inst().get("play/bg")),
    pad(TextureCache::inst().get("play/pad")),
    ball(TextureCache::inst().get("play/ball")),
    banner(TextureCache::inst().get("play/banner")),
    banner_anim(.5),

    countD(FontCache::RASTER, "3"),
    score_1(FontCache::KA, std::to_string(Constants::P1_SCORE)),
    score_2(score_1.getFont(), std::to_string(Constants::P2_SCORE)),
    P1_ready(false), P2_ready(false) // false
    {}


void PlayUI::configure() {
    // scores conf
    this->score_1.setOrigin( this->score_1.getLocalBounds().getCenter() );
    this->score_1.setPosition( {Constants::WIDTH /3.f, Constants::HEIGHT /3.f} );
    this->score_1.setFillColor( sf::Color(94, 159, 224, 255) );
    this->score_1.setScale( {2.f, 2.f} );

    this->score_2.setOrigin( this->score_2.getLocalBounds().getCenter() );
    this->score_2.setPosition({ sf::Vector2f(Constants::WIDTH, Constants::HEIGHT) - this->score_1.getPosition() });
    this->score_2.setFillColor( this->score_1.getFillColor() );
    this->score_2.setScale( this->score_1.getScale() );

    // countdown sprite conf
    this->countD.setOrigin( this->countD.getLocalBounds().getCenter() );
    this->countD.setPosition( {Constants::W_CTR.x, Constants::W_CTR.y /2.f} );
    this->countD.setFillColor( sf::Color( 12, 32, 36, 150 ));
    this->countD.setScale( {1.5f, 1.5f} );

    this->banner.setPosition( {210, 360} );

    this->bounds[PlayUI::BTNS::MENU] = sf::Rect<int>(
        {350, 12}, {20, 20}
    );
}

void PlayUI::update( const sf::Time& dt ) {
    if ( Flags::goalScored ) {
        Flags::goalScored = false;
        this->_cdTime = sf::Time::Zero;
        Constants::CD = 0;

        this->score_1.setString( std::to_string(Constants::P1_SCORE) );
        this->score_2.setString( std::to_string(Constants::P2_SCORE) );
    }

    if ( Constants::CD >= Constants::maxCD ) {
        this->_cdTime = sf::Time::Zero;
        Constants::CD = -1;

        this->countD.setString( std::to_string( Constants::maxCD ) );

    } else if ( Constants::CD != -1 ) {
        if ( !P1_ready ) {
            this->_update_banner(dt);
            return;
        }
        // if ( !(P1_ready && P2_ready) ) return;
        // if ( !P1_ready || !P2_ready ) return;

        Constants::CD = static_cast<int>( this->_cdTime.asSeconds() );
        this->countD.setString( std::to_string( Constants::maxCD - Constants::CD ) );
        this->_cdTime += dt;
    }
}

void PlayUI::sync() {
    this->score_1.setString( std::to_string( Constants::P1_SCORE) );
    this->score_2.setString( std::to_string( Constants::P2_SCORE ));
}

void PlayUI::set_players_ready( const bool P1, const bool P2 ) {
    this->P1_ready = P1; this->P2_ready = P2;
}

void PlayUI::_update_banner( const sf::Time& dt ) {
    this->banner_anim.update(dt);

    sf::Color b_clr = this->banner.getColor();
    b_clr.a = static_cast<uint8_t>( Math::easeInOut(this->banner_anim.progress()) * 255 );
    this->banner.setColor(b_clr);

    if ( this->banner_anim.finished() ) {
        if ( this->banner_anim.status() == Animation::Status::In )
            this->banner_anim.exit();
        else // .status() == Animation::Status::Out
            this->banner_anim.enter();
    }
}