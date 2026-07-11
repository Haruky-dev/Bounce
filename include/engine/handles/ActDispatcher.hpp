#include <engine/Manager.hpp>
#include <engine/input/Action.hpp>

class Manager;


class ActDispatcher {
    friend class Manager;

    static bool handleOutput( Manager&, const Action );
};
