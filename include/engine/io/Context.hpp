#pragma once

#include <chrono>

#include <engine/io/Input.hpp>


struct Context {
    std::chrono::steady_clock::time_point now;
    Input input;

    Context() = default;
    Context( const std::chrono::steady_clock::time_point& now, const Input& in )
        : now(now), input(in) {}
};