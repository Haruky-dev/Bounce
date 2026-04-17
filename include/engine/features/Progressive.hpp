/*
    Defines a loading system based on arbitrary set 'work units' /
    'cost of loading' that an object takes to load.
    (e.g Loading a textures takes up to 3 work units)
*/

#pragma once

#include <atomic>


class Progressive {
    protected:
        std::atomic<int> cost {1};              // total #n of work units (start at 1 to avoid division by 0)
        std::atomic<int> progress {0};          // curr #n of work units
        std::atomic<bool> done {false};

    public:
        virtual void add_to_total( const int u ) { this->cost.fetch_add(u); }
        virtual void increment_by( int u=1 )     { this->progress.fetch_add(u); }

        virtual bool finished() const { return this->done.load(); }

        virtual ~Progressive() = default;
};