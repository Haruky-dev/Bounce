#include <engine/visuals/PauseUI.hpp>

#include <cache/TextureCache.hpp>
#include <tools/Constants.hpp>
#include <tools/Math.hpp>


PauseUI::PauseUI() :
    animation(), buttons( __make_btns() ),
    bg(TextureCache::inst().get("pause/bg")),
    shadow(TextureCache::inst().get("shad_1")),
    bg_rect(bg.getTextureRect())
    {}

void PauseUI::configure() {
    this->bg.setOrigin( sf::Vector2f(bg.getTexture().getSize()) / 2.f );
    this->bg_init_y = 1.5f * Constants::HEIGHT;
    this->bg.setPosition( {Constants::W_CTR.x, this->bg_init_y});

    // init buttons bounds to their final position
    this->bounds[PauseUI::BTNS::QUIT] = sf::Rect<int>(
        this->__normalize<int>( this->bg_rect, {20, 190} ), {190, 70}
    );
    this->bounds[PauseUI::BTNS::RESUME] = sf::Rect<int>(
        this->__normalize<int>( this->bg_rect, {240, 190} ), {190, 70}
    );

    this->__move_btns();
}

void PauseUI::update( const sf::Time& dt ) {
    this->animation.update( dt );

    const double p = this->animation.progress();

    float y = Math::Lerp(
        this->bg_init_y,
        Constants::W_CTR.y,
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

void PauseUI::__move_btns() {
    for ( int i = 0; i < this->BTN_COUNT; i++ ) {
        static const int width = this->buttons.at(i).getTexture().getSize().x;

        this->buttons.at( i ).setPosition({
           this->bg.getPosition().x + ( (30 + width)*i - (width+15) ), // 30: horizontal distance between btns, 15: half of it
           this->bg.getPosition().y + 40                               // 40: vertical distance between btns and bg center
        });
    }
}