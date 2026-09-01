#pragma once

#include <buffing/Buff.hpp>
#include <buffing/buffs/Freeze.hpp>

#include <SFML/System/Time.hpp>

#include <memory>


class Generator {
    public:
        static std::unique_ptr<Buff> yield();

    // private:
};
