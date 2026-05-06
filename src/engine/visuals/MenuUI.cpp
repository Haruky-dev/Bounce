#include <engine/visuals/MenuUI.hpp>

#include <cache/TextureCache.hpp>
#include <cache/FontCache.hpp>
#include <tools/Tool.hpp>
#include <tools/Json.hpp>

#include <SFML/Graphics.hpp>
#include <cassert>


MenuUI::MenuUI() :
    bg(TextureCache::inst().get("mm/bg")),
    credit(TextureCache::inst().get("mm/c")),
    version(TextureCache::inst().get("mm/v")),
    btns( this->makeBtns() )
    {}
    

void MenuUI::configure( const std::optional<Progressive*>& prog ) {
    if ( prog.has_value() ) (*prog)->add_to_total( 10 );

    for (int i{}; i < BTN_COUNT; i++) {
        this->btns.at( i ).setOrigin( sf::Vector2f(this->btns.at( i ).getTexture().getSize()) / 2.f );
        this->btns.at( i ).setPosition({ Tool::W_CTR.x, Tool::W_CTR.y - 90.f * (1-i) });
        this->btns.at( i ).setScale( {2.f, 2.f} );

        this->bounds.at( i ) = Tool::getBound( this->btns.at( i ) );
    }
    
    this->credit.setOrigin( sf::Vector2f(this->credit.getTexture().getSize()) / 2.0f );
    this->credit.setPosition( {Tool::WIDTH - this->credit.getTexture().getSize().x/2.0f , Tool::HEIGHT - 20.0f} );

    // this->version.setOrigin( sf::Vector2f(this->version.getTexture().getSize()) / 2.0f );
    this->version.setPosition( {5.0f, 5.0f} );

    if ( prog.has_value() ) (*prog)->increment_by( 10 );
}

const sf::Rect<int>& MenuUI::btn_bound( const int id ) const {
    assert( id >= 0 && id < BTN_COUNT );
    
    return this->bounds[id];
}