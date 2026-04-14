#include <cache/visuals/MenuUI.hpp>

#include <cache/TextureCache.hpp>
#include <cache/FontCache.hpp>
#include <tools/Tool.hpp>
#include <tools/Json.hpp>

#include <SFML/Graphics.hpp>
#include <cassert>


MenuUI::MenuUI() :
    bg(TextureCache::inst().get("mm/bg")),
    author( FontCache::RASTER, Json::String("setting.author") ),
    version( author.getFont(), Json::String("setting.version") ),
    btns( this->makeBtns() )
    {}
    

void MenuUI::configure( Progressive& prog ) {
    prog.addTotal( 6 );

    TextureCache& txtCache = TextureCache::inst();

    for (int i{}; i < BTN_COUNT; i++) {
        this->btns.at( i ).setOrigin( sf::Vector2f(this->btns.at( i ).getTexture().getSize()) / 2.f );
        this->btns.at( i ).setPosition({ Tool::W_CTR.x, Tool::W_CTR.y - 90.f * (1-i) });
        this->btns.at( i ).setScale( {2.f, 2.f} );

        this->bounds.at( i ) = Tool::getBound( this->btns.at( i ) );
    }
    
    this->author.setFillColor( sf::Color::Black );
    this->version.setFillColor( sf::Color::Black );
    this->version.setPosition( {20.0f, 20.0f} );

    prog.incCount( 6 );
}

const sf::Rect<int>& MenuUI::btnBound( const int id ) const {
    assert( id >= 0 && id < BTN_COUNT );
    
    return this->bounds[id];
}