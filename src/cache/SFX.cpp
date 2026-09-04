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
        this->cache_.insert(
            std::make_pair(static_cast<SFX::Type>(i), sf::SoundBuffer())
        );

        if ( !(this->cache_.at( static_cast<SFX::Type>(i) ).loadFromFile(paths.at(i))) )
            throw std::runtime_error("[SFX] Loading failure for path='" + paths.at(i) + "'!");

        prog.increment_by( 20 );
    }

    // seed the pool_ to the first buffer
    this->pool_.reserve(this->POOL_SIZE_);
    for (int i = 0; i < this->POOL_SIZE_; i++ )
        this->pool_.emplace_back( this->cache_.begin()->second );
}

void SFX::play( const SFX::Type T ) {
    if ( !Flags::sfxON || (T==SFX::Type::NONE) ) return;

    // Search for free/available slot
    sf::Sound* slot = nullptr;
    for ( auto& S : this->pool_ )
        if ( S.getStatus() != sf::Sound::Status::Playing ) {
            slot = &S; break;
        }

    // Not found? then use the oldest one
    if ( !slot ) {
        slot = &this->pool_[this->next_slot_];

        // circle next slot index. 0 -> 1 -> .. -> POOL_SIZE_-1 -> 0
        this->next_slot_ = (this->next_slot_+1) % this->POOL_SIZE_; 
    }

    slot->setBuffer( this->cache_.at(T) );
    slot->setVolume(150);
    slot->play();
}