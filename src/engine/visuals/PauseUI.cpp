#include <engine/visuals/PauseUI.hpp>

#include <cache/TextureCache.hpp>
#include <tools/Tool.hpp>
#include <tools/Math.hpp>


PauseUI::PauseUI() :
    animation(),
    bg(TextureCache::inst().get("pause/bg")),
    shadow(TextureCache::inst().get("pause/shad")),
    bg_clr(bg.getColor()),
    shadow_clr(shadow.getColor())
    {}

void PauseUI::configure( const std::optional<Progressive*>& prog ) {
    if ( prog.has_value() ) (*prog)->add_to_total( 5 );

    this->bg.setOrigin( sf::Vector2f(bg.getTexture().getSize()) / 2.f );

    this->bg_init_y = 1.5f * Tool::HEIGHT;

    this->bg.setPosition( {Tool::W_CTR.x, this->bg_init_y});

    if ( prog.has_value() ) (*prog)->increment_by( 5 );
}

void PauseUI::update( const sf::Time& dt ) {
    this->animation.update( dt );

    const double p = this->animation.progress();

    float y = Math::Lerp(
        this->bg_init_y,
        Tool::W_CTR.y,
        Math::easeOut( p )
    );
    this->shadow_clr.a = static_cast<std::uint8_t>(
        180 * Math::easeInOut( p )
    );
    this->bg_clr.a = static_cast<uint8_t>(
        255 * Math::easeIn( p )
    );

    this->bg.setPosition( {this->bg.getPosition().x, y} );
    this->bg.setColor( this->bg_clr );
    this->shadow.setColor( this->shadow_clr );
}

void PauseUI::exit_animation() {
    this->animation.exit();
}
const bool PauseUI::anim_finished() const {
    return this->animation.finished();
}