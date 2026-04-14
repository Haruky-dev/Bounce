#pragma once

#include <SFML/System/Time.hpp>

class Transition {
    protected:
        float timeScale = 1;
        float targetSc  = 1;
        int speed       = 1000; // ease it later

    public:
        void initT( const int speed=1000 );
        void resetT();

        sf::Time tick( const sf::Time& dt );
        float scale() const;
        bool done() const;
};