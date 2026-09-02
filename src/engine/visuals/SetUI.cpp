#include <engine/visuals/SetUI.hpp>

#include <cache/TextureCache.hpp>
#include <cache/SFX.hpp>
#include <cache/FontCache.hpp>
#include <tools/Constants.hpp>
#include <tools/Math.hpp>


SetUI::SetUI() :
    animation(),
    modes_spr( __init_modes() ),
    marks_spr( __init_marks() ),
    max_score(FontCache::MineCraf, std::to_string(Constants::maxScore)),
    bg(TextureCache::inst().get("set/bg")),
    shadow(TextureCache::inst().get("shad_1")),
    bg_rect(bg.getTextureRect()),
    bg_init_y(1.5f*Constants::HEIGHT)
    {}

void SetUI::configure() {
    this->bg.setOrigin(
        sf::Vector2f(this->bg.getTexture().getSize()) / 2.f
    );
    this->bg.setPosition( {Constants::W_CTR.x, this->bg_init_y} );

    this->__init_bounds();

    for ( int i = 0; i < this->modes_spr.size(); i++ )
        this->modes_spr.at(i).setPosition(
             this->__normalize<float>(this->bg_rect, {82, 175}) // or just bounds+margin
        );

    this->marks_spr.at(0).setPosition(sf::Vector2f(this->bounds.at(SetUI::BTNS::MUSIC_MARK).position));
    this->marks_spr.at(1).setPosition(sf::Vector2f(this->bounds.at(SetUI::BTNS::SFX_MARK).position));

    this->modes_i.insert({ {'E', 0}, {'M', 1}, {'H', 2} });

    this->max_score.setFillColor(sf::Color(48, 49, 52, 255));
    this->max_score.setOutlineThickness(2.0f);
    this->max_score.setOutlineColor(sf::Color::Black);
    this->max_score.setScale({0.5f, 0.5f});
    this->max_score.setPosition( this->__normalize<float>(this->bg_rect, {108, 221}) );
}

void SetUI::update( const sf::Time& dt ) {
    this->animation.update( dt );

    this->max_score.setString(std::to_string(Constants::maxScore));

    const double p = this->animation.progress();

    float y = Math::Lerp(
        this->bg_init_y,
        Constants::W_CTR.y,
        Math::easeOut( p )
    );
    sf::Color bg_c = this->bg.getColor(),
              shadow_c = this->shadow.getColor();

    bg_c.a = shadow_c.a = static_cast<uint8_t>( Math::easeOut(p) * 255 );

    this->bg.setPosition( {this->bg.getPosition().x, y} );
    this->bg.setColor( bg_c );
    this->shadow.setColor( shadow_c );

    this->__move_elements();
}

void SetUI::exit_animation() {
    this->animation.exit();
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
void SetUI::__move_elements() {
    const sf::Vector2<float> bg_pos = this->bg.getPosition();

    for ( int i = 0; i < 3; i++ ) {
        this->modes_spr.at(i).setPosition({bg_pos.x - 143, bg_pos.y + 25});
        if (i<3) this->marks_spr.at(i).setPosition({bg_pos.x + 103, bg_pos.y + 23 + 44*i});
    }

    this->max_score.setPosition({bg_pos.x - 117, bg_pos.y + 71});

    // this->modes_spr.at(
    //         this->modes_i.at(Constants::MODE.front())
    //     ).setPosition({bg_pos.x - 143, bg_pos.y + 25});
}

const sf::Sprite& SetUI::get_modeSpr( const Json::Type T ) const {
    switch (T) {
        case Json::Type::EASY: return this->modes_spr.at(0);
        case Json::Type::MED: return this->modes_spr.at(1);
        case Json::Type::HARD: return this->modes_spr.at(2);

        default:
            throw std::runtime_error("Invalid 'Constants::MODE' given for 'SetUI::get_modeSpr'");
    }
}