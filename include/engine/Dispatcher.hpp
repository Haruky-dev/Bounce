#pragma once

#include <engine/Manager.hpp>
#include <engine/io/Process.hpp>


class Dispatcher {
    public:
        static Dispatcher& inst() {
            static Dispatcher I = Dispatcher();
            return I;
        }

        void handle( Manager&, const Process& );

    private:
        void __process_settings( const Process::Action );
        void __process_layers( const Process::Action, Manager& );
};