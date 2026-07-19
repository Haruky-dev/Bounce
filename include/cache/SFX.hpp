#pragma once

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

#include <unordered_map>
#include <utility>


class Progressive;

class SFX {
    friend class LoadLayer;

    SFX()  = default;
    ~SFX() = default;
    SFX( const SFX& ) = delete;

    SFX& operator=( const SFX& ) = delete;
    SFX& operator=( const SFX&& ) = delete;

    public:
        enum class Type {
            PAD, WALL, CLICK, WHOOSH, WIN, LOSE, NONE
        };
    public:
        static SFX& inst();
        void play( const SFX::Type );

    private:
        void Load( Progressive& );

        std::unordered_map<SFX::Type, sf::SoundBuffer> __cache;
        std::optional<sf::Sound> __sound;
};
