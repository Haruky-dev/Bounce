#pragma once

#include <engine/features/Motion.hpp>


class Animated {
    private:
        bool finished;
        bool onExit;

    protected:
        explicit Animated() : finished(false), onExit(false) {}

    public:
        Motion animation;
    
    public:
        virtual void setDone( const bool flag ) { this->finished = flag; }
        virtual void setExit( const bool flag ) { this->onExit = flag; }

        virtual bool isDone() const { return this->finished; }
        virtual bool isExited() const { return this->onExit; }
};