#include <engine/visuals/MenuUI.hpp>

#include <cache/TextureCache.hpp>
#include <cache/FontCache.hpp>
#include <tools/Json.hpp>
#include <tools/Constants.hpp>

#include <SFML/Graphics.hpp>
#include <cassert>


MenuUI::MenuUI() :
    bg(TextureCache::inst().get("mm/bg")),
    credit(TextureCache::inst().get("mm/c")),
    version(TextureCache::inst().get("mm/v")),
    bg_rect(bg.getTextureRect()),
    btns( this->make_btns_() )
    {}


void MenuUI::configure() {
    for (int i{}; i < BTN_COUNT; i++) {
        this->btns.at( i ).setOrigin( sf::Vector2f(this->btns.at( i ).getTexture().getSize()) / 2.f );
        this->btns.at( i ).setPosition({ Constants::W_CTR.x, Constants::W_CTR.y - 90.f * (1-i) });
        this->btns.at( i ).setScale( {2.f, 2.f} );
    }

    this->init_bounds_();

    this->credit.setOrigin( sf::Vector2f(this->credit.getTexture().getSize()) / 2.0f );
    this->credit.setPosition( {Constants::WIDTH - this->credit.getTexture().getSize().x/2.0f , Constants::HEIGHT - 20.0f} );

    this->version.setPosition( {5.0f, 5.0f} );
}

void MenuUI::init_bounds_() {
    this->bounds[MenuUI::BTNS::PLAY] = sf::Rect<int>( this->normalize_<int>(this->bg_rect,
        {(int)Constants::W_CTR.x-50, (int)Constants::W_CTR.y-110}), {100, 40} );
    this->bounds[MenuUI::BTNS::MENU] = sf::Rect<int>( this->normalize_<int>(this->bg_rect,
        {(int)Constants::W_CTR.x-50, (int)Constants::W_CTR.y-20}), {100, 40} );
    this->bounds[MenuUI::BTNS::QUIT] = sf::Rect<int>( this->normalize_<int>(this->bg_rect,
        {(int)Constants::W_CTR.x-50, (int)Constants::W_CTR.y+70}), {100, 40} );
}
