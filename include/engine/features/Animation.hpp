#pragma once

#include <engine/features/Motion.hpp>


class Animation {
    private:
        Motion __motion;

        void __forward();
        void __backward();

    public:
        enum class Status { In, Out };

    public:
        Animation( const float sec=1.0f );
        ~Animation() = default;

        void update( const sf::Time& );

        void enter();
        void exit();

        const double progress() const;
        const bool   finished() const;

        const Animation::Status status() const;
};
