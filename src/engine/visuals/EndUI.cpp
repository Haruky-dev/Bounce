#include <engine/visuals/EndUI.hpp>

#include <cache/TextureCache.hpp>
#include <cache/FontCache.hpp>
#include <tools/Tool.hpp>
#include <tools/Math.hpp>


EndUI::EndUI() :
    animation(),
    scores( __init_scores() ),
    bg(TextureCache::inst().get("end/bg")),
    shadow(TextureCache::inst().get("shad_2")),
    winner(TextureCache::inst().get("end/winner")),
    bg_rect(bg.getTextureRect())
    {}
    
void EndUI::configure() {
    this->animation.set_duration( .4f );
    this->bg.setOrigin( sf::Vector2f(this->bg.getTexture().getSize()) / 2.f );
    this->bg.setPosition( Tool::W_CTR );

    // init buttons bounds to their final position
    this->bounds[EndUI::BTNS::QUIT] = sf::Rect<int>(
        this->__normalize<int>( this->bg_rect, {25, 210} ), {185, 60}
    );
    this->bounds[EndUI::BTNS::RESTART] = sf::Rect<int>(
        this->__normalize<int>( this->bg_rect, {240, 210} ), {185, 60}
    );

    this->winner.setPosition( this->__normalize<float>( this->bg_rect, {
        60.0f + 220 * ( Tool::P1_SCORE < Tool::P2_SCORE ),
        175
    }) );
}

void EndUI::update( const sf::Time& dt ) {
    this->animation.update( dt );

    const double p = this->animation.progress();

    sf::Color bg_c = this->bg.getColor(), shad_clr = this->shadow.getColor(), win_clr = this->winner.getColor();
    bg_c.a = win_clr.a = static_cast<std::uint8_t>( 255 * Math::easeIn( p ) );
    shad_clr.a  = static_cast<std::uint8_t>( 180 * Math::easeIn( p ) );

    this->bg.setColor(bg_c);
    this->shadow.setColor(shad_clr);
    this->winner.setColor(win_clr);

    const float s = Math::easeElastic(p) + 1;
    this->winner.setScale( {s, s} );
}

std::array<sf::Text, 2> EndUI::__init_scores() {
    std::array<sf::Text, 2> arr({
        sf::Text( FontCache::MineCraf, std::to_string(Tool::P1_SCORE) ),
        sf::Text( FontCache::MineCraf, std::to_string(Tool::P2_SCORE) )
    });

    for ( int i = 0; i < arr.size(); i++ ) {
        arr.at( i ).setFillColor( sf::Color( 26, 26, 46, 255) );
        arr.at( i ).setPosition( this->__normalize<float>( this->bg_rect,
            { (float) 175 + i*80, 140 }
        ) );
        arr.at( i ).setScale({ 0.8f, 0.8f });
    }

    return arr;
}