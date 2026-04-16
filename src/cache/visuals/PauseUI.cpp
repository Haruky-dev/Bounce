#include <cache/visuals/PauseUI.hpp>

#include <tools/Tool.hpp>


PauseUI::PauseUI() :
    bg(TextureCache::inst().get("pause/bg")),
    shad(TextureCache::inst().get("pause/shad")),
    bgClr(bg.getColor()),
    shadClr(shad.getColor()),
    bg_initY( Tool::HEIGHT + bg.getTexture().getSize().y / 2.f )
    {}

void PauseUI::configure( const std::optional<Progressive*>& prog ) {
    if ( prog.has_value() ) (*prog)->addTotal( 5 );

    this->bg.setOrigin( sf::Vector2f(bg.getTexture().getSize()) / 2.f );
    this->bg.setPosition( {Tool::W_CTR.x, this->bg_initY});

    if ( prog.has_value() ) (*prog)->incCount( 5 );
}