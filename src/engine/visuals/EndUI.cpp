#include <engine/visuals/EndUI.hpp>

#include <cache/TextureCache.hpp>


EndUI::EndUI() :
    bg(TextureCache::inst().get("pause/bg"))
    {}
    
void EndUI::configure( Progressive& prog ) {
    prog.add_to_total( 1 );
    
    
    prog.increment_by( 1 );
}