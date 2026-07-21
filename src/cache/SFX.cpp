#include <cache/SFX.hpp>

#include <engine/features/Progressive.hpp>
#include <tools/Flags.hpp>

#include <string>
#include <array>



SFX& SFX::inst() {
    static SFX I = SFX();
    return I;
}

void SFX::Load( Progressive& prog ) {
    prog.add_to_total( 100 );

    std::array<std::string, (size_t) SFX::Type::NONE> paths = {
        "assets/sfx/padHit.wav", "assets/sfx/wallHit.wav",
        "assets/sfx/msClick.wav", "assets/sfx/whoosh.wav",
        "assets/sfx/win.wav", "assets/sfx/lose.wav"
    };

    for ( size_t i = 0; i < paths.size(); i++ ) {
        this->__cache.insert(
            std::make_pair(static_cast<SFX::Type>(i), sf::SoundBuffer())
        );

        if ( !(this->__cache.at( static_cast<SFX::Type>(i) ).loadFromFile(paths.at(i))) )
            throw std::runtime_error("[SFX] Loading failure for path='" + paths.at(i) + "'!");

        prog.increment_by( 20 );
    }

    // seed the __pool to the first buffer
    this->__pool.reserve(this->POOL_SIZE);
    for (int i = 0; i < this->POOL_SIZE; i++ )
        this->__pool.emplace_back( this->__cache.begin()->second );
}

void SFX::play( const SFX::Type T ) {
    if ( !Flags::sfxON || (T==SFX::Type::NONE) ) return;

    // Search for free/available slot
    sf::Sound* slot = nullptr;
    for ( auto& S : this->__pool )
        if ( S.getStatus() != sf::Sound::Status::Playing ) {
            slot = &S; break;
        }

    // Not found? then use the oldest one
    if ( !slot ) {
        slot = &this->__pool[this->next_slot];

        // circle next slot index. 0 -> 1 -> .. -> POOL_SIZE-1 -> 0
        this->next_slot = (this->next_slot+1) % this->POOL_SIZE; 
    }

    slot->setBuffer( this->__cache.at(T) );
    slot->setVolume(150);
    slot->play();
}