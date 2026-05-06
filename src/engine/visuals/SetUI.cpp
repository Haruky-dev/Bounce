#include <engine/visuals/SetUI.hpp>

#include <cache/TextureCache.hpp>
#include <tools/Tool.hpp>
#include <tools/Math.hpp>


SetUI::SetUI() :
    animation(),
    bg(TextureCache::inst().get("set/bg")),
    shadow(TextureCache::inst().get("set/shad")),
    bg_init_y(1.5f*Tool::HEIGHT)
    {}

void SetUI::configure( const std::optional<Progressive*>& prog ) {
    if ( prog.has_value() ) (*prog)->add_to_total( 5 );

    this->bg.setOrigin(
        sf::Vector2f(this->bg.getTexture().getSize()) / 2.f
    );
    this->bg.setPosition( {Tool::W_CTR.x, this->bg_init_y} );

    if ( prog.has_value() ) (*prog)->increment_by( 5 );
}

void SetUI::update( const sf::Time& dt ) {
    this->animation.update( dt );

    const double p = this->animation.progress();

    float y = Math::Lerp(
        this->bg_init_y,
        Tool::W_CTR.y,
        Math::easeOut( p )
    );
    sf::Color bg_c = this->bg.getColor(),
              shadow_c = this->shadow.getColor();

    bg_c.a = shadow_c.a = static_cast<uint8_t>( Math::easeOut(p) * 255 );

    this->bg.setPosition( {this->bg.getPosition().x, y} );
    this->bg.setColor( bg_c );
    this->shadow.setColor( shadow_c );
}

void SetUI::exit_animation() {
    this->animation.exit();
}
const bool SetUI::anim_finished() const {
    return this->animation.finished();
}