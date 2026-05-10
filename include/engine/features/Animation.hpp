#pragma once

#include <engine/features/Motion.hpp>


class Animation {
    private:
        Motion motion;

        void forward();
        void backward();

    public:
        enum class Status { In, Out };

    public:
        Animation();
        ~Animation() = default;

        void update( const sf::Time& );

        void exit();
        void set_duration( const float time );

        const double progress() const;
        const bool   finished() const;

        const Animation::Status status() const;
};