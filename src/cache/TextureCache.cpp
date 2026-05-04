#include <cache/TextureCache.hpp>

#include <engine/layers/LoadLayer.hpp>

#include <algorithm>


TextureCache& TextureCache::inst() {
    static TextureCache inst = TextureCache();
    
    return inst;
}

void TextureCache::Load( Progressive& prog ) {
    const std::vector<TextureCache::Asset> properties = { /* 1kb -> .5 units */
        { "assets/MMbg.jpg", "mm/bg", 120 },        /* MainMenu layer assets */
        { "assets/credit_gh.png", "mm/c", 3 },
        { "assets/version.png", "mm/v", 2 },
        { "assets/play.png", "mm/btn/play", 4 },
        { "assets/set.png", "mm/btn/set", 4 },
        { "assets/quit.png", "mm/btn/q", 4 },
        
        { "assets/holdBg.png", "h/bg", 4 },        /* Hold Layer assets */

        { "assets/menu.png", "set/bg", 4 },         /* Setting layer assets */
        { "assets/shadow_1.png", "set/shad", 20 },

        // { "assets/gameBg.png", "play/bg", 44 },     /* Game layer assets */
        { "assets/gameBg_1.png", "play/bg", 2 },
        { "assets/pad.png", "play/pad", 2 },
        { "assets/ball.png", "play/ball", 2 },

        { "assets/shadow_2.png", "pause/shad", 4 }, /* Pause layer assets */
        { "assets/p_menu.png", "pause/bg", 44 },

        { "assets/EndBg.png", "end/bg", 50 },       /* End layer assets */
        { "assets/return.png", "end/btn/ret", 4 },
        { "assets/replay.png", "end/btn/rep", 5 },
        { "assets/winner.png", "end/winner", 1 }
    };

    prog.add_to_total(
        std::ranges::fold_left(
            properties, 0,
            [] ( int acc, const TextureCache::Asset& that ) {
                return acc + that.weight;
            }
        )
    );

    this->__cache.reserve( properties.size() );

    for ( const Asset& that : properties ) {
        this->__cache[ that.id ] = std::make_unique<sf::Texture>();

        if ( !(this->__cache.at( that.id )->loadFromFile( that.path )) )
            throw std::runtime_error(
                "Cannot load [Texture] at path: '" + that.path + "' !"
            );    

        prog.increment_by( that.weight );
    }
}

const sf::Texture& TextureCache::get( const std::string& id ) const {
    const auto it = this->__cache.find( id );

    if ( it == this->__cache.end() )
        throw std::runtime_error(
            "Invalid given [ID] (id==" + id + ") for 'Texture' look-up!"
        );

    return *(it->second);
}