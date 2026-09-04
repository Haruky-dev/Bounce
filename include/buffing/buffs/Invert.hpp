#pragma once

#include <buffing/Buff.hpp>
#include <tools/Flags.hpp>

#include <iostream>


class Invert : public Buff {
    public:
        Invert( Buff::Target T, int duration ) :
            Buff(T), elapsed_(sf::Time::Zero), duration_(duration),
            cache_(Flags::invert.first, Flags::invert.second)
            {
                std::cout << "  -- Invert ";
            }

        void update( const sf::Time& dt ) override {
            if ( this->elapsed_.asMilliseconds() >= this->duration_ ) {
                this->elapsed_ = sf::Time::Zero;
                this->status   = Buff::Status::OFF;
            }

            this->elapsed_ += dt;
        }

        void apply() override {
            // save && apply
            switch (this->target) {
                case Buff::Target::P1:
                    this->cache_.first = Flags::invert.first;
                    Flags::invert.first = true;
                    break;
                case Buff::Target::P2:
                    this->cache_.second = Flags::invert.second;
                    Flags::invert.second = true;
                    break;

                default: throw std::runtime_error("Invalid 'Buff::Target' given to 'Buff::Invert'");
            }
        }

        void revert() override {
            // restore
            switch (this->target) {
                case Buff::Target::P1:
                    Flags::invert.first  = this->cache_.first; break;
                case Buff::Target::P2:
                    Flags::invert.second = this->cache_.second; break;

                default: throw std::runtime_error("Invalid 'Buff::Target' given to 'Buff::Invert'");
            }
        }

        
    private:
        sf::Time elapsed_;
        std::pair<bool, bool> cache_;
        int duration_;
};