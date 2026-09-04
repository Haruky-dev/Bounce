#pragma once

#include <SFML/System/Time.hpp>


class Buff {
    public:
        enum class Target { P1, P2, Ball };
        enum class Status { ON, OFF };
        enum class Type   { Freeze, Invert };

    public:
        // arg: context
        virtual void update( const sf::Time& ) = 0;
        virtual void apply()  {}
        virtual void revert() {}

        Buff( Buff::Target T ) : target(T), status(Buff::Status::ON) {}
        virtual ~Buff() = default;

    public:
        Buff::Target target;
        Buff::Status status;
};
