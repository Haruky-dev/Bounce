#include <engine/visuals/QuitUI.hpp>

#include <cache/TextureCache.hpp>
#include <tools/Json.hpp>
#include <tools/Math.hpp>

#include <SFML/Graphics.hpp>


QuitUI::QuitUI() :
    animation(),
    bg(TextureCache::inst().get("quit/bg")),
    shadow(TextureCache::inst().get("shad_2"))
    {}

void QuitUI::configure( const std::optional<Progressive*>& prog ) {
    if ( prog.has_value() ) (*prog)->add_to_total( 10 );

    this->bg.setOrigin( sf::Vector2<float>(this->bg.getTextureRect().size / 2) );
    this->bg.setPosition(Tool::W_CTR);
    this->bg.setScale({1.5f, 1.5f});

    if ( prog.has_value() ) (*prog)->increment_by( 10 );
}

void QuitUI::update( const sf::Time& dt ) {
    this->animation.update(dt);

    const double p = this->animation.progress();

    sf::Color bg_clr = this->bg.getColor(), shad_clr = this->shadow.getColor();
    bg_clr.a =  static_cast<uint8_t>( Math::easeInOut(p) * 255 );
    shad_clr.a = static_cast<uint8_t>( Math::easeInOut(p) * 180 );

    this->bg.setColor(bg_clr);
    this->shadow.setColor(shad_clr);
}

void QuitUI::exit_animation() { this->animation.exit(); }
