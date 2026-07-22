#pragma once

enum class Action {
    NONE,

    raiseMain, raisePause, raisePlay,
    raiseSett, raiseQuit, raiseGameOv,

    dropOverlap,

    incDiff, decDiff, incMaxScr,
    decMaxScr, toggleMusic, toggleSFX,

    Quit
};