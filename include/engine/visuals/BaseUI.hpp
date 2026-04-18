#pragma once

#include <engine/features/Progressive.hpp>
#include <SFML/System/Time.hpp>

#include <optional>


class BaseUI {
    public:
        virtual void update( const sf::Time& ) = 0;
        virtual void configure( const std::optional<Progressive*>& ) = 0;

        virtual ~BaseUI() = default;
};
