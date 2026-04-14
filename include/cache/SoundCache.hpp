#pragma once

#include <SFML/Audio.hpp>


class Progressive;


class SoundCache {
    private:
        friend class LoadLayer;
        static void Load( Progressive& );

    public:
        static sf::SoundBuffer paddleBUF;
        static sf::SoundBuffer wallBUF;
};