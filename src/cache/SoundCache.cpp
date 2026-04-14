#include <cache/SoundCache.hpp>

#include <engine/layers/LoadLayer.hpp>


sf::SoundBuffer SoundCache::paddleBUF;
sf::SoundBuffer SoundCache::wallBUF;

void SoundCache::Load( Progressive& prog ) {
    prog.addTotal( 50 );

    paddleBUF = sf::SoundBuffer("assets/sfx/padHit.wav");
    prog.incCount( 20 );

    wallBUF = sf::SoundBuffer("assets/sfx/wallHit.wav");
    prog.incCount( 20 );
}