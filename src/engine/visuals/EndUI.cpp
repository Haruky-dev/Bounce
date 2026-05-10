#include <engine/visuals/EndUI.hpp>

#include <cache/TextureCache.hpp>
#include <cache/FontCache.hpp>
#include <tools/Tool.hpp>
#include <tools/Math.hpp>


EndUI::EndUI() :
    animation(),
    scores( __init_scores() ),
    bg(TextureCache::inst().get("end/bg")),
    winner(TextureCache::inst().get("end/winner"))
    {}
    
void EndUI::configure( const std::optional<Progressive*>& prog ) {
    if ( prog.has_value() ) (*prog)->add_to_total( 20 );

    this->animation.set_duration( .4f );
    this->bg.setOrigin( sf::Vector2f(this->bg.getTexture().getSize()) / 2.f );
    this->bg.setPosition( Tool::W_CTR );

    // init buttons bounds to their final position
    for ( int i = 0; i < this->BTN_COUNT; i++ ) {
        static const int width = 180, height = 40; // hardcoded since buttons are pre-drawn into the bg, and not a stand-alone sprite
        // static const int h_dist = 32; // horizontal distance between the two butttons
        this->bounds.at( i ) = sf::Rect<int>(
            sf::Vector2<int>( this->__normalize({
                25 + 215*i, 210
            }) ),
            { width, height }
        );
        // this->bounds.at( i ) = sf::Rect<int>(
        //     sf::Vector2<int>( Tool::W_CTR.x + ( (width+h_dist)*i - (width+h_dist/2.f) ), Tool::W_CTR.y +  60 ),
        //     { width, height }
        // );

    }
    this->winner.setPosition( this->__normalize({
        60 + 220 * ( Tool::P1_SCORE < Tool::P2_SCORE ),
        175
    }));

    if ( prog.has_value() ) (*prog)->increment_by( 20 );
}

void EndUI::update( const sf::Time& dt ) {
    this->animation.update( dt );

    const double p = this->animation.progress();

    sf::Color bg_c = this->bg.getColor();
    bg_c.a = static_cast<std::uint8_t>( 255 * Math::easeIn( p ) );

    this->bg.setColor(bg_c);

    const float s = Math::easeElastic(p) + 1;
    this->winner.setScale( {s, s} );
}

sf::Vector2<float> EndUI::__normalize( const sf::Vector2<int>& pos ) const {
    static const int X = (Tool::WIDTH - this->bg.getTextureRect().size.x) / 2.f;
    static const int Y = (Tool::HEIGHT - this->bg.getTextureRect().size.y) / 2.f;

    return sf::Vector2<float>(
      X + pos.x,
      Y + pos.y
    );
}

std::array<sf::Text, 2> EndUI::__init_scores() const {
    std::array<sf::Text, 2> arr({
        sf::Text( FontCache::MineCraf, std::to_string(Tool::P1_SCORE) ),
        sf::Text( FontCache::MineCraf, std::to_string(Tool::P2_SCORE) )
    });

    for ( int i = 0; i < arr.size(); i++ ) {
        arr.at( i ).setFillColor( sf::Color( 26, 26, 46, 255) );
        arr.at( i ).setPosition( this->__normalize({
            175 + 80*i, 140
        }) );
        arr.at( i ).setScale({ 0.8f, 0.8f });
    }

    return arr;
}