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
}

void SFX::play( const SFX::Type T ) {
    if ( !Flags::sfxON || (T==SFX::Type::NONE) ) return;

    this->__sound.emplace( this->__cache.at(T) );
    this->__sound->play();
}