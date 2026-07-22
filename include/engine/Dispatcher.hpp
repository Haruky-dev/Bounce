#pragma once

#include <engine/Manager.hpp>
#include <engine/io/Action.hpp>


class Dispatcher {
    public:
        static Dispatcher& inst() {
            static Dispatcher I = Dispatcher();
            return I;
        }

        void handle( Manager&, const Action );

    private:
        void __process_settings( const Action );
        void __process_layers( const Action, Manager& );
};