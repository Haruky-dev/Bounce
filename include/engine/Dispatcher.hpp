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
        void process_settings_( const Action );
        void process_layers_( const Action, Manager& );
};