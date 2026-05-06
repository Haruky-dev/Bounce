#include <cache/TextureCache.hpp>

#include <engine/layers/LoadLayer.hpp>

#include <algorithm>


TextureCache& TextureCache::inst() {
    static TextureCache inst = TextureCache();
    
    return inst;
}

void TextureCache::Load( Progressive& prog ) {
    const std::vector<TextureCache::Asset> properties = { /* 1kb -> .5 units */
        { "assets/UI/Menu/bg.jpg", "mm/bg", 120 },              /* MainMenu layer assets */
        { "assets/UI/Menu/credit.png", "mm/c", 3 },
        { "assets/UI/Menu/v.png", "mm/v", 2 },
        { "assets/UI/Menu/play.png", "mm/btn/play", 3 },
        { "assets/UI/Menu/menu.png", "mm/btn/set", 3 },
        { "assets/UI/Menu/quit.png", "mm/btn/q", 3 }, 
    
        { "assets/holdBg.png", "h/bg", 4 },                     /* Hold Layer assets */

        { "assets/UI/Setting/bg.png", "set/bg", 20 },           /* Setting layer assets */
        { "assets/UI/Setting/shadow.png", "set/shad", 20 },

        { "assets/UI/Game/bg.png", "play/bg", 3 },              /* Game layer assets */
        { "assets/UI/Game/paddle.png", "play/pad", 1 },
        { "assets/UI/Game/ball.png", "play/ball", 1 },
        

        { "assets/UI/Pause/shadow.png", "pause/shad", 1 },      /* Pause layer assets */
        { "assets/UI/Pause/bg.png", "pause/bg", 2 },
        { "assets/UI/Pause/quit.png", "pause/btn/quit", 1 },
        { "assets/UI/Pause/resume.png", "pause/btn/resume", 1 },

        { "assets/EndBg.png", "end/bg", 50 },                   /* End layer assets */
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