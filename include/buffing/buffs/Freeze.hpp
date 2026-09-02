#pragma once

#include <buffing/Buff.hpp>
#include <tools/Flags.hpp>

#include <iostream>


class Freeze : public Buff {
    public:
        Freeze( Buff::Target T, int duration ) :
            Buff(T), _elapsed(sf::Time::Zero), _duration(duration),
            _org_flags(Flags::PlayerFrozen, Flags::PlayerFrozen)
            {
                std::cout << "  -- Freeze ";
            }

        void update( const sf::Time& dt ) override {
            if ( this->_elapsed.asMilliseconds() >= this->_duration ) {
                this->_elapsed = sf::Time::Zero;
                this->status = Buff::Status::OFF;
                return;
        }

            this->_elapsed += dt;
        }

        void apply() override {
            // save && apply
            switch (this->target) {
                case Buff::Target::P1:
                    this->_org_flags.first = Flags::PlayerFrozen;
                    Flags::PlayerFrozen = true;
                    break;
                case Buff::Target::P2:
                    this->_org_flags.second = Flags::computFrozen;
                    Flags::computFrozen = true;
                    break;

                default: throw std::runtime_error("Invalid 'Buff::Target' given to Buff::Freeze");
            }
        }
        void revert() override {
            // restore
            switch (this->target) {
                case Buff::Target::P1:
                    Flags::PlayerFrozen = this->_org_flags.first; break;
                case Buff::Target::P2:
                    Flags::computFrozen = this->_org_flags.second; break;

                default: throw std::runtime_error("Invalid 'Buff::Target' given to Buff::Freeze");
            }
        }

    public:
        sf::Time _elapsed;
        std::pair<bool, bool> _org_flags;
        int _duration;
};