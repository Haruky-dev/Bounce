#pragma once

enum class Action {
    None,

    raiseMain,
    raisePause,
    raisePlay,
    raiseSett,
    raiseQuit,
    raiseGameOv,
    
    incDiff,
    decDiff,
    incMaxScr,
    decMaxScr,
    toggleMusic,
    toggleSFX,

    dropOverlap
};