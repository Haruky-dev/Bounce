#include <cache/visuals/EndUI.hpp>

#include <cache/TextureCache.hpp>


EndUI::EndUI() :
    bg(TextureCache::inst().get("pause/bg"))
    {}
    
void EndUI::configure( Progressive& prog ) {
    prog.addTotal( 1 );
    
    
    prog.incCount( 1 );
}