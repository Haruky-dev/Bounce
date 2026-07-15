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
    bg_rect(bg.getTextureRect()),
    btns( this->__make_btns() )
    {}


void MenuUI::configure() {
    for (int i{}; i < BTN_COUNT; i++) {
        this->btns.at( i ).setOrigin( sf::Vector2f(this->btns.at( i ).getTexture().getSize()) / 2.f );
        this->btns.at( i ).setPosition({ Tool::W_CTR.x, Tool::W_CTR.y - 90.f * (1-i) });
        this->btns.at( i ).setScale( {2.f, 2.f} );
    }

    this->__init_bounds();

    this->credit.setOrigin( sf::Vector2f(this->credit.getTexture().getSize()) / 2.0f );
    this->credit.setPosition( {Tool::WIDTH - this->credit.getTexture().getSize().x/2.0f , Tool::HEIGHT - 20.0f} );

    // this->version.setOrigin( sf::Vector2f(this->version.getTexture().getSize()) / 2.0f );
    this->version.setPosition( {5.0f, 5.0f} );
}

void MenuUI::__init_bounds() {
    this->bounds[MenuUI::BTNS::PLAY] = sf::Rect<int>( this->__normalize<int>(this->bg_rect,
        {(int)Tool::W_CTR.x-50, (int)Tool::W_CTR.y-110}), {100, 40} );
    this->bounds[MenuUI::BTNS::MENU] = sf::Rect<int>( this->__normalize<int>(this->bg_rect,
        {(int)Tool::W_CTR.x-50, (int)Tool::W_CTR.y-20}), {100, 40} );
    this->bounds[MenuUI::BTNS::QUIT] = sf::Rect<int>( this->__normalize<int>(this->bg_rect,
        {(int)Tool::W_CTR.x-50, (int)Tool::W_CTR.y+70}), {100, 40} );
}
