#pragma once

#include <engine/Manager.hpp>
#include <engine/input/Process.hpp>


class Dispatcher {
    friend class Manager;

    static bool handleOutput( Manager&, const Process& );
};