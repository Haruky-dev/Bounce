#pragma once

#include <engine/request/Constraint.hpp>
#include <engine/request/Context.hpp>

#include <chrono>


class Cooldown : public Constraint {
    private:
        int T;
        mutable std::chrono::steady_clock::time_point lastUse;

    public:
        Cooldown( int ms ) : T(ms), lastUse() {}

        bool satisfied( const Context& context ) const override {
            bool first_call = this->lastUse.time_since_epoch().count() == 0;
            bool elapsed    = std::chrono::duration_cast<std::chrono::milliseconds>(context.now - this->lastUse).count() > this->T;

            if ( first_call || elapsed ) {
                this->lastUse = context.now;
                return true;
            } else return false;
        }
}; 