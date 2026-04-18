#include <engine/visuals/HoldUI.hpp>

#include <cache/TextureCache.hpp>
#include <tools/Tool.hpp>


HoldUI::HoldUI() :
    BaseUI(),
    bg(TextureCache::inst().get("h/bg"))
    {}

void HoldUI::configure( const std::optional<Progressive*>& prog ) {
    if ( prog.has_value() ) (*prog)->add_to_total( 10 );

    this->bg.setOrigin( this->bg.getLocalBounds().getCenter() );
    this->bg.setPosition( Tool::W_CTR );
    
    if ( prog.has_value() ) (*prog)->increment_by( 10 );
}