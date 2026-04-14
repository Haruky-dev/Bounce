#include <cache/visuals/SetUI.hpp>

#include <cache/TextureCache.hpp>
#include <tools/Tool.hpp>


SetUI::SetUI() :
    bg(TextureCache::inst().get("set/bg")),
    shad(TextureCache::inst().get("set/shad")),
    shadClr(shad.getColor()),
    bg_initY(Tool::HEIGHT + bg.getPosition().y / 2.f)
    {}

void SetUI::configure( Progressive& prog ) {
    prog.addTotal( 5 );

    this->bg.setOrigin(
        sf::Vector2f(this->bg.getTexture().getSize()) / 2.f
    );

    this->bg.setPosition( {Tool::W_CTR.x, this->bg_initY} );

    prog.incCount( 5 );
}