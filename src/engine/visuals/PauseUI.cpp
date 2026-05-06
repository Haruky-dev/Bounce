#include <engine/visuals/PauseUI.hpp>

#include <cache/TextureCache.hpp>
#include <tools/Tool.hpp>
#include <tools/Math.hpp>


PauseUI::PauseUI() :
    animation(), buttons( __make_btns() ),
    bg(TextureCache::inst().get("pause/bg")),
    shadow(TextureCache::inst().get("pause/shad"))
    {}

void PauseUI::configure( const std::optional<Progressive*>& prog ) {
    if ( prog.has_value() ) (*prog)->add_to_total( 10 );

    this->bg.setOrigin( sf::Vector2f(bg.getTexture().getSize()) / 2.f );
    this->bg_init_y = 1.5f * Tool::HEIGHT;
    this->bg.setPosition( {Tool::W_CTR.x, this->bg_init_y});

    // init buttons bounds to their final position
    for ( int i = 0; i < this->BTN_COUNT; i++ ) {
        static const int width = this->buttons.at(0).getTexture().getSize().x;
        this->bounds.at( i ) = sf::Rect<int>(
            sf::Vector2<int>( Tool::W_CTR.x + ( (20+width)*i - (width+10) ), Tool::W_CTR.y + 40 ),
            this->buttons.at( i ).getTextureRect().size
        );
    }

    this->__move_btns();

    if ( prog.has_value() ) (*prog)->increment_by( 10 );
}

void PauseUI::update( const sf::Time& dt ) {
    this->animation.update( dt );

    const double p = this->animation.progress();

    float y = Math::Lerp(
        this->bg_init_y,
        Tool::W_CTR.y,
        Math::easeOut( p )
    );

    sf::Color bg_c = this->bg.getColor(),
              shadow_c = this->shadow.getColor(),
              btn_c = this->buttons.at(0).getColor();
    bg_c.a = shadow_c.a = btn_c.a = static_cast<uint8_t>( Math::easeInOut(p) * 255 );

    this->bg.setPosition( {this->bg.getPosition().x, y} );
    this->bg.setColor( bg_c );
    this->shadow.setColor( shadow_c );
    this->buttons.at(0).setColor( btn_c );
    this->buttons.at(1).setColor( btn_c );

    this->__move_btns();
}

void PauseUI::exit_animation() {
    this->animation.exit();
}
const bool PauseUI::anim_finished() const {
    return this->animation.finished();
}

const sf::Rect<int>& PauseUI::btn_bound( const int id ) const {
    assert( id >= 0 && id < BTN_COUNT );

    return this->bounds.at( id );
}

void PauseUI::__move_btns() {
    for ( int i = 0; i < this->BTN_COUNT; i++ ) {
        static const int width = this->buttons.at(i).getTexture().getSize().x;

        this->buttons.at( i ).setPosition({
           this->bg.getPosition().x + ( (20 + width)*i - (width+10) ), // 20: horizontal distance between btns, 10: half of it
           this->bg.getPosition().y + 40                             // 40: vertical distance between btns and bg center
        });
    }
}