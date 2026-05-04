#include <engine/visuals/SetUI.hpp>

#include <cache/TextureCache.hpp>
#include <tools/Tool.hpp>
#include <tools/Math.hpp>


SetUI::SetUI() :
    animation(),
    bg(TextureCache::inst().get("set/bg")),
    shadow(TextureCache::inst().get("set/shad")),
    shadow_clr(shadow.getColor())
    {}

void SetUI::configure( const std::optional<Progressive*>& prog ) {
    if ( prog.has_value() ) (*prog)->add_to_total( 5 );

    this->bg.setOrigin(
        sf::Vector2f(this->bg.getTexture().getSize()) / 2.f
    );

    this->bg_init_y = 1.5f * Tool::HEIGHT;
    this->bg.setPosition( {Tool::W_CTR.x, this->bg_init_y} );

    if ( prog.has_value() ) (*prog)->increment_by( 5 );
}

void SetUI::update( const sf::Time& dt ) {
    this->animation.update( dt );

    const double p = this->animation.progress();

    switch ( this->animation.status() ) {
        case Animation::Status::In:
            break;
        case Animation::Status::Out:
            break;
    }

    float y = Math::Lerp(
        this->bg_init_y,
        Tool::W_CTR.y,
        Math::easeOut( p )
    );

    this->shadow_clr.a = static_cast<std::uint8_t>(
        255 * Math::easeInOut( p )
    );

    this->bg.setPosition( {this->bg.getPosition().x, y} );
    this->shadow.setColor(this->shadow_clr);
}

void SetUI::exit_animation() {
    this->animation.exit();
}
const bool SetUI::anim_finished() const {
    return this->animation.finished();
}