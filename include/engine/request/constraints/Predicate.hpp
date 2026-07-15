#pragma once

#include <engine/request/Constraint.hpp>

#include <functional>


class Predicate : public Constraint {
    private:
        std::function<bool()> func;

    public:
        Predicate( std::function<bool()> f ) : func(std::move(f)) {}

        bool satisfied( const Context& context ) const override {
            return this->func();
        }
};