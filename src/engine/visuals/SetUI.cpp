#include <engine/visuals/SetUI.hpp>

#include <cache/TextureCache.hpp>
#include <cache/FontCache.hpp>
#include <tools/Tool.hpp>
#include <tools/Math.hpp>


SetUI::SetUI() :
    animation(),
    modes_spr( __init_modes() ),
    marks_spr( __init_marks() ),
    max_score(FontCache::MineCraf, std::to_string(Tool::maxScore)),
    bg(TextureCache::inst().get("set/bg")),
    shadow(TextureCache::inst().get("set/shad")),
    bg_rect(bg.getTextureRect()),
    bg_init_y(1.5f*Tool::HEIGHT)
    {}

void SetUI::configure( const std::optional<Progressive*>& prog ) {
    if ( prog.has_value() ) (*prog)->add_to_total( 5 );

    this->bg.setOrigin(
        sf::Vector2f(this->bg.getTexture().getSize()) / 2.f
    );
    this->bg.setPosition( {Tool::W_CTR.x, this->bg_init_y} );

    this->__init_bounds();

    for ( int i = 0; i < this->modes_spr.size(); i++ )
        this->modes_spr.at(i).setPosition(
             this->__normalize<float>(this->bg_rect, {72, 175}) // or just bounds+margin
        );

    // // this->max_score.setPosition(Vector2f position)
    
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

std::array<sf::Sprite, 3> SetUI::__init_modes() const {
    return std::array<sf::Sprite, 3>({
        sf::Sprite(TextureCache::inst().get("set/mode/easy")),
        sf::Sprite(TextureCache::inst().get("set/mode/even")),
        sf::Sprite(TextureCache::inst().get("set/mode/hard"))
    });
}
std::array<sf::Sprite, 2> SetUI::__init_marks() const {
    return std::array<sf::Sprite, 2>({
       sf::Sprite(TextureCache::inst().get("set/mark")), 
       sf::Sprite(TextureCache::inst().get("set/mark"))
    });
}
void SetUI::__init_bounds() {
    this->bounds[BTNS::DIF_ARW_INC] = sf::Rect<int>( this->__normalize<int>( this->bg_rect, {47, 173} ),  {20, 20} );
    this->bounds[BTNS::DIF_ARW_DEC] = sf::Rect<int>( this->__normalize<int>( this->bg_rect, {159, 173} ), {20, 20} );
    this->bounds[BTNS::SCR_ARW_INC] = sf::Rect<int>( this->__normalize<int>( this->bg_rect, {78, 218} ),  {20, 20} );
    this->bounds[BTNS::SCR_ARW_DEC] = sf::Rect<int>( this->__normalize<int>( this->bg_rect, {131, 218} ), {20, 20} );
    this->bounds[BTNS::MUSIC_MARK]  = sf::Rect<int>( this->__normalize<int>( this->bg_rect, {327, 171} ), {20, 20} );
    this->bounds[BTNS::SFX_MARK]    = sf::Rect<int>( this->__normalize<int>( this->bg_rect, {327, 215} ), {20, 20} );
    this->bounds[BTNS::EXIT]        = sf::Rect<int>( this->__normalize<int>( this->bg_rect, {400, 20} ),  {30, 30} );
}