#include <cache/TextureCache.hpp>

#include <engine/layers/LoadLayer.hpp>


TextureCache& TextureCache::inst() {
    static TextureCache inst = TextureCache();
    
    // This func
    return inst;
}


void TextureCache::Load( Progressive& prog ) {
    prog.addTotal( 260 ); // 1kb -> .5 units

    //-- [MainMenu] State
    this->cache["mm/bg"] = std::make_unique<sf::Texture>();
    if (!(this->cache["mm/bg"]->loadFromFile("assets/MMbg.jpg")))
        throw std::runtime_error("Cannot load [Texture] 'MainMenu/bg'!");
    prog.incCount( 120 );

    this->cache["mm/btn/play"] = std::make_unique<sf::Texture>();
    if (!(this->cache["mm/btn/play"]->loadFromFile( "assets/play.png" )))   //-- buttons
        throw std::runtime_error("Cannot load [Texture] 'MainMenu/Button/play'!");
    prog.incCount( 2 );

    this->cache["mm/btn/set"] = std::make_unique<sf::Texture>();
    if (!(this->cache["mm/btn/set"]->loadFromFile( "assets/set.png" )))
        throw std::runtime_error("Cannot load [Texture] 'MainMenu/Button/Setting'!");
    prog.incCount( 2 );

    this->cache["mm/btn/q"] = std::make_unique<sf::Texture>();
    if (!(this->cache["mm/btn/q"]->loadFromFile( "assets/quit.png" )))
        throw std::runtime_error("Cannot load [Texture] 'MainMenu/Button/Quit'!");
    prog.incCount( 2 );

    //= [Setting] State
    this->cache["set/bg"] = std::make_unique<sf::Texture>();
    if (!(this->cache["set/bg"]->loadFromFile( "assets/menu.png" )))
        throw std::runtime_error("Cannot load [Texture] 'Setting/bg'!");
    prog.incCount( 19 );

    this->cache["set/shad"] = std::make_unique<sf::Texture>();
    if (!(this->cache["set/shad"]->loadFromFile( "assets/shadow_1.png" )))
        throw std::runtime_error("Cannot load [Texture] 'Setting/Shadow'!");
    prog.incCount( 19 );

    //= [Play] State
    this->cache["play/bg"] = std::make_unique<sf::Texture>();
    if (!(this->cache["play/bg"]->loadFromFile( "assets/gameBg.png" )))
        throw std::runtime_error("Cannot load [Texture] 'play/bg'!");
    prog.incCount( 35 );

    this->cache["play/pad"] = std::make_unique<sf::Texture>();
    if (!(this->cache["play/pad"]->loadFromFile( "assets/pad.png" )))
        throw std::runtime_error("Cannot load [Texture] 'play/pad'!");
    prog.incCount( 1 );

    this->cache["play/ball"] = std::make_unique<sf::Texture>();
    if (!(this->cache["play/ball"]->loadFromFile( "assets/ball.png" )))
        throw std::runtime_error("Cannot load [Texture] 'play/ball'!");
    prog.incCount( 1 );
    
    this->cache["pause/shad"] = std::make_unique<sf::Texture>();
    if (!(this->cache["pause/shad"]->loadFromFile( "assets/shadow_2.png" )))
        throw std::runtime_error("Cannot load [Texture] 'pause/shadow'!");
    prog.incCount( 4 );
    
    this->cache["pause/bg"] = std::make_unique<sf::Texture>();
    if (!(this->cache["pause/bg"]->loadFromFile( "assets/p_menu.png" )))
        throw std::runtime_error("Cannot load [Texture] 'pause/bg'!");
    prog.incCount( 40 );
}

const sf::Texture& TextureCache::get( const std::string& id ) const {

    if ( this->cache.find( id ) == this->cache.end() )
        throw std::runtime_error("Invalid given [ID] for 'Texture' look-up!");

    return *( this->cache.at( id ) );
}