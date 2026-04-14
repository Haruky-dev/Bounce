#pragma once

#include <engine/features/Motion.hpp>


class Animated {
    private:
        bool done;
        bool exit;

    protected:
        explicit Animated() : done(false), exit(false) {}

    public:
        Motion animation;
    
    public:
        virtual void setDone( const bool flag ) { this->done = flag; }
        virtual void setExit( const bool flag ) { this->exit = flag; }

        virtual bool isDone() const { return this->done; }
        virtual bool isExited() const { return this->exit; }
};