#pragma once

#include <buffing/Buff.hpp>


#include <SFML/System/Time.hpp>

#include <forward_list>
#include <memory>


class BuffOperator {
    public:
        BuffOperator();
        ~BuffOperator() = default;
        BuffOperator( const BuffOperator& ) = delete;

        BuffOperator& operator=( const BuffOperator& ) = delete;
        BuffOperator& operator=( const BuffOperator&& ) = delete;

        static BuffOperator& inst();

    public:
        void update( const sf::Time& );

    private:
        int period_;
        sf::Time elapsed_, lastFire_;
        std::forward_list<std::unique_ptr<Buff>> list_;
};
