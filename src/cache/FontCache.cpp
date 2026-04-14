#include <cache/FontCache.hpp>

#include <engine/features/Progressive.hpp>


sf::Font FontCache::ARIAL = sf::Font();
sf::Font FontCache::RASTER = sf::Font();
sf::Font FontCache::KA = sf::Font();


void FontCache::Load( Progressive& prog ) {
    prog.addTotal( 500 );

    if (!(FontCache::ARIAL.openFromFile("assets/fonts/arialFont.ttf")))
        throw std::runtime_error("Cannot load [Font] 'Arial'!");
    prog.incCount( 450 );
    
    if (!(FontCache::RASTER.openFromFile("assets/fonts/RasterForge.ttf")))
        throw std::runtime_error("Cannot load [Font] 'Raster Forge'!");    
    prog.incCount( 20 );
    
    if (!(FontCache::KA.openFromFile("assets/fonts/ka1.ttf")))
        throw std::runtime_error("Cannot load [Font] 'ka'!");
    prog.incCount( 30 );
}