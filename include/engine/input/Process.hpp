#pragma once

#include <cache/SFX.hpp>


class Process {
    public:
        enum class Action {
            NONE,
    
            raiseMain, raisePause, raisePlay,
            raiseSett, raiseQuit, raiseGameOv,
    
            dropOverlap,
    
            incDiff, decDiff, incMaxScr,
            decMaxScr, toggleMusic, toggleSFX,
    
            QUIT
        };

    public:
        Process();
        Process( const Process::Action A, const SFX::Type S=SFX::Type::NONE );

        Process::Action act() const;
        SFX::Type       sfx() const;

    private:
        std::pair<Process::Action, SFX::Type> __p;
};