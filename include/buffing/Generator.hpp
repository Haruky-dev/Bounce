#pragma once

#include <buffing/Buff.hpp>
#include <buffing/buffs/Freeze.hpp>

#include <SFML/System/Time.hpp>

#include <memory>
#include <initializer_list>


class Generator {
    public:
        static std::unique_ptr<Buff> yield();

    private:
        static Buff::Target randTarget( const std::initializer_list<Buff::Target> );
};
