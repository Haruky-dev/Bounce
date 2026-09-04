#pragma once

#include <buffing/Buff.hpp>
#include <tools/Flags.hpp>

#include <iostream>


class Freeze : public Buff {
    public:
        Freeze( Buff::Target T, int duration ) :
            Buff(T), elapsed_(sf::Time::Zero), duration_(duration),
            flags_cache_(Flags::PlayerFrozen, Flags::PlayerFrozen)
            {
                std::cout << "  -- Freeze ";
            }

        void update( const sf::Time& dt ) override {
            if ( this->elapsed_.asMilliseconds() >= this->duration_ ) {
                this->elapsed_ = sf::Time::Zero;
                this->status = Buff::Status::OFF;
                return;
        }

            this->elapsed_ += dt;
        }

        void apply() override {
            // save && apply
            switch (this->target) {
                case Buff::Target::P1:
                    this->flags_cache_.first = Flags::PlayerFrozen;
                    Flags::PlayerFrozen = true;
                    break;
                case Buff::Target::P2:
                    this->flags_cache_.second = Flags::computFrozen;
                    Flags::computFrozen = true;
                    break;

                default: throw std::runtime_error("Invalid 'Buff::Target' given to Buff::Freeze");
            }
        }
        void revert() override {
            // restore
            switch (this->target) {
                case Buff::Target::P1:
                    Flags::PlayerFrozen = this->flags_cache_.first; break;
                case Buff::Target::P2:
                    Flags::computFrozen = this->flags_cache_.second; break;

                default: throw std::runtime_error("Invalid 'Buff::Target' given to Buff::Freeze");
            }
        }

    public:
        sf::Time elapsed_;
        std::pair<bool, bool> flags_cache_;
        int duration_;
};