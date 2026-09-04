#pragma once

#include <utility>


namespace Flags {
    inline bool sfxON = true;
    inline bool musicON = true;
    inline bool goalScored = false;
    inline std::pair<bool, bool> freeze({ false, false });
    inline std::pair<bool, bool> invert({ false, false });
};