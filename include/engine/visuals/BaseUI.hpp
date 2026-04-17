#pragma once

#include <engine/features/Progressive.hpp>

#include <optional>


class BaseUI {
    public:
        virtual void configure( const std::optional<Progressive*>& ) = 0;

        virtual ~BaseUI() = default;
};