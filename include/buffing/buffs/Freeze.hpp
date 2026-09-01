#pragma once

#include <buffing/Buff.hpp>

#include <iostream>


class Freeze : public Buff {
    public:
        Freeze( Buff::Target T )
            : Buff(T), elapsed(sf::Time::Zero), duration(1000) {}

        void update( const sf::Time& dt ) override {
            if ( this->elapsed.asMilliseconds() >= this->duration ) {
                this->elapsed = sf::Time::Zero;
                this->status = Buff::Status::OFF;
                return;
        }

            this->elapsed += dt;
        }

        void apply() override {
            // Flags::forzen = true;
        }
        void revert() override {
            // Flags::frozen = false;
        }

    public:
        Buff::Target target;
        sf::Time elapsed;
        int duration;
};
