#include <engine/visuals/EndUI.hpp>

#include <cache/TextureCache.hpp>
#include <cache/FontCache.hpp>
#include <tools/Tool.hpp>


EndUI::EndUI() :
    bg(TextureCache::inst().get("end/bg")),
    winner(TextureCache::inst().get("end/winner")),
    menu_btn(TextureCache::inst().get("end/btn/ret")),
    replay_btn(TextureCache::inst().get("end/btn/ret")),
    human_score(FontCache::KA, ""),
    ai_score(human_score.getFont(), "")
    // shadow(TextureCache::inst().get("set/shad"))
    {}
    
void EndUI::configure( const std::optional<Progressive*>& prog ) {
    if ( prog.has_value() ) (*prog)->add_to_total( 10 );

    this->bg.setOrigin( sf::Vector2f(this->bg.getTexture().getSize()) / 2.f );
    this->bg.setPosition( Tool::W_CTR );

    this->relative_place(replay_btn, {112.f,  247.f});
    this->relative_place(menu_btn,   {338.f,  247.f}); // 450 - 112
    this->relative_place(winner,     {338.f,  193.f}); // above the AI button, 154+39 = 193

    // this->replay_btn.setOrigin( sf::Vector2f(this->replay_btn.getTexture().getSize()) / 2.0f );
    // this->relative_place( replay_btn, {31.0f, 210.0f});
    // this->relative_place( menu_btn, {-31.0f, 210.0f});
    // // assume Computer won for now, just as a prototype
    // this->relative_place( winner, {-31.0f, 217.0f}); // y= 154 + 39 + 50/2

    if ( prog.has_value() ) (*prog)->increment_by( 10 );
}

void EndUI::relative_place( sf::Sprite& spr, const sf::Vector2<float>& pos) {
    const sf::Vector2f bg_pos = this->bg.getGlobalBounds().position;

    spr.setOrigin( sf::Vector2<float>( spr.getTexture().getSize() ) / 2.0f );
    spr.setPosition( bg_pos + pos );
}